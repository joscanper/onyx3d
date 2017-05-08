//
//  O3DQuadRenderer.cpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 18/04/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#include "O3DQuadRenderer.hpp"

using namespace o3d;

O3DQuadRenderer::O3DQuadRenderer(float size) : O3DMeshRenderer(){
    glm::vec3 red(1,0,0);
    glm::vec3 green(0,1,0);
    m_mesh->vertices.push_back(O3DVertex(glm::vec3(-size,-size,0.0f),red,glm::vec3(0,0,1),glm::vec2(0,0))); //0
    m_mesh->vertices.push_back(O3DVertex(glm::vec3(size,-size,0.0f),red,glm::vec3(0,0,1),glm::vec2(1,0))); //1
    m_mesh->vertices.push_back(O3DVertex(glm::vec3(-size,size,0.0f),green,glm::vec3(0,0,1),glm::vec2(0,1))); //3
    
    m_mesh->vertices.push_back(O3DVertex(glm::vec3(size,-size,0.0f),red,glm::vec3(0,0,1),glm::vec2(1,0))); //1
    m_mesh->vertices.push_back(O3DVertex(glm::vec3(size,size,0.0f),green,glm::vec3(0,0,1),glm::vec2(1,1))); //2
    m_mesh->vertices.push_back(O3DVertex(glm::vec3(-size,size,0.0f),green,glm::vec3(0,0,1),glm::vec2(0,1))); //3
   
    m_mesh->calculateTangents();
    m_mesh->generateVAO();
}
