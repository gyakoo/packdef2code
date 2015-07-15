#include "pdef_cpp.h"
#pragma warning(disable:4996)
static void CPPGenerateEnum(pdefQualificator* qualif, pdefCodeWriter* writer);
static void CPPGeneratePacketClass(pdef* pDef, const pdefProfileConfig* config, pdefPacket* pack, pdefCodeWriter* writer);
static void CPPGenerateHelpers(pdef* pDef, pdefCodeWriter* writer);
static void CPPGenerateHelperInstantiator(pdef* pDef, pdefCodeWriter* writer);
static void CPPGenerateHeader(pdef* pDef, pdefCodeWriter* writer);
static void CPPGenerateBasePacketClass( pdef* pDef, pdefCodeWriter* writer);
static void CPPGenerateFooter(pdef* pDef, pdefCodeWriter* writer);
static void CPPCalculateGroupIndices(size_t bitsgroup, pdefPacket* pack);
static void CPPGeneratePacketClassDataMembers(size_t bitsgroup, pdefPacket* pack, pdefCodeWriter* writer);
static void CPPGeneratePacketClassMethods(pdef* pDef, pdefPacket* pack, pdefCodeWriter* writer);
static void CPPGenerateFieldGetterBody(const char* retType, const char* fieldName, pdefField* field, pdefCodeWriter* writer);
static void CPPGenerateFieldSetterBody(size_t bitsgroup, const char* retType, const char* fieldName, pdefField* field, pdefCodeWriter* writer);
static void CPPGeneratePacketClassConstructor(pdef* pDef, pdefPacket* pack, pdefCodeWriter* writer);
static void CPPGeneratePacketClassStreamMethods(pdef* pDef, pdefPacket* pack, pdefCodeWriter* writer);
static void CPPGenerateFieldMethods(pdef* pDef, pdefField* field, pdefCodeWriter* writer, bool getter, bool setter);
static int CPPUniqueInt(){static int uid=0;return ++uid;}
static std::string& CPPGenNameWithNumber(const char* basename, int number, std::string& outName);
static const char* CPPGetNativeTypeForField(pdefField* field);
static std::string& CPPGetTypeOrQualifForField(pdef* pDef, pdefField* field, std::string& outTypeOrQualif);

TypeTableFunc g_typeTable=CPPGetNativeTypeForField;

void CPPSetTypeTableFunc( TypeTableFunc ttf )
{
  g_typeTable = ttf;
  if ( ttf == 0 )
    g_typeTable = CPPGetNativeTypeForField;
}
void CPPSectionComment( const char* text, pdefCodeWriter* writer, const char* ext=0)
{
  writer->Printf( "//===------------------------------===//\n" );
  writer->Printf( "// %s\n// %s\n", text, (ext&&*ext)?ext:"" );
  writer->Printf( "//===------------------------------===//\n");
}

bool CPPGenerate( pdef* pDef, const pdefProfileConfig* profile, pdefCodeWriter* writer, pdefLogCallback log )
{
  writer->Begin();

  // write file header
  CPPGenerateHeader(pDef, writer);

  // Base class
  CPPSectionComment("Base packet class",writer);
  CPPGenerateBasePacketClass( pDef, writer );

  // some helper functions
  CPPSectionComment( "Helper functions", writer);  
  CPPGenerateHelpers(pDef, writer);

  // enumerations
  CPPSectionComment("Enumerations", writer);
  writer->BeginQualificators();
  pdef::IteratorQualificators itQ = pDef->qualificators.begin();
  for ( ;itQ != pDef->qualificators.end(); ++itQ )
  {
    writer->NewQualificator();
    CPPGenerateEnum( &(*itQ), writer );
  }

  // packet classes
  writer->BeginPackets();
  pdef::IteratorPackets itP = pDef->packets.begin();
  for ( ;itP != pDef->packets.end(); ++itP )
  {
    if ( itP->generate )
    {
      writer->NewPacket();
      CPPGeneratePacketClass( pDef, profile, &(*itP), writer );
    }
  }

  // more helper functions
  CPPSectionComment( "Factory functions", writer );
  CPPGenerateHelperInstantiator(pDef,writer);  

  CPPGenerateFooter(pDef, writer);

  writer->End();  
  return true;
}

