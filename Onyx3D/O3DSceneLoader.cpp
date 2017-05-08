//
//  O3DSceneLoader.cpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 21/04/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#include "O3DCore.hpp"

#include "O3DSceneLoader.hpp"
#include "O3DCubeRenderer.hpp"
#include "O3DQuadRenderer.hpp"
#include "O3DGridRenderer.hpp"
#include "O3DOctahedronRenderer.hpp"
#include "O3DSkyboxRenderer.hpp"
#include "O3DSpotLight.hpp"
#include "O3DModel.hpp"
#include "O3DModelProxy.hpp"


extern "C"{
#include <lua-5.1/lualib.h>
#include <lua-5.1/lauxlib.h>
#include <lua-5.1/lua.h>
}

#include <iostream>

using namespace o3d;

Scene_ptr       O3DSceneLoader::g_scene = nullptr;
GameObject_ptr  O3DSceneLoader::g_lastobject = nullptr;
Material_ptr    O3DSceneLoader::g_lastmaterial = nullptr;


Scene_ptr O3DSceneLoader::load(const char* filename, bool active, bool reload_includes){
    
    g_scene = std::make_shared<O3DScene>();
    g_lastobject = nullptr;
    
    lua_State* L = luaL_newstate();
    if (L == nullptr)
        throw("Error initializing LUA");
    luaL_openlibs(L);
    
    if (reload_includes)
        lua_register(L, "include", O3DSceneLoader::l_include);
    else
        lua_register(L, "include", O3DSceneLoader::l_void);
    
    
    // Object creation
    lua_register(L, "ambient_light", O3DSceneLoader::l_ambientLight);
    lua_register(L, "default_camera", O3DSceneLoader::l_defaultCamera);
    lua_register(L, "node", O3DSceneLoader::l_node);
    lua_register(L, "grid", O3DSceneLoader::l_mesh<O3DGridRenderer>);
    lua_register(L, "cube", O3DSceneLoader::l_mesh<O3DCubeRenderer>);
    lua_register(L, "octa", O3DSceneLoader::l_mesh<O3DOctahedronRenderer>);
    lua_register(L, "quad", O3DSceneLoader::l_mesh<O3DQuadRenderer>);
    lua_register(L, "skybox", O3DSceneLoader::l_mesh<O3DSkyboxRenderer>);
    lua_register(L, "model", O3DSceneLoader::l_model);
    lua_register(L, "model_instance", O3DSceneLoader::l_modelInstance);
    lua_register(L, "dir_light", O3DSceneLoader::l_dirLight);
    lua_register(L, "spot_light", O3DSceneLoader::l_spotLight);
    lua_register(L, "point_light", O3DSceneLoader::l_pointLight);
    
    lua_register(L, "material", O3DSceneLoader::l_material);
    lua_register(L, "default_material", O3DSceneLoader::l_defaultMaterial);
    lua_register(L, "shader", O3DSceneLoader::l_shader);
    lua_register(L, "texture", O3DSceneLoader::l_texture);
    lua_register(L, "cubemap", O3DSceneLoader::l_cubemap);
    
    //Model modification
    lua_register(L, "set_model_material", O3DSceneLoader::l_setModelMaterial);
    
    //Object modification
    lua_register(L, "set_position", O3DSceneLoader::l_setPosition);
    lua_register(L, "set_scale", O3DSceneLoader::l_setScale);
    lua_register(L, "set_rotation", O3DSceneLoader::l_setRotation);
    lua_register(L, "set_local_position", O3DSceneLoader::l_setLocalPosition);
    lua_register(L, "set_local_scale", O3DSceneLoader::l_setLocalScale);
    lua_register(L, "set_local_rotation", O3DSceneLoader::l_setLocalRotation);
    lua_register(L, "set_parent", O3DSceneLoader::l_setParent);
    lua_register(L, "set_material", O3DSceneLoader::l_setMaterial);
    
    //Material modification
    lua_register(L, "set_mat_vec4", O3DSceneLoader::l_setMatVec4);
    lua_register(L, "set_mat_vec3", O3DSceneLoader::l_setMatVec3);
    lua_register(L, "set_mat_vec2", O3DSceneLoader::l_setMatVec2);
    lua_register(L, "set_mat_float", O3DSceneLoader::l_setMatFloat);
    lua_register(L, "set_mat_int", O3DSceneLoader::l_setMatInt);
    lua_register(L, "set_mat_texture", O3DSceneLoader::l_setMatTexture);
    lua_register(L, "set_mat_cubemap", O3DSceneLoader::l_setMatCubemap);
    
    //Light modification
    lua_register(L, "set_light_color", O3DSceneLoader::l_setLightColor);
    lua_register(L, "set_light_specular", O3DSceneLoader::l_setLightSpecular);
    lua_register(L, "set_light_angle", O3DSceneLoader::l_setLightAngle);
    lua_register(L, "set_light_range", O3DSceneLoader::l_setLightRange);
    lua_register(L, "set_light_intensity", O3DSceneLoader::l_setLightIntensity);
    lua_register(L, "set_light_shadows", O3DSceneLoader::l_setLightShadows);
    
    
    
    if(luaL_dofile(L, filename))
        std::cout << lua_tostring(L, -1) << std::endl;
    
    lua_close(L);
    
    if (active)
        O3DScene::setActiveScene(g_scene);
    
    g_lastobject = nullptr;
    g_lastmaterial = nullptr;
    
    return g_scene;
}

