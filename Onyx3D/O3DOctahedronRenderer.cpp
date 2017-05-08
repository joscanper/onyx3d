//
//  O3DOctahedronRenderer.cpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 22/04/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#include "O3DOctahedronRenderer.hpp"

using namespace o3d;

O3DOctahedronRenderer::O3DOctahedronRenderer() : O3DMeshRenderer(){
    
    glm::vec3 white(1,1,1);
    m_mesh->vertices.push_back(O3DVertex(glm::vec3(0,-0.5f,0.0f), white, glm::vec3(0,-1,0)));
    m_mesh->vertices.push_back(O3DVertex(glm::vec3(-0.5f,0,0.0f), white, glm::vec3(-1,0,0)));
    m_mesh->vertices.push_back(O3DVertex(glm::vec3(0.5f,0,0.0f), white, glm::vec3(1,0,0)));
    m_mesh->vertices.push_back(O3DVertex(glm::vec3(0,0,-0.5f), white, glm::vec3(0,0,-1)));
    m_mesh->vertices.push_back(O3DVertex(glm::vec3(0,0,0.5f), white, glm::vec3(0,0,1)));
    m_mesh->vertices.push_back(O3DVertex(glm::vec3(0,0.5f,0.0f), white, glm::vec3(0,1,0)));
    
    m_mesh->indices.push_back(0);
    m_mesh->indices.push_back(1);
    m_mesh->indices.push_back(3);
    
    m_mesh->indices.push_back(0);
    m_mesh->indices.push_back(3);
    m_mesh->indices.push_back(2);
    
    
    m_mesh->indices.push_back(0);
    m_mesh->indices.push_back(2);
    m_mesh->indices.push_back(4);
    
    m_mesh->indices.push_back(0);
    m_mesh->indices.push_back(4);
    m_mesh->indices.push_back(1);
    
    m_mesh->indices.push_back(1);
    m_mesh->indices.push_back(4);
    m_mesh->indices.push_back(5);
    
    m_mesh->indices.push_back(4);
    m_mesh->indices.push_back(2);
    m_mesh->indices.push_back(5);
    
    m_mesh->indices.push_back(2);
    m_mesh->indices.push_back(3);
    m_mesh->indices.push_back(5);
    
    m_mesh->indices.push_back(3);
    m_mesh->indices.push_back(1);
    m_mesh->indices.push_back(5);
    
    m_mesh->calculateTangents();
    m_mesh->generateVAO();
}