void CPPGenerateHeader(pdef* pDef, pdefCodeWriter* writer)
{
  int incid=CPPUniqueInt();
  writer->Printf( "#ifndef _INCLUDETOKEN_%d_H_\n", incid );
  writer->Printf( "#define _INCLUDETOKEN_%d_H_\n\n", incid );
  if ( pDef->numBinCopies > 0 )
    writer->Printf( "#include <stdio.h>\n");
  writer->Printf( "// Auto generated code by packdef2code\n" );
  if ( !pDef->version.empty() )
    writer->Printf( "// Version: %s\n", pDef->version.c_str() );
  if ( !pDef->desc.empty() )
    writer->Printf( "// Desc: %s\n\n", pDef->desc.c_str() );  
  if ( !pDef->ns.empty() )
    writer->Printf( "namespace %s\n{\n", pDef->ns.c_str() );
}

void CPPGenerateBasePacketClass( pdef* pDef, pdefCodeWriter* writer)
{
  writer->Printf( "class %s\n", pDef->basePacketName.c_str() );
  writer->Printf("{\n");
  writer->Printf( "public:\n");
  writer->IncIndent();
  if ( pDef->streamInfo.loader )
    writer->Printf( "virtual size_t loadFromBinaryStream(const unsigned char* data, size_t s){ return 0; }\n" );
  if ( pDef->streamInfo.saver )
    writer->Printf( "virtual size_t saveToBinaryStream(unsigned char* data, size_t s){ return 0; }\n");
  writer->Printf( "virtual unsigned int getType(){ return 0; }\n" );
  writer->DecIndent();
  writer->Printf( "};\n\n");
}

void CPPGenerateHelpers(pdef* pDef, pdefCodeWriter* writer)
{
  // Extracting bits
  writer->Printf( "template<typename N, unsigned int S, unsigned int C> inline unsigned int extractBits(N number)\n" );
  writer->Printf( "{\n" );
  writer->IncIndent();
  writer->Printf( "unsigned int t = (unsigned int)((1<<C)-1);\n" );
  writer->Printf( "t = t<<S;\n");
  writer->Printf( "return (unsigned int)( (t&number) >> S);\n" );
  writer->DecIndent();
  writer->Printf( "}\n\n" );

  // Setting bits
  writer->Printf( "template<typename T, unsigned int S, unsigned int C> inline void setBits( T& r, unsigned int value )\n" );
  writer->Printf( "{\n" );
  writer->IncIndent();
  writer->Printf( "unsigned int m = (1<<C)-1;\n" );
  writer->Printf( "unsigned int n = ~(m << S) & (unsigned int)(r);\n" );
  writer->Printf( "unsigned int v = (~m & value) << S;\n" );
  writer->Printf( "r = (T)(n|v);\n" );
  writer->DecIndent();
  writer->Printf( "}\n\n" );

  // data ptr reader
  if ( pDef->numBinCopies == pDef->packets.size() ) // only these packets if they're used by any packet
  {
    writer->Printf( "struct DataPtrReader\n" );
    writer->Printf( "{\n" );
    writer->IncIndent();
      writer->Printf( "DataPtrReader ( const unsigned char* ptr, int s ) : ptr(ptr),size(s), rem(s){}\n" );
      writer->Printf( "template<typename T> T get()\n" );
      writer->Printf( "{\n" );
      writer->IncIndent();
        writer->Printf( "if ( rem <= 0 ) return T();\n" );
        writer->Printf( "T* p = (T*)ptr; \n" );
        writer->Printf( "T ret = *p;\n" );
        writer->Printf( "++p;\n" );
        writer->Printf( "rem -= sizeof(T);\n" );
        writer->Printf( "ptr = (unsigned char*)p;\n" );
        writer->Printf( "return ret;\n" );
      writer->DecIndent();
      writer->Printf( "}\n" );
      writer->Printf( "const unsigned char* ptr;\n" );
      writer->Printf( "int size;\n" );
      writer->Printf( "int rem;\n" );
    writer->DecIndent();
    writer->Printf( "};\n\n" );
  
    // data ptr writer
    writer->Printf( "struct DataPtrWriter\n" );
    writer->Printf("{\n");
    writer->IncIndent();
      writer->Printf( "DataPtrWriter(unsigned char* ptr, int s ): ptr(ptr), size(s), rem(s){}\n" )      ;
      writer->Printf( "template<typename T> void set( T value )\n" );
      writer->Printf( "{\n" );
      writer->IncIndent();
        writer->Printf( "T* p = (T*)ptr;\n");
        writer->Printf( "*p = value;\n");
        writer->Printf( "++p;\n");
        writer->Printf( "rem -= sizeof(T);\n");
        writer->Printf( "ptr = (unsigned char*)p;\n");
      writer->DecIndent();
      writer->Printf( "}\n" );
      writer->Printf( "unsigned char* ptr;\n");
      writer->Printf( "int size;\n");
      writer->Printf( "int rem;\n");
    writer->DecIndent();
    writer->Printf("};\n\n");  
  }
}

