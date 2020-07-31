#include "luafuncs.h"

extern "C" {
	static int lTraceback(lua_State* L) {
		lua_getglobal(L, "debug");
		lua_getfield(L, -1, "traceback");
		lua_pushvalue(L, 1);
		lua_pushinteger(L, 2);
		lua_call(L, 2, 1);
		lua_pop(L, 1);
		return 1;
	}

	static void lCallFunc(lua_State* L, const char* funcName, int n, int r, int f) {
		lua_pushcfunction(L, lTraceback);
		lua_getglobal(L, funcName);
		if (lua_pcall(L, n, r, f)) {
			const char* error = lua_tostring(L, -1);
			lua_getglobal(L, "engine_error");
			lua_pushstring(L, error);
			lua_pcall(L, 1, 0, 0);
		}
	}

	static void lStackDump(lua_State* L) {
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

	int lOpenLibCustom(lua_State* L) {
		//luaL_newlib(L, window);
		//luaL_newlib(L, graphics);
		return 1;
	}
}