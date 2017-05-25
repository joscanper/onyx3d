//
//  O3DLuaLoader.cpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 14/05/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#include "O3DLuaLoader.hpp"
#include "O3DGridRenderer.hpp"
#include "O3DOctahedronRenderer.hpp"
#include "O3DWaterRenderer.hpp"

namespace o3d {
    namespace O3DLuaLoader{
        GameObject_ptr   g_lastobject;
        Scene_ptr        g_scene;
        Material_ptr     g_lastmaterial;
        Batch_ptr        g_batch;
        
        void clear(){
            g_lastobject = nullptr;
            g_scene = nullptr;
            g_lastmaterial = nullptr;
        }
        
        namespace Includer{
            
            int l_void(lua_State* L){
                return 1;
            }
            
            int l_include(lua_State* L){
                std::string path = O3D().getResources().getResourcesPath(lua_tostring(L, 1));
                std::cout << "Processing included file:" << path << std::endl;
                if (luaL_dofile(L, path.c_str()))
                    std::cout << "Error loading file: " << path << ":" << lua_tostring(L, -1) << std::endl;
                return 1;
            }
            
             void registerAll(lua_State* L, bool reload_includes){
                if (reload_includes)
                    lua_register(L, "include", l_include);
                else
                    lua_register(L, "include", l_void);
            }
        }
        
        namespace LighModificators{
            
            int l_setLightColor(lua_State* L){
                Light_ptr l = dynamic_pointer_cast<O3DLight>(g_lastobject);
                if (l == nullptr)
                    throw("LuaLoader :Last created object is not a Light");
                l->setColor(luawrapper::get_vec3(L));
                return 1;
            }
            
            int l_setLightSpecular(lua_State* L){
                Light_ptr l = dynamic_pointer_cast<O3DLight>(g_lastobject);
                if (l == nullptr)
                    throw("LuaLoader :Last created object is not a Light");
                glm::vec3 s = luawrapper::get_vec3(L);
                l->setSpecular(s);
                return 1;
            }
            
            int l_setLightAngle(lua_State* L){
                SpotLight_ptr l = dynamic_pointer_cast<O3DSpotLight>(g_lastobject);
                if (l == nullptr)
                    throw("LuaLoader :Last created object is not a SpotLight");
                l->setAngle(lua_tonumber(L, 1));
                return 1;
            }
            
            int l_setLightRange(lua_State* L){
                Light_ptr l = dynamic_pointer_cast<O3DLight>(g_lastobject);
                if (l == nullptr)
                    throw("LuaLoader :Last created object is not a Light");
                l->setRange(lua_tonumber(L, 1));
                return 1;
            }
            int l_setLightIntensity(lua_State* L){
                Light_ptr l = dynamic_pointer_cast<O3DLight>(g_lastobject);
                if (l == nullptr)
                    throw("LuaLoader :Last created object is not a Light");
                l->setIntensity(lua_tonumber(L, 1));
                return 1;
            }
            int l_setLightShadows(lua_State* L){
                Light_ptr l = dynamic_pointer_cast<O3DLight>(g_lastobject);
                if (l == nullptr)
                    throw("LuaLoader :Last created object is not a Light");
                
                
                ShadowEmitter emitter(luawrapper::pop_number(L,512));
                emitter.light = l;
                emitter.near = luawrapper::pop_number(L, 0.1);
                emitter.far = luawrapper::pop_number(L, 10);
                emitter.range = luawrapper::pop_number(L, 5);
                
                g_scene->getLighting().addShadowEmitter(emitter);
                return 1;
            }
            
             void registerAll(lua_State* L){
                //Light modification
                lua_register(L, "set_light_color", l_setLightColor);
                lua_register(L, "set_light_specular", l_setLightSpecular);
                lua_register(L, "set_light_angle", l_setLightAngle);
                lua_register(L, "set_light_range", l_setLightRange);
                lua_register(L, "set_light_intensity", l_setLightIntensity);
                lua_register(L, "set_light_shadows", l_setLightShadows);
            }
            
        }
        