void CPPGenerateHelperInstantiator(pdef* pDef, pdefCodeWriter* writer)
{
  if ( pDef->streamInfo.binInstantiator )
  {
    // compute offset in bytes
    size_t offs = pDef->streamInfo.binOffset/8;
    size_t bitsOffs = pDef->streamInfo.binBits % 8; // if bitsOffs > 0 then we have to make bits operation to retrive the id
    pdefField tmpType; 
    tmpType.bits = pDef->streamInfo.binBits; 
    tmpType.isReal = false;
    tmpType.isUnsigned = true;  
    const char* idType = g_typeTable(&tmpType);

    writer->Printf( "inline %s* InstancePacketFromBinaryStream(unsigned char* data, size_t size)\n", pDef->basePacketName.c_str() );
    writer->Printf( "{\n" );
    writer->IncIndent();
    if ( offs > 0 )
      writer->Printf( "data += %d;\n", offs );
    if ( bitsOffs == 0 )
      writer->Printf( "%s id = *( reinterpret_cast<%s*>(data) );\n", idType, idType );
    else
      writer->Printf( "#error Id has to be aligned to 8 bits. %d bits found in stream info.\n", pDef->streamInfo.binBits );
    writer->Printf( "%s* basepack = 0;\n", pDef->basePacketName.c_str() );
    writer->Printf( "size_t expectedBytes = 0;\n" );
    if ( !pDef->packets.empty() )
    {
      writer->Printf( "switch (id)\n" );
      writer->Printf( "{\n" );
      writer->IncIndent();
      std::string validClassName;
      for ( size_t i = 0; i < pDef->packets.size(); ++i )
      {
        pdefPacket& pck = pDef->packets[i];
        if ( !pck.generate || pck.instField == -1 ) continue;
        pdefGenerateValidIdName(pck.name, validClassName);
        writer->Printf( "case %s::PACKET_ID : expectedBytes = %s::PACKET_SIZE; basepack = new %s; break;\n", validClassName.c_str(), validClassName.c_str(), validClassName.c_str() );
      }
      writer->DecIndent();
      writer->Printf( "}\n" );
    }

    if ( pDef->streamInfo.loader )
    {
      writer->Printf( "if ( basepack != 0 )\n" );
      writer->Printf("{\n" );
      writer->IncIndent();
        writer->Printf( "size_t ret = basepack->loadFromBinaryStream(data,size);\n" );
        writer->Printf( "if ( ret != expectedBytes )\n");
        writer->Printf( "{\n" );
        writer->IncIndent();
          writer->Printf( "delete basepack;\n" );
          writer->Printf( "basepack = 0;\n");
        writer->DecIndent();
        writer->Printf( "}\n" );
      writer->DecIndent();
      writer->Printf( "}\n" );
    }
    writer->Printf( "return basepack;\n" );
    writer->DecIndent();
    writer->Printf( "}\n");
  }
}

void CPPGenerateFooter(pdef* pDef, pdefCodeWriter* writer)
{
  if ( !pDef->ns.empty() )
    writer->Printf( "}; // ns %s\n", pDef->ns.c_str() );
  writer->Printf("#endif\n");
}

void CPPGenerateEnum(pdefQualificator* qualif, pdefCodeWriter* writer)
{
  if ( qualif->type == PDEF_ENUM )
  {
    std::string validEnumName;
    writer->Printf( "enum %s\n", pdefGenerateValidIdName(qualif->name, validEnumName).c_str() );
    writer->Printf("{\n");
    writer->IncIndent();
    pdefQualificator::IteratorEntries itEE = qualif->enumEntries.begin();
    std::string finalName;
    for ( ;itEE != qualif->enumEntries.end(); ++itEE )
    {
      finalName = qualif->prefix + itEE->name;
      writer->Printf( "%s = %d,\n", pdefGenerateValidIdName(finalName, validEnumName).c_str(), itEE->value );
    }
    writer->DecIndent();
    writer->Printf( "};\n\n" );
  }
}

