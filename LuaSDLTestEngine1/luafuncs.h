#ifndef LUAFUNCS_H
#define LUAFUNCS_H

#include "globals.h"
extern "C" {
	static int lTraceback(lua_State* L);
	static void lStackDump(lua_State* L);
	static void lCallFunc(lua_State* L, const char* funcName, int n, int r, int f);
	int lOpenLibCustom(lua_State* L);
}
#endif