        namespace MaterialDefiners{
            
            int l_material(lua_State* L){
                const char* id = lua_tostring(L, 1);
                const char* shaderid = lua_tostring(L, 2);
                const char* mode = lua_tostring(L, 3);
                
                MaterialRenderingMode mat_mode = O3DMaterial::getRenderingMode(mode);
                
                Material_ptr m = O3D().getResources().createMaterial(id, shaderid, mat_mode);
                g_lastmaterial = m;
                return 1;
            }
            
            int l_defaultMaterial(lua_State* L){
                const char* id = lua_tostring(L, 1);
                const char* mode = lua_tostring(L, 2);
                MaterialRenderingMode mat_mode = O3DMaterial::getRenderingMode(mode);
                g_lastmaterial = O3D().getResources().createDefaultMaterial(id, mat_mode);
                return 1;
            }
            
            int l_shader(lua_State* L){
                const char* id = lua_tostring(L, 1);
                const char* frag = lua_tostring(L, 2);
                const char* vert = lua_tostring(L, 3);
                O3D().getResources().createShader(id, frag, vert);
                return 1;
            }
            
            int l_texture(lua_State* L){
                const char* id = lua_tostring(L, 1);
                const char* path = lua_tostring(L, 2);
                O3D().getResources().createTexture(id, path);
                return 1;
            }
            
            int l_cubemap(lua_State* L){
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
            
            int l_getMaterial(lua_State* L){
                const char* id = lua_tostring(L, 1);
                g_lastmaterial = O3D().getResources().getMaterial(id);
                return 1;
            }
            
             void registerAll(lua_State* L){
                lua_register(L, "material", l_material);
                lua_register(L, "default_material", l_defaultMaterial);
                lua_register(L, "shader", l_shader);
                lua_register(L, "texture", l_texture);
                lua_register(L, "cubemap", l_cubemap);
                lua_register(L, "get_material", l_getMaterial);
            }
            
        }
        
        namespace MaterialModificators{
            
            int l_setMatVec4(lua_State* L){
                const char* att_id = lua_tostring(L, 1);
                lua_remove(L, 1);
                glm::vec4 v = luawrapper::get_vec4(L);
                g_lastmaterial->setVector4(att_id, v);
                return 1;
            }
            
            int l_setMatVec3(lua_State* L){
                const char* att_id = lua_tostring(L, 1);
                lua_remove(L, 1);
                glm::vec3 v = luawrapper::get_vec3(L);
                g_lastmaterial->setVector3(att_id, v);
                return 1;
            }
            
            int l_setMatVec2(lua_State* L){
                const char* att_id = lua_tostring(L, 1);
                lua_remove(L, 1);
                glm::vec2 v = luawrapper::get_vec2(L);
                g_lastmaterial->setVector2(att_id, v);
                return 1;
            }
            
            int l_setMatFloat(lua_State* L){
                const char* att_id = lua_tostring(L, 1);
                float f = lua_tonumber(L, 2);
                g_lastmaterial->setFloat(att_id, f);
                return 1;
            }
            
            int l_setMatInt(lua_State* L){
                const char* att_id = lua_tostring(L, 1);
                int n = (int)lua_tonumber(L, 2);
                g_lastmaterial->setFloat(att_id, n);
                return 1;
            }
            
            int l_setMatTexture(lua_State* L){
                const char* att_id = lua_tostring(L, 1);
                const char* texture_id = lua_tostring(L, 2);
                int index = (int)lua_tonumber(L, 3);
                Texture_ptr tex = O3D().getResources().getTexture(texture_id);
                g_lastmaterial->setTexture(att_id, tex, index);
                return 1;
            }
            
            int l_setMatCubemap(lua_State* L){
                const char* att_id = lua_tostring(L, 1);
                const char* map_id = lua_tostring(L, 2);
                int index = (int)lua_tonumber(L, 3);
                CubeMap_ptr tex = O3D().getResources().getCubemap(map_id);
                g_lastmaterial->setCubemap(att_id, tex, index);
                return 1;
            }
            
