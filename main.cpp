#include <iostream>

#ifdef __cplusplus
  extern "C" {
    #include <lua/lua.h>
    #include <lua/lualib.h>
    #include <lua/lauxlib.h>
  }
#endif //__cplusplus

int main(int argc, char **argv) {
    std::cout << "LUA is saying: ";

    lua_State* L;
    L = luaL_newstate();
    lua_pushstring(L, "Anna");
    lua_setglobal(L, "name");
    luaL_openlibs(L);
    if(luaL_dofile(L, "hello.lua")) {
        std::cout << "Final:" << lua_tostring(L, -1) << "\n";
    }
    lua_close(L);
}
