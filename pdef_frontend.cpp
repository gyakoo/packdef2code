#include "pdef_frontend.h"
#include "tinyxml2.h"
#include <string.h>
#include <map>

using namespace tinyxml2;

struct pdefImpl
{
  typedef std::map<std::string,size_t> maptype;
  maptype qualifMap;
  maptype packetMap;
};

// forward declarations
static void DummyLog(pdefLogLevel , int , const char* );
static void ParseStrAttr(XMLElement* elm, const char* attrName, std::string& str);
static bool ReadQualificator(XMLElement* elm, pdefQualificator* qualif, pdefLogCallback log);
static void ReadStreamInfo( XMLElement* elm, pdefStreamInfo* strInfo, pdefLogCallback log );
static bool ReadPacket(XMLElement* elm, pdef* pDef, pdefPacket* pack, pdefLogCallback log);
static void ReadInclude( XMLElement* elm, pdef* pDef, pdefPacket* pack, pdefLogCallback log );
static bool ReadField( XMLElement* elm, pdef* pDef, pdefField* field, bool* instantiator, pdefLogCallback log );
static bool Validate( pdef* pDef, pdefLogCallback log );
static const char* NextInt(const char* str, int* val, char sep);
static void ParsePairFieldValues( const char* valuesStr, std::map<int,std::string>& pairs );


// function implementations
bool pdefFromXML( const char* xmlfile, pdef* outPdef, pdefLogCallback log/*=0*/ )
{
  // always valid pointer to avoid 'if' during parsing
  if ( !log )
    log = DummyLog;

  XMLDocument doc;
  if ( doc.LoadFile( xmlfile ) != XML_SUCCESS )
  {
    log(PDEF_ERROR, 1, "Cannot open the file or xml parsing error" );
    return false;
  }

  // Root
  XMLElement* root = doc.FirstChildElement("packetdef");
  if ( !root )
  {
    log(PDEF_ERROR, 2, "Cannot find <packetdef> root element" );
    return false;
  }
  // read values (set defaults)
  ParseStrAttr(root, "version", outPdef->version);
  ParseStrAttr(root, "desc", outPdef->desc);
  ParseStrAttr(root, "basepacket", outPdef->basePacketName);
  if ( outPdef->basePacketName.empty() ) outPdef->basePacketName = "BasePacket";
  ParseStrAttr(root, "namespace", outPdef->ns );
  outPdef->numBinCopies = 0;
  ReadStreamInfo( root->FirstChildElement( "stream" ), &outPdef->streamInfo, log );
  
  outPdef->packets.clear();
  outPdef->qualificators.clear();
  outPdef->impl = new pdefImpl; // internal data for parsing
  int bitsgroup=8;
  root->QueryIntAttribute("bitsgroup", &bitsgroup);
  outPdef->bitsgroup = (size_t)bitsgroup;
  if ( outPdef->bitsgroup != 8 && outPdef->bitsgroup != 16 && outPdef->bitsgroup != 32 )
  {
    std::string desc="Bitsgroup has to be 8, 16 or 32, and found: "; desc += root->Attribute("bitsgroup");
    log(PDEF_WARNING, 0, desc.c_str());
    log(PDEF_WARNING, 0, "Using bitsgroup=8");
    outPdef->bitsgroup = 8;
  }

  // Reading all <qualificator>s first
  XMLElement* elm = root->FirstChildElement("qualificator");
  while ( elm )
  {
    pdefQualificator qualif;
    if ( ReadQualificator(elm, &qualif, log) )
    {
      if ( outPdef->impl->qualifMap.find(qualif.name) == outPdef->impl->qualifMap.end() )
      {
        outPdef->impl->qualifMap[qualif.name] = outPdef->qualificators.size();
        outPdef->qualificators.push_back(qualif);
      }
      else
      {
        std::string desc="Qualifier already defined: "; desc+=qualif.name;
        log(PDEF_WARNING, 1, desc.c_str() );
      }
    }
    elm = elm->NextSiblingElement("qualificator");
  }
  if ( outPdef->qualificators.empty() )
    log(PDEF_WARNING, 2, "Cannot find any qualificator" );

  // Reading all <packet>s then
  elm = root->FirstChildElement("packet");
  while ( elm )
  {
    pdefPacket packet;
    if ( ReadPacket(elm, outPdef, &packet, log) )
    {
      outPdef->impl->packetMap[packet.name] = outPdef->packets.size();
      outPdef->packets.push_back(packet);
    }
    else
    {
      std::string desc="Packet definition already defined: "; desc+=packet.name;
      log(PDEF_WARNING, 3, desc.c_str() );
    }
    elm = elm->NextSiblingElement("packet");
  }
  if ( outPdef->packets.empty() )
    log(PDEF_WARNING, 4, "Cannot find any packet definition" );

  // releasing temporary resources
  delete outPdef->impl;
  outPdef->impl = 0;
  return Validate(outPdef,log);
}

void DummyLog(pdefLogLevel , int , const char* )
{
}

