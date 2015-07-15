#ifdef _WIN32
#include <windows.h>
#endif
#include "pdef_frontend.h"
#include "pdef_cpp.h"
#include "outtest.h"

// Gets the param value after (spaces) of the param name
// for example: "app.exe -channel 5 -sync true" will return "5" if called with "-channel"
// or "true" if called with "-sync".
bool ExtractCommandLineParameter( const char* paramName, char* destParam=NULL, int maxSize=0 )
{
  bool ret = false;
  char* cmdline = NULL;
#ifdef _WIN32
  cmdline= GetCommandLineA();
#endif
  if ( cmdline )
  {
    // adding a space to search the correct param
    char paramNameWithSpace[256];
    sprintf_s(paramNameWithSpace,"%s ", paramName);
    // returns null if not found
    const char* paramStr = strstr(cmdline,paramNameWithSpace);
    ret = paramStr != NULL;

    if ( ret && destParam != NULL && maxSize > 0)
    {
      // skip until parameter value
      paramStr += strlen(paramName);
      while ( *paramStr == ' ' || *paramStr == '\t' ) ++paramStr;

      bool quotedParam = *paramStr == '"';
      int n = 0;
      // copy back the value
      if ( !quotedParam )
      { 
        // normal param finishes when a space or tab is found.
        while ( *paramStr && *paramStr != ' ' && *paramStr != '\t' && n < maxSize )
          destParam[n++] = *(paramStr++);
      }
      else
      {
        // quoted param finished when another quote is found
        ++paramStr;
        while ( *paramStr && *paramStr != '"' && n < maxSize )
          destParam[n++] = *(paramStr++);
      }
      // make sure it ends in zero
      destParam[ n < maxSize ? n : maxSize-1 ] = 0;
    }
  }
  return ret;
}

struct sConfig
{
  char packetDefFile[256];
  bool separatedFiles;
};

void ReadConfigFromCommandLine(sConfig* cfg)
{
  if ( !ExtractCommandLineParameter( "-i", cfg->packetDefFile, sizeof(cfg->packetDefFile)) )
    strcpy_s(cfg->packetDefFile, "packetdef.xml");
  cfg->separatedFiles = ExtractCommandLineParameter( "-s" );
}

void mylog(pdefLogLevel level, int code, const char* msg)
{
  switch ( level )
  {
  case PDEF_ERROR: printf( "Error: "); break;
  case PDEF_WARNING: printf( "Warning: "); break;
  case PDEF_INFO: printf( "Info: "); break;
  }
  printf( "[%d] %s\n", code, msg );
}

int main(int argc, const char** argv)
{
  /* TEST */
//   {
//     Cigi33::IG_Control igcontrol;
//     igcontrol.set_Database_Number(10);
//     igcontrol.set_Extra_Interpolation_mode(Cigi33::GBS_Enabled);
//     igcontrol.set_Host_Frame_Number(1023);
//     igcontrol.set_IG_Mode(Cigi33::IGMS_Operate);
//     igcontrol.set_Last_IG_Frame_Number(1020);
//     igcontrol.set_Timestamp(11111);
//     unsigned char tmp[256];
//     igcontrol.saveToBinaryStream(tmp,256);
//     tmp[Cigi33::IG_Control::PACKET_SIZE] = 0;
// 
//     Cigi33::BasePacket* pck = Cigi33::InstancePacketFromBinaryStream( tmp, 256 );
//     if ( pck )
//     {
//       switch ( pck->getType() )
//       {
//       case Cigi33::IG_Control::PACKET_ID: printf( "ig_control\n" ); break;
//       case Cigi33::Entity_Control::PACKET_ID: printf( "Entity_Control\n" ); break;
//       }
//     }
//   }

  // initialize standard code profiles
  pdefInstallCodeProfile("CPP", CPPGenerate);

  // read command line
  sConfig config;
  ReadConfigFromCommandLine(&config);

  // parse packet definition xml file
  pdef pdef;
  pdefFromXML(config.packetDefFile, &pdef, mylog);
  
  // generate code (atm for profile cpp)
  pdefProfileConfig codeConfig;
  codeConfig.name = "CPP";
  codeConfig.indent = "\t";
  codeConfig.bitsGroupPrefix = "BitsGroup_";
  codeConfig.separatedFiles = false;
  std::string code;
  pdefGenerateCodeInMemory(&pdef, &codeConfig, code, mylog);
  pdefGenerateCodeInFile(&pdef, &codeConfig, "outtest.h", mylog);
  return 0;
}
