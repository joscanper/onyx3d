//
//  luawrapper.hpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 22/04/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#ifndef luawrapper_h
#define luawrapper_h


extern "C"{
#include <lua-5.1/lualib.h>
#include <lua-5.1/lauxlib.h>
#include <lua-5.1/lua.h>
}

#include <glm/vec3.hpp>


class luawrapper{
    public:
   
    static glm::vec2 get_vec2(lua_State* L){
        return glm::vec2(lua_tonumber(L, 1), lua_tonumber(L, 2));
    }
    
    static glm::vec3 get_vec3(lua_State* L){
        return glm::vec3(lua_tonumber(L, 1), lua_tonumber(L, 2), lua_tonumber(L, 3));
    }
    
    static glm::vec4 get_vec4(lua_State* L){
        return glm::vec4(lua_tonumber(L, 1), lua_tonumber(L, 2), lua_tonumber(L, 3), lua_tonumber(L, 4));
    }
    
    static float pop_number(lua_State* L, float def){
        float val;
        if (lua_gettop(L) >= 1){
            val = lua_tonumber(L, 1);
            lua_remove(L, 1);
        }else{
            val = def;
        }
        return val;
    }
    
    static const char* pop_string(lua_State* L, const char* def){
        const char* val;
        if (lua_gettop(L) >= 1){
            val = lua_tostring(L, 1);
            lua_remove(L, 1);
        }else{
            val = def;
        }
        return val;
    }
};

#endif /* luawrapper_h */