void ReadStreamInfo( XMLElement* elm, pdefStreamInfo* strInfo, pdefLogCallback log )
{
  strInfo->saver = strInfo->loader = true;
  strInfo->binInstantiator = false;
  strInfo->texInstantiator = false;
  if ( !elm )
  {
    log( PDEF_WARNING, 1, "<stream> not found, using defaults" );    
    return;
  }
  elm = elm->FirstChildElement();
  while ( elm )
  {
    if ( _stricmp(elm->Value(), "loader") == 0 )
    {
      elm->QueryBoolAttribute( "create", &strInfo->loader );
    }else if ( _stricmp(elm->Value(), "saver" ) == 0 )
    {
      elm->QueryBoolAttribute( "create", &strInfo->saver );
    }else if ( _stricmp(elm->Value(), "instantiator" ) == 0)
    {
      const char* type = elm->Attribute("type");
      if ( !type || _stricmp(type,"binary")== 0 )
      {
        strInfo->binInstantiator = true;
        strInfo->binOffset = 0;
        strInfo->binBits = 8;
        elm->QueryIntAttribute( "offset", &strInfo->binOffset );
        elm->QueryIntAttribute( "bits", &strInfo->binBits );
      }else if ( _stricmp( type, "text" )== 0 )
      {
        strInfo->texInstantiator = true;
        strInfo->texOffset = 0;
        elm->QueryIntAttribute( "offset", &strInfo->texOffset );
      }
    }
    elm = elm->NextSiblingElement();
  }
}


void ParseStrAttr(XMLElement* elm, const char* attrName, std::string& str)
{
  const char* attStr = elm->Attribute(attrName);
  str = attStr ? attStr : "";
}

bool ReadQualificator(XMLElement* elm, pdefQualificator* qualif, pdefLogCallback log)
{
  if ( !elm || !qualif )
  {
    log( PDEF_WARNING, 11, "Qualificator element or instance is null" );
    return false;
  }
  ParseStrAttr(elm, "name", qualif->name);
  if ( qualif->name.empty() )
  {
    log( PDEF_WARNING, 12, "Qualificator name is empty" );
    return false;
  }
  ParseStrAttr(elm, "prefix", qualif->prefix);
  std::string type;
  ParseStrAttr(elm, "type", type);
  if ( _stricmp(type.c_str(), "enum") == 0 )
  {
    // if it's an ENUM qualificator type 
    qualif->type = PDEF_ENUM;
    XMLElement* qelm = elm->FirstChildElement("enum");
    pdefEnumEntry enumEntry;
    while ( qelm )
    {
      ParseStrAttr(qelm, "name", enumEntry.name);
      enumEntry.value = (unsigned int)qelm->IntAttribute("value");
      // valid name?
      if ( !enumEntry.name.empty() )
        qualif->enumEntries.push_back(enumEntry); 
      qelm = qelm->NextSiblingElement("enum");
    }

    // no enumerator entries
    if ( qualif->enumEntries.empty() )
    {
      std::string desc = "Qualificator has no entries: "; desc += qualif->name;
      log( PDEF_WARNING, 13, desc.c_str() );
      return false;
    }
  }  
  else
  {
    // no more types supported at the moment
    std::string desc = "Qualificator type not supported: "; desc += qualif->name;
    log(PDEF_WARNING, 14, desc.c_str() );
    return false;
  }
  return true;
}

void ReadInclude( XMLElement* elm, pdef* pDef, pdefPacket* pack, pdefLogCallback log )
{
  if ( !elm || !pDef || !pack )
  {
    log(PDEF_WARNING,31,"Error arguments in ReadInclude");
    return;
  }
  std::string incName;
  ParseStrAttr(elm, "name", incName);
  if ( incName.empty() )
  {
    log(PDEF_WARNING, 32, "Empty include name");
    return;
  }

  pdefImpl::maptype::iterator it = pDef->impl->packetMap.find(incName);
  if ( it == pDef->impl->packetMap.end() )
  {
    std::string desc="Include packet name not found. Has to be defined before: "; desc += incName;
    log(PDEF_WARNING, 33, desc.c_str());
    return;
  }

  // getting the real packet values from index
  if ( it->second >= pDef->packets.size() )
  {
    std::string desc="Include packet index out of bounds: "; desc += incName;
    log(PDEF_WARNING, 34, desc.c_str() );
    return;
  }
  const pdefPacket& incPacket = pDef->packets[it->second];

  // getting the values to instantiate
  std::string valuesStr;  
  std::map< int, std::string > pairs;
  ParseStrAttr(elm, "values", valuesStr);
  if ( !valuesStr.empty() )
    ParsePairFieldValues(valuesStr.c_str(), pairs);
  for ( size_t i = 0; i < incPacket.fields.size(); ++i )
  {
    pdefField field = incPacket.fields[i]; // copy & instantiate value
    if ( pairs.find((int)i) != pairs.end() )
      field.value = pairs[(int)i];
    pack->fields.push_back(field);
  }
  pack->instField = incPacket.instField;
}

