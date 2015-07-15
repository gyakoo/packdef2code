#ifndef _PDEF_CPP_H_
#define _PDEF_CPP_H_

#include "pdef.h"
#include "pdef_backend.h"

typedef const char* (*TypeTableFunc)(pdefField*);

bool CPPGenerate( pdef* pDef, const pdefProfileConfig* profile, pdefCodeWriter* writer, pdefLogCallback log );
void CPPSetTypeTableFunc( TypeTableFunc ttf );

#endif