//
//  LuaWrapper.hpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 22/04/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#ifndef LuaWrapper_hpp
#define LuaWrapper_hpp


extern "C"{
    #include <lua-5.1/lualib.h>
    #include <lua-5.1/lauxlib.h>
    #include <lua-5.1/lua.h>
}

#include <glm/vec3.hpp>

namespace luawrapper {
    
    glm::vec3 get_vec3(lua_State* L){
        return glm::vec3(lua_tonumber(L, 1), lua_tonumber(L, 2), lua_tonumber(L, 3));
    }
    
}

#endif /* LuaWrapper_hpp */