bool ReadField( XMLElement* elm, pdef* pDef, pdefField* field, bool* instantiator, pdefLogCallback log )
{
  if ( !elm || !pDef || !field )
  {
    log(PDEF_WARNING,41,"Invalid arguments for ReadField");
    return false;
  }
  field->isPadding = false;
  elm->QueryBoolAttribute("padding", &field->isPadding);
  ParseStrAttr(elm, "name", field->name);
  if ( !field->isPadding && field->name.empty() )
  {
    log(PDEF_WARNING, 42, "Field with no name. Only padding fields can be unnamed." );
    return false;
  }
  if ( elm->QueryIntAttribute("bits",&field->bits) != XML_SUCCESS )
  {
    std::string desc = "Bits is mandatory for field: "; desc += field->name;
    log(PDEF_WARNING, 43, desc.c_str() );
    return false;
  }
  field->readOnly = false;
  field->isUnsigned = false;
  field->isReal = false;
  field->groupNdx = -1;
  field->startInGroup = -1;
  ParseStrAttr(elm, "value", field->value );
  ParseStrAttr(elm, "desc", field->desc);
  ParseStrAttr(elm, "units", field->units);
  elm->QueryBoolAttribute( "readonly", &field->readOnly );
  elm->QueryBoolAttribute( "unsigned", &field->isUnsigned );
  elm->QueryBoolAttribute( "real", &field->isReal );
  *instantiator = false;
  elm->QueryBoolAttribute( "instantiator", instantiator );

  // index to qualificator
  field->qualificator = -1;
  std::string qualifName;
  ParseStrAttr(elm, "qualificator", qualifName);
  pdefImpl::maptype::iterator it = pDef->impl->qualifMap.find( qualifName );
  if ( it != pDef->impl->qualifMap.end() )
    field->qualificator = (int)it->second;

  return true;
}

bool ReadPacket(XMLElement* elm, pdef* pDef, pdefPacket* pack, pdefLogCallback log)
{
  if (!elm || !pack)
  {
    log(PDEF_WARNING, 21, "Invalid elm or pack instance" );
    return false;
  }
  ParseStrAttr(elm, "name", pack->name);
  if ( pack->name.empty() )
  {
    log(PDEF_WARNING, 22, "No name for packet" );
    return false;
  }
  ParseStrAttr(elm, "desc", pack->desc);
  pack->size = elm->IntAttribute("size");
  if ( pack->size <= 0 )
  {
    std::string desc="Invalid size for packet: "; desc += pack->name;
    log(PDEF_WARNING, 23, desc.c_str() );
    return false;
  }
  pack->generate = true;
  pack->instField = -1;
  pack->binCopy = true;
  elm->QueryBoolAttribute("generate", &pack->generate);
  if ( pack->binCopy )
    ++pDef->numBinCopies;
  pack->publicData = false;
  elm->QueryBoolAttribute("publicdata", &pack->publicData);
  elm->QueryBoolAttribute("bincopy", &pack->binCopy);
  elm = elm->FirstChildElement();
  while ( elm )
  {
    if ( _stricmp(elm->Value(),"include") == 0 )
    {
      ReadInclude(elm, pDef, pack, log);
    }
    else if ( _stricmp(elm->Value(),"field") == 0 )
    {
      pdefField field;
      bool instantiator=false;
      if ( ReadField(elm, pDef, &field, &instantiator, log ) )
      {
        pack->fields.push_back(field);
        if ( instantiator )
          pack->instField = (int)pack->fields.size()-1;
      }
    }
    else
    {
      std::string desc="Invalid tag found in packet definition. Only <field> and <include> allowed: ";
      desc += pack->name;
      log(PDEF_WARNING, 25, desc.c_str() );
    }
    elm = elm->NextSiblingElement();
  }

  if ( pack->fields.empty() )
  {
    std::string desc="No fields found for packet: "; desc+=pack->name;
    log( PDEF_WARNING, 29, desc.c_str() );
  }

  return true;
}

bool Validate( pdef* pDef, pdefLogCallback log )
{
  // check packet sizes
  // check padding/alignment?
  // warning qualificator entries with same value
  // warning/fix/check field with same name in the same packet
  // check if packets with same name
  return true;
}

const char* NextInt(const char* str, int* val, char sep)
{
  char tmp[64];
  int ndx=0;
  while (*str && *str!=sep && ndx < 63 )
  {
    while ( *str == ' ' || *str == '\t') ++str;
    if ( *str==sep) break;
    tmp[ndx++] = *str;
    ++str;
  }
  tmp[ndx]=0;
  *val = atoi(tmp);
  if ( *str == sep )
    ++str;
  return str;
}

void ParsePairFieldValues( const char* valuesStr, std::map<int,std::string>& pairs )
{
  const char* str = valuesStr;
  while ( *str )
  {
    int fndx=-1;
    str = NextInt(str,&fndx,'=');
    if ( !*str ) return;
    // value as string
    std::string fval;
    while ( *str && *str != ';' )
    {
      if ( *str != ' ' && *str != '\t' )
        fval += *str;
      ++str;
    }
    if ( *str == ';' ) ++str;
    pairs[fndx] = fval;
  }
}