std::string& CPPGenNameWithNumber(const char* basename, int number, std::string& outName)
{
  char tmp[64];
  itoa(number, tmp, 10);
  outName = basename;
  outName.append(tmp);
  return outName;
}

void CPPGeneratePacketClass(pdef* pDef, const pdefProfileConfig* config, pdefPacket* pack, pdefCodeWriter* writer)
{
  std::string validClassName;
  pdefGenerateValidIdName(pack->name, validClassName);
  CPPSectionComment( pack->name.c_str(), writer, pack->desc.c_str() );  
  writer->Printf( "class %s : public %s\n", validClassName.c_str(), pDef->basePacketName.c_str() );
  writer->Printf("{\n");
  
  // calculate group indices for fields
  CPPCalculateGroupIndices(pDef->bitsgroup, pack);
  // generate constructor (default values)
  CPPGeneratePacketClassConstructor(pDef, pack, writer);  
  // generate stream methods
  CPPGeneratePacketClassStreamMethods(pDef, pack, writer);
  // methods
  CPPGeneratePacketClassMethods(pDef, pack, writer);
  // data members
  CPPGeneratePacketClassDataMembers(pDef->bitsgroup, pack, writer);

  writer->Printf( "};\n\n" );
}

void CPPCalculateGroupIndices(size_t bitsgroup, pdefPacket* pack)
{
  size_t memberNdx=0, countGroup=0, groupNdx=0;
  do
  {
    countGroup = pdefCountFieldBitsGroup( pack, memberNdx, bitsgroup );
    if ( countGroup > 1 )
    {
      size_t startInGroup=0;
      for ( size_t i = 0; i < countGroup ;++i )
      {
        pdefField& field = pack->fields[memberNdx+i];
        field.groupNdx = groupNdx;
        field.startInGroup = startInGroup;
        startInGroup += field.bits;
      }
      groupNdx++;
    }
    memberNdx += countGroup;
  } while ( countGroup != 0 && memberNdx < pack->fields.size() );
}

// todo: extract from here the logic of group index computation and use CPPCalculateGroupIndices instead
void CPPGeneratePacketClassDataMembers(size_t bitsgroup, pdefPacket* pack, pdefCodeWriter* writer)
{
  if ( pack->publicData )
    writer->Printf( "public:\n" );
  else
    writer->Printf( "protected:\n" );
  writer->IncIndent();

  std::string validIdName;
  size_t memberNdx=0, countGroup=0;
  size_t groupNdx=0, paddingNdx=0;
  do
  {
    countGroup = pdefCountFieldBitsGroup( pack, memberNdx, bitsgroup );
    if ( countGroup == 1 )
    {
      pdefField& field = pack->fields[memberNdx];
      // field name depending whether it's a padding field or not
      if ( field.isPadding )
        CPPGenNameWithNumber("Reserved_", paddingNdx++, validIdName);
      else
        pdefGenerateValidIdName(field.name, validIdName);
      // field documentation
      if ( !field.desc.empty() )
        writer->Printf( "// %s\n", field.desc.c_str() );
      if ( !field.value.empty() )
        writer->Printf( "// Default value: %s\n", field.value.c_str());
      if ( !field.units.empty() )
        writer->Printf( "// Units: %s\n", field.units.c_str() );
      if ( field.bits < (int)bitsgroup )
        writer->Printf( "// Only %d bits used!\n", field.bits );
      // field definition
      writer->Printf( "%s %s;\n\n", g_typeTable(&field), validIdName.c_str() );
    }
    else if ( countGroup > 1 )
    {
      // field documentation
      writer->Printf("// Bits are for:\n" );
      writer->IncIndent();
      for ( size_t i = 0; i < countGroup ;++i )
      {
        pdefField& field = pack->fields[memberNdx+i];
        writer->Printf( "// %s (%d bits) (Default: %s)\n", field.name.c_str(), field.bits, field.value.c_str() );
      }
      writer->DecIndent();

      // field definition
      pdefField tmpGroupField; 
      tmpGroupField.bits = bitsgroup;
      tmpGroupField.isReal = false;
      tmpGroupField.isUnsigned = true;
      CPPGenNameWithNumber("BitsGroup_", groupNdx, validIdName);
      groupNdx++;
      writer->Printf( "%s %s;\n\n", g_typeTable(&tmpGroupField), validIdName.c_str() );
    }
    memberNdx += countGroup;
  } while ( countGroup != 0 && memberNdx < pack->fields.size() );
  writer->DecIndent();
}

