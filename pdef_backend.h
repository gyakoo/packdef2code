#ifndef _PDEF_BACKEND_H_
#define _PDEF_BACKEND_H_

struct pdef;
struct pdefProfileConfig
{
  std::string name;
  std::string indent;
  std::string bitsGroupPrefix;
  bool separatedFiles;
};

// Writer classes
class pdefCodeWriter
{
public:
  pdefCodeWriter();
  virtual void Printf(const char* format, ...) = 0;
  void IncIndent();
  void DecIndent();
  void SetIndent(const char* indent);
  void SetLogCallback( pdefLogCallback logfn );

  virtual void Begin(){}
  virtual void BeginQualificators(){}
  virtual void NewQualificator(){}
  virtual void BeginPackets(){}
  virtual void NewPacket(){}
  virtual void End(){}

protected:
  virtual void Indent() = 0;
  pdefLogCallback log;
  std::string indentChars;
  int indentLevel;
};

class pdefCodeWriterStr : public pdefCodeWriter
{
public:
  pdefCodeWriterStr(int initCap=0);
  const char* GetStr(){ return buffer.c_str(); }
  const std::string& GetStdStr(){ return buffer; }
  size_t Length(){ return buffer.length(); }
  virtual void Printf(const char* format, ...);

protected:
  virtual void Indent();
  std::string buffer;
};

class pdefCodeWriterFile : public pdefCodeWriter
{
public:
  pdefCodeWriterFile(const char* fname, bool separatedFiles=false);
  ~pdefCodeWriterFile();
  virtual void Printf(const char* format, ...);
  virtual void Begin();
  virtual void BeginQualificators();
  virtual void NewQualificator();
  virtual void BeginPackets();
  virtual void NewPacket();
  virtual void End();

protected:
  virtual void Indent();
  std::string baseFilename;
  FILE* file;
  bool separatedFiles;
};

// Function callback for code generators
typedef bool (*pdefCodeProfileFn)( pdef* pDef, const pdefProfileConfig* profile, pdefCodeWriter* writer, pdefLogCallback log );

// high level functions
bool pdefInstallCodeProfile( const char* profileName, pdefCodeProfileFn profileFn );
bool pdefGenerateCodeInFile( pdef* pDef, const pdefProfileConfig* profile, const char* outFile, pdefLogCallback log=0 ); // file
bool pdefGenerateCodeInMemory( pdef* pDef, const pdefProfileConfig* profile, std::string& outCode, pdefLogCallback log=0 ); // in memory

// helper functions for backend
std::string& pdefGenerateValidIdName(std::string& name, std::string& validName, char fillChar='_');
size_t pdefCountFieldBitsGroup( pdefPacket* pack, size_t start, size_t bitsgroup );
#endif