            int l_setMatShader(lua_State* L){
                const char* shader_id = lua_tostring(L, 1);
                Shader_ptr shader = O3D().getResources().getShader(shader_id);
                g_lastmaterial->setShader(shader);
                return 1;
            }
             void registerAll(lua_State* L){
                lua_register(L, "set_mat_vec4", l_setMatVec4);
                lua_register(L, "set_mat_vec3", l_setMatVec3);
                lua_register(L, "set_mat_vec2", l_setMatVec2);
                lua_register(L, "set_mat_float", l_setMatFloat);
                lua_register(L, "set_mat_int", l_setMatInt);
                lua_register(L, "set_mat_texture", l_setMatTexture);
                lua_register(L, "set_mat_cubemap", l_setMatCubemap);
                lua_register(L, "set_mat_shader", l_setMatShader);
            }
        };
        
        namespace ObjectDefiners{
            void addToScene(GameObject_ptr obj){
                g_lastobject = obj;
                if (g_batch == nullptr)
                    g_scene->add(obj);
                else
                    g_batch->add(obj);
            }
            
            int l_defaultCamera(lua_State* L){
                const char* id = lua_tostring(L, 1);
                Camera_ptr cam = O3DScene::createCamera(id);
                g_scene->setActiveCamera(cam);
                addToScene(cam);
                return 1;
            }
            
            int l_node(lua_State* L){
                const char* id = lua_tostring(L, 1);
                GameObject_ptr go = O3DScene::createObject<O3DGameObject>(id);
                addToScene(go);
                return 1;
            }
            
            int l_model(lua_State* L){
                const char* id = lua_tostring(L, 1);
                const char* path = lua_tostring(L, 2);
                Model_ptr m = O3D().getResources().createModel(id, path);
                g_lastobject = m;
                return 1;
            }
            
            int l_modelInstance(lua_State* L){
                const char* id = lua_tostring(L, 1);
                const char* modelid = lua_tostring(L, 2);
                Model_ptr mi = O3D().getResources().getModel(modelid)->instantiate(id);
                addToScene(mi);
                return 1;
            }
            
            
            int l_dirLight(lua_State* L){
                const char* id = lua_tostring(L, 1);
                Light_ptr light = O3DScene::createObject<O3DLight>(id);
                g_scene->getLighting().addDirectionalLight(light);
                addToScene(light);
                return 1;
            }
            
            int l_spotLight(lua_State* L){
                const char* id = lua_tostring(L, 1);
                SpotLight_ptr light = O3DScene::createObject<O3DSpotLight>(id);
                g_scene->getLighting().addSpotLight(light);
                addToScene(light);
                return 1;
            }
            
            int l_pointLight(lua_State* L){
                const char* id = lua_tostring(L, 1);
                Light_ptr light = O3DScene::createObject<O3DLight>(id);
                g_scene->getLighting().addPointLight(light);
                addToScene(light);
                return 1;
            }
            
            int l_ambientLight(lua_State* L){
                glm::vec3 l = luawrapper::get_vec3(L);
                g_scene->getLighting().setAmbientLight(l);
                return 1;
            }
            
            int l_water(lua_State* L){
                const char* id = luawrapper::pop_string(L, "");
                int w = luawrapper::pop_number(L, 512);
                int h = luawrapper::pop_number(L, 512);
                GameObject_ptr go = O3DScene::createObject<O3DGameObject>(id);
                addToScene(go);
                
                WaterRenderer_ptr m = make_shared<O3DWaterRenderer>();
                m->initFBOs(w, h);
                go->addComponent(m);
                
                
                return 1;
            }
            
            int l_getModel(lua_State* L){
                const char* id = luawrapper::pop_string(L, "");
                g_lastobject = O3D().getResources().getModel(id);
                return 1;
            }
            
