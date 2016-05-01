#include "luaApi/LuaApi.h"

int Lua_API_getProjectionType(lua_State* L)
{

    lua_pushlightuserdata(L, &orthographic);
    return 1;
}
int Lua_API_switchProjectionType(lua_State* L)
{
    bool* type_ptr = (bool*) lua_topointer(L, -1);
    *type_ptr = !(*type_ptr);

    return 0;
}
int Lua_API_getCamera(lua_State* L)
{

    lua_pushlightuserdata(L, global_camera);
    return 1;
}

int Lua_API_moveCamera(lua_State* L)
{
    glUtils::Camera* camera = (glUtils::Camera*) lua_topointer(L, -2);
    int direction = lua_tointeger(L, -1);
    camera->deplacer(direction);

    return 0;
}

int Lua_API_rotateCamera(lua_State* L)
{
    glUtils::Camera* camera = (glUtils::Camera*) lua_topointer(L, -3);
    float x = lua_tointeger(L, -2);
    float y = lua_tointeger(L, -1);
    camera->orienter(x, y);

    return 0;
}