void O3DSceneLoader::addToScene(GameObject_ptr obj){
    g_lastobject = obj;
    g_scene->add(obj);
}


// ------------------------------------------------------------------
// ------------------------------------------------------------------ LUA functions
// ------------------------------------------------------------------

int O3DSceneLoader::l_void(lua_State* L){
    return 1;
}

int O3DSceneLoader::l_include(lua_State* L){
    const char* path = lua_tostring(L, 1);
    luaL_dofile(L, path);
    return 1;
}


// ---------------------------------
// ------ Object creation
// ---------------------------------

int O3DSceneLoader::l_defaultCamera(lua_State* L){
    const char* id = lua_tostring(L, 1);
    Camera_ptr cam = O3DScene::createCamera(id);
    g_scene->setActiveCamera(cam);
    addToScene(cam);
    return 1;
}

int O3DSceneLoader::l_node(lua_State* L){
    const char* id = lua_tostring(L, 1);
    GameObject_ptr go = O3DScene::createObject<O3DGameObject>(id);
    addToScene(go);
    return 1;
}

int O3DSceneLoader::l_model(lua_State* L){
    const char* id = lua_tostring(L, 1);
    const char* path = lua_tostring(L, 2);
    Model_ptr m = O3D().getResources().createModel(id, path);
    g_lastobject = m;
    return 1;
}

int O3DSceneLoader::l_modelInstance(lua_State* L){
    const char* id = lua_tostring(L, 1);
    const char* modelid = lua_tostring(L, 2);
    Model_ptr mi = O3D().getResources().getModel(modelid)->instantiate(id);
    addToScene(mi);
    return 1;
}


int O3DSceneLoader::l_dirLight(lua_State* L){
    const char* id = lua_tostring(L, 1);
    Light_ptr light = O3DScene::createObject<O3DLight>(id);
    g_scene->getLighting().addDirectionalLight(light);
    addToScene(light);
    return 1;
}

int O3DSceneLoader::l_spotLight(lua_State* L){
    const char* id = lua_tostring(L, 1);
    SpotLight_ptr light = O3DScene::createObject<O3DSpotLight>(id);
    g_scene->getLighting().addSpotLight(light);
    addToScene(light);
    return 1;
}

int O3DSceneLoader::l_pointLight(lua_State* L){
    const char* id = lua_tostring(L, 1);
    Light_ptr light = O3DScene::createObject<O3DLight>(id);
    g_scene->getLighting().addPointLight(light);
    addToScene(light);
    return 1;
}

int O3DSceneLoader::l_ambientLight(lua_State* L){
    glm::vec3 l = luawrapper::get_vec3(L);
    g_scene->getLighting().setAmbientLight(l);
    return 1;
}

int O3DSceneLoader::l_material(lua_State* L){
    const char* id = lua_tostring(L, 1);
    const char* shaderid = lua_tostring(L, 2);
    bool transparent = lua_toboolean(L, 3);
    
    Material_ptr m = O3D().getResources().createMaterial(id, shaderid, transparent);
    g_lastmaterial = m;
    return 1;
}

