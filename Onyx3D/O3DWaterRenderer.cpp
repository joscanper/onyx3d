//
//  O3DWaterRenderer.cpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 16/05/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#include "O3DWaterRenderer.hpp"
#include "O3DCore.hpp"

using namespace o3d;

O3DWaterRenderer::O3DWaterRenderer() :
    O3DMeshRenderer(),
    m_specular(16.0f),
    m_waveStrength(0.01f),
    m_speed(0.1f),
    m_density(1),
    m_color(1,1,1)
{
    float sizex = 0.5f;
    float sizez = 0.5f;
    glm::vec3 white(1,1,1);
    
    /*
    float waveStrength = 0.005f;
    float speed = 0.05f;
    vec3 color = vec3(1,0.3,0.3);
    float density = 5.0f;
    float specularity = 15.0f;
    */
    
    m_mesh->vertices.push_back(O3DVertex(glm::vec3(-sizex,0.0f,-sizez),white,glm::vec3(0,1,0),glm::vec2(0,0)));
    m_mesh->vertices.push_back(O3DVertex(glm::vec3(-sizex,0.0f,sizez),white,glm::vec3(0,1,0),glm::vec2(0,1)));
    m_mesh->vertices.push_back(O3DVertex(glm::vec3(sizex,0.0f,-sizez),white,glm::vec3(0,1,0),glm::vec2(1,0)));
    
    
    m_mesh->vertices.push_back(O3DVertex(glm::vec3(sizex,0.0f,-sizez),white,glm::vec3(0,1,0),glm::vec2(1,0)));
    m_mesh->vertices.push_back(O3DVertex(glm::vec3(-sizex,0.0f,sizez),white,glm::vec3(0,1,0),glm::vec2(0,1)));
    m_mesh->vertices.push_back(O3DVertex(glm::vec3(sizex,0.0f,sizez),white,glm::vec3(0,1,0),glm::vec2(1,1)));
    
    m_mesh->calculateTangents();
    m_mesh->generateVAO();
    
    setMaterial(O3D().getResources().getMaterial("o3d_materials/water"));
}
                
void O3DWaterRenderer::initFBOs(int w, int h){
    reflection_fbo = std::make_shared<O3DFBO>(w,h);
    refraction_fbo = std::make_shared<O3DFBO>(w,h);
    
    reflection_fbo->addColorTexture();
    reflection_fbo->addDepthTexture();
    
    refraction_fbo->addColorTexture();
    refraction_fbo->addDepthTexture();
    
    reflection_fbo->checkStatus();
    refraction_fbo->checkStatus();
}

void O3DWaterRenderer::render(const glm::mat4& view, const glm::mat4& proj, const Shader_ptr& shader){
    
    shader->setUniformTexture("water.reflection", reflection_fbo->getColorTextureId(), 0);
    shader->setUniformTexture("water.refraction", refraction_fbo->getColorTextureId(), 1);
    shader->setUniformTexture("water.refractionDepth", refraction_fbo->getDepthTextureId(), 2);
    //shader->setUniform("time", O3D().getTime());
    
    shader->setUniform("water.specular", m_specular);
    shader->setUniform("water.speed", m_speed);
    shader->setUniform("water.waveStrength", m_waveStrength);
    shader->setUniform("water.density", m_density);
    shader->setUniform("water.color", m_color);
    shader->setUniform("water.tiling", m_tiling);
    
    O3DMeshRenderer::render(view, proj, shader);
    
}
