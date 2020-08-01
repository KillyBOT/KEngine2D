#ifndef LUAFUNCS_H
#define LUAFUNCS_H

#include "globals.h"

int lTraceback(lua_State* L);
void lStackDump(lua_State* L);
void lCallFunc(lua_State* L, const char* funcName, int n, int r, int f);
void lLoadGetKeysFunction(lua_State* L);
std::vector<std::string> lGetTableKeys(lua_State* L, const std::string& varName);
void lGetToStack(lua_State* L, const std::string& varName );


#endif