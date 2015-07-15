#include "pdef.h"
#include "pdef_backend.h"
#include <map>
#include <stdarg.h>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>

#pragma warning(disable:4996)
typedef std::map<std::string, pdefCodeProfileFn> ProfilesMap;
ProfilesMap g_profiles;

static void DummyLog(pdefLogLevel , int , const char* ){}
static bool CommonGenerate( pdef* pDef, const pdefProfileConfig* profile, pdefCodeWriter* writer, pdefLogCallback log );

// in memory
bool pdefGenerateCodeInMemory( pdef* pDef, const pdefProfileConfig* profile, std::string& outCode, pdefLogCallback log/*=0*/ )
{
  pdefCodeWriterStr cwriter(4096);
  cwriter.SetIndent(profile->indent.c_str());
  bool res = CommonGenerate(pDef, profile, &cwriter, log);
  outCode = cwriter.GetStdStr();
  return res;
}

// in file
bool pdefGenerateCodeInFile( pdef* pDef, const pdefProfileConfig* profile, const char* outFile, pdefLogCallback log/*=0*/ )
{
  pdefCodeWriterFile cwriter(outFile, profile->separatedFiles);
  cwriter.SetIndent(profile->indent.c_str());
  return CommonGenerate(pDef, profile, &cwriter, log);
}

bool pdefInstallCodeProfile( const char* profileName, pdefCodeProfileFn profileFn )
{
  if ( g_profiles.find(profileName) != g_profiles.end() )
    return false;

  g_profiles[profileName] = profileFn;
  return true;
}


// trim from start
static inline std::string &ltrim(std::string &s) 
{
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
  return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) 
{
  s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
  return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) 
{
  return ltrim(rtrim(s));
}

std::string& pdefGenerateValidIdName(std::string& name, std::string& validName, char fillChar)
{
  trim(name);
  if ( name.empty() )
    return validName;
  validName.clear();
  validName.reserve(name.capacity());
  
  for ( size_t i = 0; i < name.length(); ++i )
  {
    if ( i==0 && isdigit(name[0]) )
      validName += fillChar;

    if ( !isalnum(name[i]) )
    {
      validName += fillChar;
    }
    else
    {
      validName += name[i];
    }
  }
  return validName;
}

bool CommonGenerate( pdef* pDef, const pdefProfileConfig* profile, pdefCodeWriter* writer, pdefLogCallback log )
{
  if ( !log ) 
    log = DummyLog;  
  ProfilesMap::iterator it = g_profiles.find(profile->name);
  if ( it == g_profiles.end() )
  {
    log(PDEF_ERROR,1,"No profile found with that name");
    return false;
  }
  if ( it->second == 0 )
  {
    log(PDEF_ERROR, 2, "Error, profile code generator is null");
    return false;
  }
  return it->second(pDef, profile, writer, log);
}

size_t pdefCountFieldBitsGroup( pdefPacket* pack, size_t start, size_t bitsgroup )
{
  if ( start >= pack->fields.size() )
    return 0;
  size_t acum=0;
  size_t count=0;
  while ( acum < bitsgroup && start+count < pack->fields.size() )
  {
    acum += pack->fields[start+count].bits;
    ++count;
  }
  if ( acum > bitsgroup && count > 1 )
    --count;
  return count;
}



// Writer classes (Base)
pdefCodeWriter::pdefCodeWriter()
  : indentChars("\t"), indentLevel(0)
{
  SetLogCallback(0);
}

void pdefCodeWriter::IncIndent()
{
  ++indentLevel;
}

void pdefCodeWriter::DecIndent()
{
  --indentLevel;
  if ( indentLevel < 0 )
    indentLevel = 0;
}
void pdefCodeWriter::SetIndent(const char* indent)
{
  indentChars = indent;
}

void pdefCodeWriter::SetLogCallback( pdefLogCallback logfn )
{
  log = logfn;
  if ( !log )
    log = DummyLog;
}

// String (InMemory)
pdefCodeWriterStr::pdefCodeWriterStr(int initCap/*=0*/)
{
  if ( initCap > 0 )
    buffer.reserve(initCap);
}

void pdefCodeWriterStr::Printf(const char* format, ...)
{
  char tmp[2048];
  va_list args;
  va_start(args, format);
  vsprintf_s(tmp, format, args);
  va_end(args);
  Indent();
  buffer.append(tmp);
}

void pdefCodeWriterStr::Indent()
{
  for ( int i = 0; i < indentLevel; ++i )
  {
    buffer.append(indentChars);
  }
}

// File
pdefCodeWriterFile::pdefCodeWriterFile(const char* fname, bool separatedFiles/*=false*/)
  : baseFilename(fname), file(0), separatedFiles(separatedFiles)
{

}

pdefCodeWriterFile::~pdefCodeWriterFile()
{
  if ( file )
    fclose(file);
}

void pdefCodeWriterFile::Printf(const char* format, ...)
{
  va_list args;
  va_start(args, format);
  Indent();
  vfprintf_s(file, format, args);
  va_end(args);
}

void pdefCodeWriterFile::Indent()
{
  if ( !file ) return;
  for ( int i = 0; i < indentLevel; ++i )
    fprintf_s(file, "%s", indentChars.c_str() );
}

void pdefCodeWriterFile::Begin()
{
  if ( file ) fclose(file);
  file = fopen(baseFilename.c_str(), "wt");  
  if ( !file )
  {
    std::string desc = "Cannot open file for writing: "; desc += baseFilename;
    log(PDEF_ERROR, 501, desc.c_str());
  }
}

// implemented to handle separated files
void pdefCodeWriterFile::BeginQualificators()
{}
void pdefCodeWriterFile::NewQualificator()
{}
void pdefCodeWriterFile::BeginPackets()
{}
void pdefCodeWriterFile::NewPacket()
{}
void pdefCodeWriterFile::End()
{
  if ( file )
    fclose(file);
  file=0;
}

#pragma warning(default:4996)
