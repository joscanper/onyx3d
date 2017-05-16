//
//  O3DResources.hpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 23/04/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#ifndef O3DResources_hpp
#define O3DResources_hpp

#include "O3DModel.hpp"
#include "O3DMaterial.hpp"
#include "O3DDefaultMaterial.hpp"
#include "O3DFont.hpp"

#include <string>
#include <unordered_map>



namespace o3d{
class O3DResources {
    public:
    
        void init();
    
        void addShader(const char* id, Shader_ptr s){ m_shaders[id] = s; }
        void addMaterial(const char* id, Material_ptr mat){ m_materials[id] = mat; }
        void addTexture(const char* id, Texture_ptr tex){ m_textures[id] = tex; }
        void addCubemap(const char* id, CubeMap_ptr tex){ m_cubemaps[id] = tex; }
        void addFont(const char* id, Font_ptr f){ m_fonts[id] = f; }
    
    
        Shader_ptr getShader(const char* id){
            if (m_shaders.find(id) == m_shaders.end())
                throw(("Resources : Trying to get undefined shader with id : " + std::string(id)).c_str());
            return m_shaders[id];
        }
        Material_ptr getMaterial(const char* id){
            if (m_materials.find(id) == m_materials.end())
                throw(("Resources : Trying to get undefined material with id : " + std::string(id)).c_str());
            return m_materials[id];
        }
        Texture_ptr getTexture(const char* id){
            if (m_textures.find(id) == m_textures.end())
                throw(("Resources : Trying to get undefined texture with id : " + std::string(id)).c_str());
            return m_textures[id];
        }
        CubeMap_ptr getCubemap(const char* id){
            if (m_cubemaps.find(id) == m_cubemaps.end())
                throw(("Resources : Trying to get undefined cubemap with id : " + std::string(id)).c_str());
            return m_cubemaps[id];
        }
        Font_ptr getFont(const char* id){
            if (m_fonts.find(id) == m_fonts.end())
                throw(("Resources : Trying to get undefined cubemap with id : " + std::string(id)).c_str());
            return m_fonts[id];
        }
    
    
    
    
        Shader_ptr createShader(const char* id, const char *frag, const char* vert){
            Shader_ptr s = std::make_shared<O3DShader>(getResourcesPath(frag).c_str(),getResourcesPath(vert).c_str());
            m_shaders[id] = s;
            return s;
        }
        Material_ptr createMaterial(const char *id, const char* shaderid, MaterialRenderingMode mode = MaterialRenderingMode::Opaque){
            Shader_ptr s = getShader(shaderid);
            
            Material_ptr mat = std::make_shared<O3DMaterial>(s, mode);
            m_materials[id] = mat;
            return mat;
        }
        DefaultMaterial_ptr createDefaultMaterial(const char *id, MaterialRenderingMode mode){
            std::shared_ptr<O3DDefaultMaterial> mat = std::make_shared<O3DDefaultMaterial>(mode);
            m_materials[id] = mat;
            return mat;
        }
        Texture_ptr createTexture(const char *id, const char* path){
            Texture_ptr t = std::make_shared<O3DTexture>(getResourcesPath(path).c_str());
            m_textures[id] = t;
            return t;
        }
        CubeMap_ptr createCubemap(const char *id, vector<string> paths){
            for (auto s : paths)
                s = getResourcesPath(s);
            CubeMap_ptr t = std::make_shared<O3DCubeMap>(paths);
            m_cubemaps[id] = t;
            return t;
        }
        Font_ptr createFont(const char *id, const char* path){
            
            Font_ptr f = std::make_shared<O3DFont>(getResourcesPath(path).c_str());
            m_fonts[id] = f;
            return f;
        }
    
        void addModel(const char* id, Model_ptr model){ m_models[id] = model; }
        Model_ptr createModel(const char *id, const char* path){
            Model_ptr t = std::make_shared<O3DModel>(id);
            t->load(path);
            m_models[id] = t;
            return t;
        }
        Model_ptr getModel(const char* id){
            if (m_models.find(id) == m_models.end())
                throw(("Resources : Trying to get undefined model with id : " + std::string(id)).c_str());
            return m_models[id];
        }
    
        DefaultMaterial_ptr getDefaultMaterial(){ return m_default_mat; }
    
        std::string getResourcesPath(std::string path){
            return "../../../../../../Onyx3D/" + path;
        }
    
        void reloadDefaultShader(){
            createShader("o3d_shaders/default", "resources/shaders/default.vert","resources/shaders/default.frag");
        }
    
    private:
        DefaultMaterial_ptr m_default_mat;
    
        std::unordered_map<std::string, Material_ptr> m_materials;
        std::unordered_map<std::string, Shader_ptr> m_shaders;
        std::unordered_map<std::string, Texture_ptr> m_textures;
        std::unordered_map<std::string, Model_ptr> m_models;
        std::unordered_map<std::string, CubeMap_ptr> m_cubemaps;
        std::unordered_map<std::string, Font_ptr> m_fonts;
    };
}

#endif /* O3DResources_hpp */
