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
#include "O3DMaterial.hpp"
#include "O3DQuadRenderer.hpp"
#include "O3DCubeRenderer.hpp"

#include "utils/luawrapper.hpp"

namespace o3d {
    
    class O3DSceneLoader{
    public:
        static Scene_ptr load(const char* filename, bool active = true, bool reload_includes = true);
    private:
        static Scene_ptr        g_scene;
        static Material_ptr     g_lastmaterial;
        static GameObject_ptr    g_lastobject;
        
        static void addToScene(GameObject_ptr obj);
        
        static int l_void(lua_State* L);
        static int l_include(lua_State* L);
        
        // --------- Object creators
        static int l_defaultCamera(lua_State* L);
        static int l_node(lua_State* L);
        static int l_grid(lua_State* L);
        static int l_model(lua_State* L);
        static int l_modelInstance(lua_State* L);
        
        static int l_dirLight(lua_State* L);
        static int l_spotLight(lua_State* L);
        static int l_pointLight(lua_State* L);
        static int l_ambientLight(lua_State* L);
        
        template<class T>
        static int l_mesh(lua_State* L){
            const char* id = lua_tostring(L, 1);
            GameObject_ptr go = O3DScene::createObject<O3DGameObject>(id);
            addToScene(go);
            
            std::shared_ptr<T> m = make_shared<T>();
            go->addComponent(m);
            
            return 1;
        }
        
        static int l_shader(lua_State* L);
        static int l_material(lua_State* L);
        static int l_defaultMaterial(lua_State* L);
        static int l_texture(lua_State* L);
        static int l_cubemap(lua_State* L);
        
        // --------- Model modificators
        static int l_setModelMaterial(lua_State* L);
        
        // --------- Object modificators
        static int l_setPosition(lua_State* L);
        static int l_setScale(lua_State* L);
        static int l_setRotation(lua_State* L);
        static int l_setLocalPosition(lua_State* L);
        static int l_setLocalScale(lua_State* L);
        static int l_setLocalRotation(lua_State* L);
        static int l_setParent(lua_State* L);
        static int l_setMaterial(lua_State* L);
        
        // --------- Light modificators
        static int l_setLightColor(lua_State* L);
        static int l_setLightSpecular(lua_State* L);
        static int l_setLightAngle(lua_State* L);
        static int l_setLightRange(lua_State* L);
        static int l_setLightIntensity(lua_State* L);
        static int l_setLightShadows(lua_State* L);
        
        // --------- Material modificators
        static int l_setMatVec4(lua_State* L);
        static int l_setMatVec3(lua_State* L);
        static int l_setMatVec2(lua_State* L);
        static int l_setMatFloat(lua_State* L);
        static int l_setMatInt(lua_State* L);
        static int l_setMatTexture(lua_State* L);
        static int l_setMatCubemap(lua_State* L);
    };
    
    
}
#endif /* O3DSceneLoader_hpp */