void CPPGeneratePacketClassMethods( pdef* pDef, pdefPacket* pack, pdefCodeWriter* writer )
{
  // public accessors / mutators methods
  writer->Printf( "public:\n");
  writer->IncIndent();
  pdefPacket::IteratorFields itF = pack->fields.begin();
  for ( ; itF != pack->fields.end(); ++itF )
  {
    if ( !itF->isPadding )
      CPPGenerateFieldMethods( pDef, &(*itF), writer, true, !itF->readOnly );
  }
  writer->DecIndent();
  writer->Printf("\n");

  // private mutators
  writer->Printf( "protected:\n" );
  writer->IncIndent();
  for ( itF = pack->fields.begin(); itF != pack->fields.end(); ++itF )
  {
    if ( !itF->isPadding && itF->readOnly )
      CPPGenerateFieldMethods( pDef, &(*itF), writer, false, true );
  }
  writer->DecIndent();
}

void CPPGenerateFieldMethods( pdef* pDef, pdefField* field, pdefCodeWriter* writer, bool getter, bool setter )
{
  std::string retType;
  CPPGetTypeOrQualifForField(pDef, field, retType);

  if ( retType.empty() || field->name.empty() )
    return;

  std::string validFieldName;
  pdefGenerateValidIdName(field->name, validFieldName);
  if ( getter )
  {
    if ( !field->desc.empty() )
      writer->Printf( "// %s\n", field->desc.c_str() );
    writer->Printf( "%s get_%s() const\n", retType.c_str(), validFieldName.c_str() );
    writer->Printf( "{\n" );
    writer->IncIndent();
    CPPGenerateFieldGetterBody(retType.c_str(), validFieldName.c_str(), field, writer);
    writer->DecIndent();
    writer->Printf( "}\n" );
  }
  if ( setter )
  {
    writer->Printf( "void set_%s( %s value )\n", validFieldName.c_str(), retType.c_str() );
    writer->Printf( "{\n" );
    writer->IncIndent();
    CPPGenerateFieldSetterBody( pDef->bitsgroup, retType.c_str(), validFieldName.c_str(), field, writer);
    writer->DecIndent();
    writer->Printf("}\n" );
  }
}

void CPPGenerateFieldGetterBody(const char* retType, const char* fieldName, pdefField* field, pdefCodeWriter* writer)
{
  if ( field->groupNdx == -1 )
  {
    writer->Printf( "return static_cast<%s>(%s);\n", retType, fieldName );
  }
  else
  {
    writer->Printf( "return static_cast<%s>( extractBits<unsigned int, %d, %d>( (unsigned int)BitsGroup_%d ) );\n",
                  retType, field->startInGroup, field->bits, field->groupNdx );
  }  
}

void CPPGenerateFieldSetterBody(size_t bitsgroup, const char* retType, const char* fieldName, pdefField* field, pdefCodeWriter* writer)
{
  if ( field->groupNdx == -1 )
  {
    writer->Printf( "%s = static_cast<%s>( value );\n", fieldName, retType );
  }
  else
  {
    pdefField tmpGroupField; 
    tmpGroupField.bits = bitsgroup;
    tmpGroupField.isReal = false;
    tmpGroupField.isUnsigned = true;    
    writer->Printf( "setBits<%s,%d,%d>( BitsGroup_%d, value );\n", g_typeTable(&tmpGroupField), field->startInGroup, field->bits, field->groupNdx );
  }
}

