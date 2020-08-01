#include "luafuncs.h"

int lTraceback(lua_State* L) {
	lua_getglobal(L, "debug");
	lua_getfield(L, -1, "traceback");
	lua_pushvalue(L, 1);
	lua_pushinteger(L, 2);
	lua_call(L, 2, 1);
	lua_pop(L, 1);
	return 1;
}

void lCallFunc(lua_State* L, const char* funcName, int n, int r, int f) {
	lua_pushcfunction(L, lTraceback);
	lua_getglobal(L, funcName);
	if (lua_pcall(L, n, r, f)) {
		const char* error = lua_tostring(L, -1);
		lua_getglobal(L, "engine_error");
		lua_pushstring(L, error);
		lua_pcall(L, 1, 0, 0);
	}
}

void lStackDump(lua_State* L) {
	int i, t, top;
	top = lua_gettop(L);
	for (i = 1; i <= top; i++) {
		t = lua_type(L, i);

		switch (t) {
		case LUA_TSTRING:
			printf("String\t[%s]", lua_tostring(L, i));
			break;
		case LUA_TBOOLEAN:
			printf("Boolean\t[");
			printf(lua_toboolean(L, i) ? "true" : "false");
			printf("]");
			break;
		case LUA_TNUMBER:
			printf("Number\t[%.3lf]", lua_tonumber(L, i));
			break;
		default:
			printf("Type\t[%s]", lua_typename(L, i));
			break;
		}
		printf("\n");
	}

	printf("\n");
}

void lLoadGetKeysFunction(lua_State* L) {
	std::string luaCode =
		R"(function getKeys(t)
			s = {}
			for k, v in pairs(t) do
				table.insert(s,k)
			end
			return s
		end)";
	luaL_dostring(L, luaCode.c_str());
}

//Gets table keys, which we can then handle using a system

std::vector<std::string> lGetTableKeys(lua_State* L, const std::string& varName) {
	
	std::vector<std::string> keys;

	lua_getglobal(L, "getKeys");
	if (lua_isnil(L, -1)) {
		lLoadGetKeysFunction(L);
		lua_getglobal(L, "getKeys");
	}

	lGetToStack(L, varName.c_str());

	lua_pcall(L, 1, 1, 0);

	while (lua_next(L, -2)) {
		if (lua_type(L, -1) == LUA_TSTRING) keys.push_back(lua_tostring(L, -1));
		lua_pop(L, 1);
	}

	lua_settop(L, 0);
}

//Allows for more fine control over which table specifically you pick

void lGetToStack(lua_State* L, const std::string& varName) {
	int layer = 0;
	int index;
	std::string var = "";

	for (int i = 0; i < varName.size(); i++) {
		if (varName.at(i) == '.') {
			if (layer == 0) lua_getglobal(L, var.c_str());
			else lua_getfield(L, -1, var.c_str());

			if (lua_isnil(L, -1)) {
				printf("Error! Specified variable could not be found\n");
				return;
			}
			else {
				var = "";
				layer++;
			}
		}
		else {
			var += varName.at(i);
		}
	}

	if (layer == 0) lua_getglobal(L, var.c_str());
	else lua_getfield(L, -1, var.c_str());

	if (layer == 0) return;

	index = lua_gettop(L) - layer;
	lua_replace(L, index);
	lua_settop(L, index);
}