int O3DSceneLoader::l_defaultMaterial(lua_State* L){
    const char* id = lua_tostring(L, 1);
    bool transparent = lua_toboolean(L, 2);
    
    g_lastmaterial = O3D().getResources().createDefaultMaterial(id, transparent);
    return 1;
}

int O3DSceneLoader::l_shader(lua_State* L){
    const char* id = lua_tostring(L, 1);
    const char* frag = lua_tostring(L, 2);
    const char* vert = lua_tostring(L, 3);
    O3D().getResources().createShader(id, frag, vert);
    return 1;
}

int O3DSceneLoader::l_texture(lua_State* L){
    const char* id = lua_tostring(L, 1);
    const char* path = lua_tostring(L, 2);
    O3D().getResources().createTexture(id, path);
    return 1;
}

int O3DSceneLoader::l_cubemap(lua_State* L){
    const char* id = lua_tostring(L, 1);
    vector<string> textures;
    textures.push_back(lua_tostring(L, 2));
    textures.push_back(lua_tostring(L, 3));
    textures.push_back(lua_tostring(L, 4));
    textures.push_back(lua_tostring(L, 5));
    textures.push_back(lua_tostring(L, 6));
    textures.push_back(lua_tostring(L, 7));
    O3D().getResources().createCubemap(id, textures);
    return 1;
}


// ---------------------------------
// ------ Material modification
// ---------------------------------

int O3DSceneLoader::l_setMatVec4(lua_State* L){
    const char* att_id = lua_tostring(L, 1);
    lua_remove(L, 1);
    glm::vec4 v = luawrapper::get_vec4(L);
    g_lastmaterial->setVector4(att_id, v);
    return 1;
}

int O3DSceneLoader::l_setMatVec3(lua_State* L){
    const char* att_id = lua_tostring(L, 1);
    lua_remove(L, 1);
    glm::vec3 v = luawrapper::get_vec3(L);
    g_lastmaterial->setVector3(att_id, v);
    return 1;
}

int O3DSceneLoader::l_setMatVec2(lua_State* L){
    const char* att_id = lua_tostring(L, 1);
    lua_remove(L, 1);
    glm::vec2 v = luawrapper::get_vec2(L);
    g_lastmaterial->setVector2(att_id, v);
    return 1;
}

int O3DSceneLoader::l_setMatFloat(lua_State* L){
    const char* att_id = lua_tostring(L, 1);
    float f = lua_tonumber(L, 2);
    g_lastmaterial->setFloat(att_id, f);
    return 1;
}

int O3DSceneLoader::l_setMatInt(lua_State* L){
    const char* att_id = lua_tostring(L, 1);
    int n = (int)lua_tonumber(L, 2);
    g_lastmaterial->setFloat(att_id, n);
    return 1;
}

int O3DSceneLoader::l_setMatTexture(lua_State* L){
    const char* att_id = lua_tostring(L, 1);
    const char* texture_id = lua_tostring(L, 2);
    int index = (int)lua_tonumber(L, 3);
    Texture_ptr tex = O3D().getResources().getTexture(texture_id);
    g_lastmaterial->setTexture(att_id, tex, index);
    return 1;
}

int O3DSceneLoader::l_setMatCubemap(lua_State* L){
    const char* att_id = lua_tostring(L, 1);
    const char* map_id = lua_tostring(L, 2);
    int index = (int)lua_tonumber(L, 3);
    CubeMap_ptr tex = O3D().getResources().getCubemap(map_id);
    g_lastmaterial->setCubemap(att_id, tex, index);
    return 1;
}


// ---------------------------------
// ------ Object modification
// ---------------------------------

int O3DSceneLoader::l_setPosition(lua_State* L){
    g_lastobject->setPosition(luawrapper::get_vec3(L));
    return 1;
}

int O3DSceneLoader::l_setScale(lua_State* L){
    g_lastobject->setScale(luawrapper::get_vec3(L));
    return 1;
}

int O3DSceneLoader::l_setRotation(lua_State* L){
    g_lastobject->setRotation(luawrapper::get_vec3(L));
    return 1;
}


