//
//  O3DLuaLoader
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 14/05/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#ifndef O3DLuaLoader_hpp
#define O3DLuaLoader_hpp

#include "O3DCore.hpp"
#include "O3DLight.hpp"
#include "O3DGridRenderer.hpp"
#include "O3DOctahedronRenderer.hpp"

#include "utils/luawrapper.hpp"

namespace o3d {
    namespace O3DLuaLoader{
    
        extern GameObject_ptr   g_lastobject;
        extern Scene_ptr        g_scene;
        extern Material_ptr     g_lastmaterial;
        
        void clear();
        
        namespace Includer{
            int l_void(lua_State* L);
            int l_include(lua_State* L);

            void registerAll(lua_State* L, bool reload_includes);
        }
        
        namespace LighModificators{
            int l_setLightColor(lua_State* L);
            int l_setLightSpecular(lua_State* L);
            int l_setLightAngle(lua_State* L);
            int l_setLightRange(lua_State* L);
            int l_setLightIntensity(lua_State* L);
            int l_setLightShadows(lua_State* L);
            
            void registerAll(lua_State* L);
        }
        
        namespace MaterialDefiners{
            int l_material(lua_State* L);
            int l_defaultMaterial(lua_State* L);
            int l_shader(lua_State* L);
            int l_texture(lua_State* L);
            int l_cubemap(lua_State* L);
             void registerAll(lua_State* L);
        }
        
        namespace MaterialModificators{
            int l_setMatVec4(lua_State* L);
            int l_setMatVec3(lua_State* L);
            int l_setMatVec2(lua_State* L);
            int l_setMatFloat(lua_State* L);
            int l_setMatInt(lua_State* L);
            int l_setMatTexture(lua_State* L);
            int l_setMatCubemap(lua_State* L);
            
            void registerAll(lua_State* L);
        };
        
        namespace ObjectDefiners{
            void addToScene(GameObject_ptr obj);
            
            template<class T>
             int l_mesh(lua_State* L){
                const char* id = lua_tostring(L, 1);
                GameObject_ptr go = O3DScene::createObject<O3DGameObject>(id);
                addToScene(go);
                
                std::shared_ptr<T> m = make_shared<T>();
                go->addComponent(m);
                
                return 1;
            }
            
            
            int l_defaultCamera(lua_State* L);
            int l_node(lua_State* L);
            int l_model(lua_State* L);
            int l_modelInstance(lua_State* L);
            int l_dirLight(lua_State* L);
            int l_spotLight(lua_State* L);
            int l_pointLight(lua_State* L);
            int l_ambientLight(lua_State* L);

             void registerAll(lua_State* L);
        };
        
        namespace ObjectModificators{
             int l_setPosition(lua_State* L);
             int l_setScale(lua_State* L);
             int l_setRotation(lua_State* L);
             int l_setLocalPosition(lua_State* L);
             int l_setLocalScale(lua_State* L);
             int l_setLocalRotation(lua_State* L);
             int l_setParent(lua_State* L);
             int l_setModelMaterial(lua_State *L);
            
             void registerAll(lua_State* L);
        };
        
        namespace UIDefiners{
            int l_draw(lua_State* L);
            int l_font(lua_State* L);
            int l_text(lua_State* L);
            
            void registerAll(lua_State* L);
        }
        
        namespace UIModificators{
            int l_setColor(lua_State* L);
            
            void registerAll(lua_State* L);
        }
        
    };
    
}


#endif
