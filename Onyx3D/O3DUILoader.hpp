//
//  O3DUILoader.hpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 14/05/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#ifndef O3DUILoader_hpp
#define O3DUILoader_hpp

#include "O3DGameObject.hpp"
#include "O3DLuaLoader.hpp"

#include <boost/algorithm/string/replace.hpp>

namespace o3d{
    class O3DUILoader {
    public:
        static void load(const char* filename){
            
            O3DLuaLoader::clear();
            O3D().getUI().clear();
            
            lua_State* L = luaL_newstate();
            if (L == nullptr)
                throw("Error initializing LUA");
            luaL_openlibs(L);
            
            
            O3DLuaLoader::Includer::registerAll(L, true);
            O3DLuaLoader::ObjectModificators::registerAll(L);
            O3DLuaLoader::UIDefiners::registerAll(L);
            O3DLuaLoader::UIModificators::registerAll(L);
            
            std::ifstream ifs(filename);
            std::string content( (std::istreambuf_iterator<char>(ifs) ),
                                (std::istreambuf_iterator<char>()    ) );
            
            boost::replace_all( content, "@W", std::to_string(O3D().getScreenSize().x));
            boost::replace_all( content, "@H", std::to_string(O3D().getScreenSize().y));
            
            if(luaL_dostring(L, content.c_str()))
                std::cout << lua_tostring(L, -1) << std::endl;
            
            lua_close(L);
            
        }
    };
}

#endif /* O3DUILoader_hpp */
