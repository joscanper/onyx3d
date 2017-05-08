//
//  O3DMaterial.cpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 20/04/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#include "O3DMaterial.hpp"

using namespace o3d;

void O3DMaterial::use(){
    m_shader->use();
    
   
    for(auto p : m_properties){
        switch(p.second->type){
            case VEC4:
                m_shader->setUniform(("material." + p.first).c_str(), dynamic_pointer_cast<PropertyValue<glm::vec4>>(p.second)->value);
                break;
            case VEC3:
                m_shader->setUniform(("material." + p.first).c_str(), dynamic_pointer_cast<PropertyValue<glm::vec3>>(p.second)->value);
                break;
            case VEC2:
                m_shader->setUniform(("material." + p.first).c_str(), dynamic_pointer_cast<PropertyValue<glm::vec2>>(p.second)->value);
                break;
            case FLOAT:
                m_shader->setUniform(("material." + p.first).c_str(), dynamic_pointer_cast<PropertyValue<float>>(p.second)->value);
                break;
            case INT:
                m_shader->setUniform(("material." + p.first).c_str(), dynamic_pointer_cast<PropertyValue<int>>(p.second)->value);
                break;
            case TEXTURE:
            {
                std::shared_ptr<TexturePropertyValue<Texture_ptr>> tp = dynamic_pointer_cast<TexturePropertyValue<Texture_ptr>>(p.second);
                m_shader->setUniformTexture(("material." + p.first).c_str(), tp->texture->getTextureId(), tp->index);
                break;
            }
            case CUBEMAP:
            {
                std::shared_ptr<TexturePropertyValue<CubeMap_ptr>> tcp = dynamic_pointer_cast<TexturePropertyValue<CubeMap_ptr>>(p.second);
                m_shader->setUniformCubemap(("material." + p.first).c_str(), tcp->texture->getTextureId(), tcp->index);
                break;
            }
        }
        
    }
    
}