void CPPGeneratePacketClassConstructor(pdef* pDef, pdefPacket* pack, pdefCodeWriter* writer)
{
  writer->Printf( "public:\n" );
  writer->IncIndent();
  
  // inner enumerations
  writer->Printf( "enum\n" );
  writer->Printf( "{\n" );
  writer->IncIndent();
  writer->Printf( "PACKET_SIZE = %d,\n", pack->size );        
  if ( pack->instField != -1 && !pack->fields[pack->instField].value.empty() )
    writer->Printf("PACKET_ID = %s\n", pack->fields[pack->instField].value.c_str() );
  writer->DecIndent();
  writer->Printf( "};\n" );
  
  std::string validClassName;
  std::string retType;
  writer->Printf( "%s() :\n", pdefGenerateValidIdName(pack->name, validClassName).c_str() );
  writer->IncIndent();
  // only set in the constructor those fields that are not in bit groups
  pdefPacket::IteratorFields itF = pack->fields.begin();
  for ( ; itF != pack->fields.end(); ++itF )
  {
    if ( itF->bits >= (int)pDef->bitsgroup && !itF->value.empty() )
    {
      retType.clear();
      CPPGetTypeOrQualifForField(pDef, &(*itF), retType);
      if ( itF != pack->fields.begin() )
        writer->Printf( ", " );
      writer->Printf( "%s( static_cast<%s>(%s) )\n", pdefGenerateValidIdName(itF->name, validClassName).c_str(), retType.c_str(), itF->value.c_str() );
    }
  }
  writer->DecIndent();
  writer->Printf( "{\n" );

  writer->IncIndent();
  // for those fields in bit groups, use setters instead
  for ( itF = pack->fields.begin(); itF != pack->fields.end(); ++itF )
  {
    if ( itF->bits < (int)pDef->bitsgroup && !itF->value.empty() )
    {
      retType.clear();
      CPPGetTypeOrQualifForField(pDef, &(*itF), retType);
      writer->Printf( "set_%s( static_cast<%s>(%s) );\n", pdefGenerateValidIdName(itF->name, validClassName).c_str(), retType.c_str(), itF->value.c_str() );
    }
  }
  writer->DecIndent();
  writer->Printf( "}\n\n" );
  writer->DecIndent();
}

