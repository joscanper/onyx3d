//
//  O3DSceneLoader.hpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 21/04/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#ifndef O3DSceneLoader_hpp
#define O3DSceneLoader_hpp


#include "O3DScene.hpp"
#include "O3DLuaLoader.hpp"

namespace o3d {
    
    class O3DSceneLoader{
    public:
        static Scene_ptr load(const char* filename, bool active = true, bool reload_includes = true){
            
            O3DLuaLoader::clear();
            O3DLuaLoader::g_scene = std::make_shared<O3DScene>();
            
            lua_State* L = luaL_newstate();
            if (L == nullptr)
                throw("Error initializing LUA");
            luaL_openlibs(L);
            
            O3DLuaLoader::Includer::registerAll(L, reload_includes);
            
            O3DLuaLoader::ObjectDefiners::registerAll(L);
            O3DLuaLoader::ObjectModificators::registerAll(L);
            
            O3DLuaLoader::MaterialDefiners::registerAll(L);
            O3DLuaLoader::MaterialModificators::registerAll(L);
            
            O3DLuaLoader::LighModificators::registerAll(L);
            
            std::string path = O3D().getResources().getResourcesPath(filename);
            if(luaL_dofile(L, path.c_str()))
                std::cout << lua_tostring(L, -1) << std::endl;
            
            lua_close(L);
            
            if (active)
                O3DScene::setActiveScene(O3DLuaLoader::g_scene);
            
            return O3DLuaLoader::g_scene;
        }
    };
    
    
}
#endif /* O3DSceneLoader_hpp */
