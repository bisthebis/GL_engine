#include "LuaState.h"
#include <cassert>

LuaState::LuaState()
{
    _state = luaL_newstate();

    luaopen_base(_state);
    luaopen_io(_state);
    luaopen_math(_state);
    luaopen_string(_state);
    assert(_state);
}
LuaState::~LuaState()
{
    lua_close(_state);
}
lua_State* LuaState::operator()()
{
    return _state;
}
void LuaState::doProcedure(const char *name, int N_Args)
{
    lua_getglobal(_state, name);
    lua_pcall(_state, N_Args, 0, 0);
}