void CPPGeneratePacketClassStreamMethods(pdef* pDef, pdefPacket* pack, pdefCodeWriter* writer)
{
  writer->IncIndent();

  // getType()
  if ( pack->instField != -1 && !pack->fields[pack->instField].value.empty() )
    writer->Printf( "virtual unsigned int getType(){ return (unsigned int)PACKET_ID; }\n\n" );

  // Load method
  if ( pDef->streamInfo.loader )
  {
    writer->Printf( "virtual size_t loadFromBinaryStream(const unsigned char* data, size_t s)\n" );
    writer->Printf("{\n");
    writer->IncIndent();
    writer->Printf( "if (s < PACKET_SIZE) return 0;\n" );
    if ( pack->binCopy && !pack->fields.empty() )
    {
      std::string validFieldName;
      pdefGenerateValidIdName(pack->fields[0].name, validFieldName);
      writer->Printf( "memcpy(&%s, data, PACKET_SIZE);\n", validFieldName.c_str() );
      writer->Printf( "return PACKET_SIZE;\n");
    }
    else
    {
      writer->Printf( "// Using sequential read. Set the attribute binCopy=\"true\" for the packet to force memcpy instead\n" );
      writer->Printf( "DataPtrReader ptr(data,s);\n");
      writer->Printf( "size_t c = 0;\n");;
      std::string validIdName;
      size_t memberNdx = 0, paddingNdx=0;
      do 
      {
        pdefField& field = pack->fields[memberNdx];
        if ( field.groupNdx == -1 )
        {
          if ( !field.isPadding )
            pdefGenerateValidIdName(field.name, validIdName);
          else
            CPPGenNameWithNumber("Reserved_", paddingNdx++, validIdName);
          const char* fieldType = g_typeTable(&field);
          writer->Printf( "%s = ptr.get<%s>(); c += sizeof(%s);\n", validIdName.c_str(), fieldType, fieldType );
          ++memberNdx;
        }
        else
        {
          pdefField tmpGroupField; 
          tmpGroupField.bits = pDef->bitsgroup;
          tmpGroupField.isReal = false;
          tmpGroupField.isUnsigned = true;
          const char* fieldType = g_typeTable(&tmpGroupField);
          writer->Printf( "BitsGroup_%d = ptr.get<%s>(); c+= sizeof(%s);\n", field.groupNdx, fieldType, fieldType );
          char gndx = field.groupNdx;
          while ( memberNdx < pack->fields.size() && pack->fields[memberNdx].groupNdx == gndx ) 
            ++memberNdx;
        }
      } while ( memberNdx < pack->fields.size() );
      writer->Printf( "return c;\n" );
    }
    writer->DecIndent();
    writer->Printf( "}\n\n");
  }//end if loader

  // Save Method
  if ( pDef->streamInfo.saver )
  {
    writer->Printf( "virtual size_t saveToBinaryStream(unsigned char* data, size_t s)\n");
    writer->Printf("{\n");
    writer->IncIndent();
    writer->Printf( "if (s < PACKET_SIZE) return 0;\n" );
    if ( pack->binCopy && !pack->fields.empty() )
    {
      std::string validFieldName;
      pdefGenerateValidIdName(pack->fields[0].name, validFieldName);
      writer->Printf( "memcpy(data, &%s, PACKET_SIZE);\n", validFieldName.c_str() );
      writer->Printf( "return PACKET_SIZE;\n");
    }
    else
    {
      writer->Printf( "// Using sequential writing. Set the attribute binCopy=\"true\" for the packet to force memcpy instead\n" );
      writer->Printf( "DataPtrWriter ptr(data,s);\n");
      writer->Printf( "size_t c = 0;\n");
      std::string validIdName;
      size_t memberNdx = 0, paddingNdx=0;
      do 
      {
        pdefField& field = pack->fields[memberNdx];
        if ( field.groupNdx == -1 )
        {
          if ( !field.isPadding )
            pdefGenerateValidIdName(field.name, validIdName);
          else
            CPPGenNameWithNumber("Reserved_", paddingNdx++, validIdName);
          const char* fieldType = g_typeTable(&field);
          writer->Printf( "ptr.set<%s>(%s); c += sizeof(%s);\n", fieldType, validIdName.c_str(), fieldType );
          ++memberNdx;
        }
        else
        {
          pdefField tmpGroupField; 
          tmpGroupField.bits = pDef->bitsgroup;
          tmpGroupField.isReal = false;
          tmpGroupField.isUnsigned = true;
          const char* fieldType = g_typeTable(&tmpGroupField);
          writer->Printf( "ptr.set<%s>(BitsGroup_%d); c+= sizeof(%s);\n", fieldType, field.groupNdx, fieldType );
          char gndx = field.groupNdx;
          while ( memberNdx < pack->fields.size() && pack->fields[memberNdx].groupNdx == gndx ) 
            ++memberNdx;
        }
      } while ( memberNdx < pack->fields.size() );
      writer->Printf( "return c;\n" );
    }
    writer->DecIndent();
    writer->Printf( "}\n\n");
  }//end if saver  

  /*
  DataPtrWriter ptr(data,s);
  size_t c = 0;
  ptr.Set<unsigned char>(Packet_ID); c += sizeof(unsigned char);
  return c;
  */

  writer->DecIndent();
}

std::string& CPPGetTypeOrQualifForField(pdef* pDef, pdefField* field, std::string& outTypeOrQualif)
{
  const char* retType=0;
  if ( field->qualificator >= 0 && field->qualificator < (int)pDef->qualificators.size() )
  {
    pdefQualificator& qualif = pDef->qualificators[field->qualificator];
    if ( !qualif.name.empty() )
      retType = qualif.name.c_str();
  }  
  if ( !retType )
    retType = g_typeTable( field );

  if ( retType )
    outTypeOrQualif = retType;
  return outTypeOrQualif;
}

const char* CPPGetNativeTypeForField(pdefField* field)
{
  int bits = field->bits;
  if ( bits <= 8 )       bits = 8;
  else if ( bits <= 16 ) bits = 16;
  else if ( bits <= 32 ) bits = 32;
  else if ( bits <= 64 ) bits = 64;
  switch ( bits )
  {
  case 8:  return field->isUnsigned ? "unsigned char" : "char";
  case 16: return field->isUnsigned ? "unsigned short": "short";
  case 32: 
    if ( field->isReal ) return "float";
    return field->isUnsigned? "unsigned int"  : "int";
  case 64:
    if ( field->isReal ) return "double";
    return field->isUnsigned? "unsigned long long" : "long long";
  }
  return "#error";
}


#pragma warning(default:4996)