             void registerAll(lua_State* L){
                lua_register(L, "ambient_light", l_ambientLight);
                lua_register(L, "default_camera", l_defaultCamera);
                lua_register(L, "node", l_node);
                lua_register(L, "grid", l_mesh<O3DGridRenderer>);
                lua_register(L, "cube", l_mesh<O3DCubeRenderer>);
                lua_register(L, "octa", l_mesh<O3DOctahedronRenderer>);
                lua_register(L, "quad", l_mesh<O3DQuadRenderer>);
                lua_register(L, "skybox", l_mesh<O3DSkyboxRenderer>);
                lua_register(L, "water", l_water);
                lua_register(L, "model", l_model);
                lua_register(L, "model_instance", l_modelInstance);
                lua_register(L, "dir_light", l_dirLight);
                lua_register(L, "spot_light", l_spotLight);
                lua_register(L, "point_light", l_pointLight);
                 lua_register(L, "get_model", l_getModel);
            }
        };
        
        namespace ObjectModificators{
            
            
             int l_setPosition(lua_State* L){
                g_lastobject->setPosition(luawrapper::get_vec3(L));
                return 1;
            }
            
             int l_setScale(lua_State* L){
                g_lastobject->setScale(luawrapper::get_vec3(L));
                return 1;
            }
            
             int l_setRotation(lua_State* L){
                g_lastobject->setRotation(luawrapper::get_vec3(L));
                return 1;
            }
            
            
             int l_setLocalPosition(lua_State* L){
                g_lastobject->setLocalPosition(luawrapper::get_vec3(L));
                return 1;
            }
            
             int l_setLocalScale(lua_State* L){
                g_lastobject->setLocalScale(luawrapper::get_vec3(L));
                return 1;
            }
            
             int l_setLocalRotation(lua_State* L){
                g_lastobject->setLocalRotation(luawrapper::get_vec3(L));
                return 1;
            }
            
             int l_setParent(lua_State* L){
                const char* id = lua_tostring(L, 1);
                g_lastobject->setParent(g_scene->getObjectById<O3DSceneNode>(id));
                return 1;
            }
            
             int l_setMaterial(lua_State *L){
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
            
            int l_setModelMaterial(lua_State *L){
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
                    }else{
                        std::cout << "LuaLoader : Model has no submodel with id: " << model_id << std::endl;
                    }
                }
                return 1;
            }
            
             void registerAll(lua_State* L){
                lua_register(L, "set_position", l_setPosition);
                lua_register(L, "set_scale", l_setScale);
                lua_register(L, "set_rotation", l_setRotation);
                lua_register(L, "set_local_position", l_setLocalPosition);
                lua_register(L, "set_local_scale", l_setLocalScale);
                lua_register(L, "set_local_rotation", l_setLocalRotation);
                lua_register(L, "set_parent", l_setParent);
                lua_register(L, "set_material", l_setMaterial);
                lua_register(L, "set_model_material", l_setModelMaterial);
            }
        };
        
        namespace WaterModificators{
            int l_setWaterWaveStrength(lua_State* L){
                float strength = luawrapper::pop_number(L, 0.5f);
                WaterRenderer_ptr wr = g_lastobject->getComponent<O3DWaterRenderer>();
                if (wr == nullptr)
                    throw("LuaLoader :Last created object is not Water");
                
                wr->setWaveStrength(strength);
                return 1;
            }
            
            int l_setWaterSpeed(lua_State* L){
                float speed = luawrapper::pop_number(L, 0.01f);
                WaterRenderer_ptr wr = g_lastobject->getComponent<O3DWaterRenderer>();
                if (wr == nullptr)
                    throw("LuaLoader :Last created object is not Water");
                
                wr->setSpeed(speed);
                return 1;
            }

            int l_setWaterColor(lua_State* L){
                glm::vec3 col = luawrapper::get_vec3(L);
                WaterRenderer_ptr wr = g_lastobject->getComponent<O3DWaterRenderer>();
                if (wr == nullptr)
                    throw("LuaLoader :Last created object is not Water");
                
                wr->setColor(col);
                return 1;
            }

