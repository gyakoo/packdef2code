#ifndef _PDEF_FRONTEND_H_
#define _PDEF_FRONTEND_H_
#include "pdef.h"

bool pdefFromXML( const char* xmlfile, pdef* outPdef, pdefLogCallback logCb=0 );

#endif