#ifndef DEF_MYLUA_HPP
#define DEF_MYLUA_HPP

#include "lua.hpp"

class LuaState
{
    private:
        lua_State* _state = nullptr;

    public:
        LuaState();
        ~LuaState();
        LuaState(const LuaState&) = delete;

        lua_State* operator()();

        void doProcedure(const char* name, int N_args = 0);

};

#endif