            int l_setWaterDensity(lua_State* L){
                float d = luawrapper::pop_number(L, 1);
                WaterRenderer_ptr wr = g_lastobject->getComponent<O3DWaterRenderer>();
                if (wr == nullptr)
                    throw("LuaLoader :Last created object is not Water");
                
                wr->setDensity(d);
                return 1;
            }

            int l_setWaterSpecular(lua_State* L){
                float spec = luawrapper::pop_number(L, 16);
                WaterRenderer_ptr wr = g_lastobject->getComponent<O3DWaterRenderer>();
                if (wr == nullptr)
                    throw("LuaLoader :Last created object is not Water");
                
                wr->setSpecular(spec);
                return 1;
            }

            
            void registerAll(lua_State* L){
                lua_register(L, "set_water_wave_strength", l_setWaterWaveStrength);
                lua_register(L, "set_water_speed", l_setWaterSpeed);
                lua_register(L, "set_water_color", l_setWaterColor);
                lua_register(L, "set_water_density", l_setWaterDensity);
                lua_register(L, "set_water_specular", l_setWaterSpecular);
            }
        }
        
        namespace UIDefiners{
            
            int l_text(lua_State* L){
                const char* id = luawrapper::pop_string(L, "");
                const char* text = luawrapper::pop_string(L, "");
                int x = luawrapper::pop_number(L, 0);
                int y = luawrapper::pop_number(L, 0);
                int w = luawrapper::pop_number(L, 0);
                int h = luawrapper::pop_number(L, 0);
                
                g_lastobject = O3D().getUI().createText(id,text,x,y,w,h);
                return 1;
            }
            
            int l_font(lua_State* L){
                const char* id = lua_tostring(L, 1);
                const char* path = lua_tostring(L, 2);
                O3D().getResources().createFont(id, path);
                return 1;
            }
            
            int l_draw(lua_State* L){
                const char* id = luawrapper::pop_string(L, "");
                const char* texture = luawrapper::pop_string(L, "");
                int x = luawrapper::pop_number(L, 0);
                int y = luawrapper::pop_number(L, 0);
                int w = luawrapper::pop_number(L, 0);
                int h = luawrapper::pop_number(L, 0);
                
                g_lastobject = O3D().getUI().createDraw(id,texture,x,y,w,h);
                return 1;
            }
            
            void registerAll(lua_State* L){
                lua_register(L, "draw", l_draw);
                lua_register(L, "font", l_font);
                lua_register(L, "text", l_text);
            }
        }
        
        namespace UIModificators{
            int l_setColor(lua_State* L){
                UIRect_ptr l = dynamic_pointer_cast<O3DUIRect>(g_lastobject);
                if (l == nullptr)
                    throw("LuaLoader : Last created object is not a UI item");
                
                glm::vec4 col = luawrapper::get_vec4(L);
                l->setColor(col);
                return 1;
            }
            
            void registerAll(lua_State* L){
                lua_register(L, "set_color", l_setColor);
            }
        }
        
        namespace RenderOperators{
            int l_startBatch(lua_State* L){
                const char* id = luawrapper::pop_string(L, "");
                const char* mat_id = luawrapper::pop_string(L, "o3d_materials/default");
                
                g_batch = std::make_shared<O3DBatch>(id);
                g_batch->setMaterial(O3D().getResources().getMaterial(mat_id));
                
                return 1;
            }
            
            int l_endBatch(lua_State* L){
                GameObject_ptr go = g_batch->generate();
                g_batch = nullptr;
                ObjectDefiners::addToScene(go);
                
                return 1;
            }
            
            void registerAll(lua_State* L){
                lua_register(L, "start_batch", l_startBatch);
                lua_register(L, "end_batch", l_endBatch);
            }
        }
        
    };
    
    
}