int O3DSceneLoader::l_setLocalPosition(lua_State* L){
    g_lastobject->setLocalPosition(luawrapper::get_vec3(L));
    return 1;
}

int O3DSceneLoader::l_setLocalScale(lua_State* L){
    g_lastobject->setLocalScale(luawrapper::get_vec3(L));
    return 1;
}

int O3DSceneLoader::l_setLocalRotation(lua_State* L){
    g_lastobject->setLocalRotation(luawrapper::get_vec3(L));
    return 1;
}

int O3DSceneLoader::l_setParent(lua_State* L){
    const char* id = lua_tostring(L, 1);
    g_lastobject->setParent(g_scene->getObjectById<O3DSceneNode>(id));
    return 1;
}

int O3DSceneLoader::l_setMaterial(lua_State *L){
    const char* id = lua_tostring(L, 1);
    if (GameObject_ptr go = dynamic_pointer_cast<O3DGameObject>(g_lastobject)){
        Material_ptr m = O3D().getResources().getMaterial(id);
        MeshRenderer_ptr r = go->getComponent<O3DMeshRenderer>();
        if (r != nullptr && m != nullptr){
            r->setMaterial(m);
            return 1;
        }else{
            return -1;
        }
    }
    return -1;
}

int O3DSceneLoader::l_setModelMaterial(lua_State *L){
    const char* model_id = lua_tostring(L, 1);
    const char* mat_id = lua_tostring(L, 2);
    if (Model_ptr model = std::dynamic_pointer_cast<O3DModel>(g_lastobject)){
        if(GameObject_ptr go = model->getSubModel(model_id)){
            Material_ptr m = O3D().getResources().getMaterial(mat_id);
            MeshRenderer_ptr r = go->getComponent<O3DMeshRenderer>();
            if (r != nullptr && m != nullptr){
                r->setMaterial(m);
                return 1;
            }else{
                return -1;
            }
        }
    }
    return -1;
}



// ---------------------------------
// ------ Light modification
// ---------------------------------

int O3DSceneLoader::l_setLightColor(lua_State* L){
    Light_ptr l = dynamic_pointer_cast<O3DLight>(g_lastobject);
    if (l == nullptr)
        throw("SceneLoader : Last created object is not a Light");
    l->setColor(luawrapper::get_vec3(L));
    return 1;
}

int O3DSceneLoader::l_setLightSpecular(lua_State* L){
    Light_ptr l = dynamic_pointer_cast<O3DLight>(g_lastobject);
    if (l == nullptr)
        throw("SceneLoader : Last created object is not a Light");
    glm::vec3 s = luawrapper::get_vec3(L);
    l->setSpecular(s);
    return 1;
}

int O3DSceneLoader::l_setLightAngle(lua_State* L){
    SpotLight_ptr l = dynamic_pointer_cast<O3DSpotLight>(g_lastobject);
    if (l == nullptr)
        throw("SceneLoader : Last created object is not a SpotLight");
    l->setAngle(lua_tonumber(L, 1));
    return 1;
}

int O3DSceneLoader::l_setLightRange(lua_State* L){
    Light_ptr l = dynamic_pointer_cast<O3DLight>(g_lastobject);
    if (l == nullptr)
        throw("SceneLoader : Last created object is not a Light");
    l->setRange(lua_tonumber(L, 1));
    return 1;
}
int O3DSceneLoader::l_setLightIntensity(lua_State* L){
    Light_ptr l = dynamic_pointer_cast<O3DLight>(g_lastobject);
    if (l == nullptr)
        throw("SceneLoader : Last created object is not a Light");
    l->setIntensity(lua_tonumber(L, 1));
    return 1;
}
int O3DSceneLoader::l_setLightShadows(lua_State* L){
    Light_ptr l = dynamic_pointer_cast<O3DLight>(g_lastobject);
    if (l == nullptr)
        throw("SceneLoader : Last created object is not a Light");
    
    
    ShadowEmitter emitter(luawrapper::pop_number(L,512));
    emitter.light = l;
    emitter.near = luawrapper::pop_number(L, 0.1);
    emitter.far = luawrapper::pop_number(L, 10);
    emitter.range = luawrapper::pop_number(L, 5);
    
    g_scene->getLighting().addShadowEmitter(emitter);
    return 1;
}

