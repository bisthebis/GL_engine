#include "LuaState.h"
#include <cassert>

LuaState::LuaState()
{
    _state = luaL_newstate();
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

