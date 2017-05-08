//
//  O3DMeshRenderer.cpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 18/04/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#include "O3DCore.hpp"
#include "O3DMeshRenderer.hpp"
#include "O3DTransform.hpp"
#include "O3DCamera.hpp"
#include "O3DScene.hpp"
#include "O3DSpotLight.hpp"

#include <iostream>
#include <math.h>
#include <algorithm>
#include <string>

using namespace o3d;


O3DMeshRenderer::O3DMeshRenderer() :
    O3DRenderer(),
    m_mesh(std::make_shared<O3DMesh>())
{}



void O3DMeshRenderer::render(const glm::mat4& view, const glm::mat4& proj, const Shader_ptr& shader){
    
    setMVP(view, proj, shader);
    
    // -- TODO - Move this somewhere else where we set a UBO --------
    Scene_ptr   scene   = O3DScene::getActiveScene();
    Camera_ptr  camera  = scene->getActiveCamera();
    
    // Camera
    shader->setUniform("camera.direction", camera->getDirection());
    shader->setUniform("camera.position", camera->getPosition());
    
    // Lighting
    shader->setUniform("lighting_data.ambient", scene->getLighting().getAmbientLight());
    const std::vector<Light_ptr> dlights = scene->getLighting().getDirectionalLights();
    shader->setUniform("lighting_data.dirlightsnum", (GLint)dlights.size());
    for (int i=0; i < dlights.size(); ++i){
        Light_ptr l = dlights[i];
        std::string index = std::to_string(i);
        shader->setUniform(("lighting_data.directional["+index+"].direction").c_str(),l->getDirection());
        shader->setUniform(("lighting_data.directional["+index+"].color").c_str(), l->getColor());
        shader->setUniform(("lighting_data.directional["+index+"].specular").c_str(), l->getSpecular());
        shader->setUniform(("lighting_data.directional["+index+"].intensity").c_str(), l->getIntensity());
    }
    
    const std::vector<Light_ptr> plights = scene->getLighting().getPointLights();
    shader->setUniform("lighting_data.pointlightsnum", (GLint)plights.size());
    for (int i=0; i < plights.size(); ++i){
        Light_ptr l = plights[i];
        std::string index = std::to_string(i);
        
        shader->setUniform(("lighting_data.point["+index+"].position").c_str(),l->getPosition());
        shader->setUniform(("lighting_data.point["+index+"].color").c_str(), l->getColor());
        shader->setUniform(("lighting_data.point["+index+"].specular").c_str(), l->getSpecular());
        shader->setUniform(("lighting_data.point["+index+"].range").c_str(), l->getRange());
        shader->setUniform(("lighting_data.point["+index+"].intensity").c_str(), l->getIntensity());
    }
    
    const std::vector<SpotLight_ptr> slights = scene->getLighting().getSpotLights();
    shader->setUniform("lighting_data.spotlightsnum", (GLint)slights.size());
    for (int i=0; i < slights.size(); ++i){
        SpotLight_ptr l = slights[i];
        std::string index = std::to_string(i);
        shader->setUniform(("lighting_data.spot["+index+"].position").c_str(),l->getPosition());
        shader->setUniform(("lighting_data.spot["+index+"].direction").c_str(),l->getDirection());
        shader->setUniform(("lighting_data.spot["+index+"].angle").c_str(), l->getAngle());
        shader->setUniform(("lighting_data.spot["+index+"].color").c_str(), l->getColor());
        shader->setUniform(("lighting_data.spot["+index+"].specular").c_str(), l->getSpecular());
        shader->setUniform(("lighting_data.spot["+index+"].range").c_str(), l->getRange());
        shader->setUniform(("lighting_data.spot["+index+"].intensity").c_str(), l->getIntensity());
    }
    
    
    // -----------------------------------------------

    
    glBindVertexArray(m_mesh->vao);
    if (m_mesh->indices.size() > 0)
        glDrawElements(GL_TRIANGLES, (GLuint)m_mesh->indices.size(), GL_UNSIGNED_INT, 0);
    else
        glDrawArrays(GL_TRIANGLES, 0, (GLuint)m_mesh->vertices.size());
    glBindVertexArray(0);
}


