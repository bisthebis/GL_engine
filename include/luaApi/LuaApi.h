#ifndef DEF_LUA_API_HEADER
#define DEF_LUA_API_HEADER

#include "glUtils/Camera.h"
#include "lua.hpp"

int Lua_API_getProjectionType(lua_State* L);
int Lua_API_switchProjectionType(lua_State* L);
int Lua_API_stopRunning(lua_State* L);
int Lua_API_getCamera(lua_State* L);
int Lua_API_moveCamera(lua_State* L);
int Lua_API_rotateCamera(lua_State* L);


extern glUtils::Camera *global_camera;
extern bool orthographic;
extern bool run;



#endif
