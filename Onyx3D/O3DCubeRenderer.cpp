//
//  O3DCubeRenderer.cpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 20/04/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#include "O3DCubeRenderer.hpp"

using namespace o3d;

O3DCubeRenderer::O3DCubeRenderer() : O3DMeshRenderer(){
    glm::vec3 red(1,0,0);
    glm::vec3 green(0,1,0);
    glm::vec3 purple(1,0,1);
    glm::vec3 yellow(1,1,0);
    glm::vec3 white(1,1,1);
    glm::vec3 black(0.9f,0.9f,0.9f);
    
    //Back
    glm::vec3 n(0,0,-1);
    m_mesh->vertices.push_back(O3DVertex(glm::vec3(-0.5f,0.5f,-0.5f),red,n,glm::vec2(0,1)));
    m_mesh->vertices.push_back(O3DVertex(glm::vec3(0.5f,-0.5f,-0.5f),red,n,glm::vec2(1,0)));
    m_mesh->vertices.push_back(O3DVertex(glm::vec3(-0.5f,-0.5f,-0.5f),red,n,glm::vec2(0,0)));
    
    m_mesh->vertices.push_back(O3DVertex(glm::vec3(-0.5f,0.5f,-0.5f),red,n,glm::vec2(0,1)));
    m_mesh->vertices.push_back(O3DVertex(glm::vec3(0.5f,0.5f,-0.5f),red,n,glm::vec2(1,1)));
    m_mesh->vertices.push_back(O3DVertex(glm::vec3(0.5f,-0.5f,-0.5f),red,n,glm::vec2(1,0)));
    
    //Front
    n = glm::vec3(0,0,1);
    m_mesh->vertices.push_back(O3DVertex(glm::vec3(-0.5f,-0.5f,0.5f),green,n,glm::vec2(0,0)));
    m_mesh->vertices.push_back(O3DVertex(glm::vec3(0.5f,-0.5f,0.5f),green,n,glm::vec2(1,0)));
    m_mesh->vertices.push_back(O3DVertex(glm::vec3(-0.5f,0.5f,0.5f),green,n,glm::vec2(0,1)));
    m_mesh->vertices.push_back(O3DVertex(glm::vec3(0.5f,-0.5f,0.5f),green,n,glm::vec2(1,0)));
    m_mesh->vertices.push_back(O3DVertex(glm::vec3(0.5f,0.5f,0.5f),green,n,glm::vec2(1,1)));
    m_mesh->vertices.push_back(O3DVertex(glm::vec3(-0.5f,0.5f,0.5f),green,n,glm::vec2(0,1)));
    
    //Left
    n = glm::vec3(-1,0,0);
    m_mesh->vertices.push_back(O3DVertex(glm::vec3(-0.5f,-0.5f,-0.5f),purple,n,glm::vec2(1,0)));
    m_mesh->vertices.push_back(O3DVertex(glm::vec3(-0.5f,-0.5f,0.5f),purple,n,glm::vec2(0,0)));
    m_mesh->vertices.push_back(O3DVertex(glm::vec3(-0.5f,0.5f,0.5f),purple,n,glm::vec2(0,1)));
    m_mesh->vertices.push_back(O3DVertex(glm::vec3(-0.5f,-0.5f,-0.5f),purple,n,glm::vec2(1,0)));
    m_mesh->vertices.push_back(O3DVertex(glm::vec3(-0.5f,0.5f,0.5f),purple,n,glm::vec2(0,1)));
    m_mesh->vertices.push_back(O3DVertex(glm::vec3(-0.5f,0.5f,-0.5f),purple,n,glm::vec2(1,1)));
    
    
    //Right
    n = glm::vec3(1,0,0);
    m_mesh->vertices.push_back(O3DVertex(glm::vec3(0.5f,-0.5f,0.5f),yellow,n,glm::vec2(0,0)));
    m_mesh->vertices.push_back(O3DVertex(glm::vec3(0.5f,-0.5f,-0.5f),yellow,n,glm::vec2(1,0)));
    m_mesh->vertices.push_back(O3DVertex(glm::vec3(0.5f,0.5f,0.5f),yellow,n,glm::vec2(0,1)));
    m_mesh->vertices.push_back(O3DVertex(glm::vec3(0.5f,-0.5f,-0.5f),yellow,n,glm::vec2(1,0)));
    m_mesh->vertices.push_back(O3DVertex(glm::vec3(0.5f,0.5f,-0.5f),yellow,n,glm::vec2(1,1)));
    m_mesh->vertices.push_back(O3DVertex(glm::vec3(0.5f,0.5f,0.5f),yellow,n,glm::vec2(0,1)));
    
    // Down
    n = glm::vec3(0,-1,0);
    m_mesh->vertices.push_back(O3DVertex(glm::vec3(0.5f,-0.5f,0.5f),white,n,glm::vec2(1,1)));
    m_mesh->vertices.push_back(O3DVertex(glm::vec3(-0.5f,-0.5f,0.5f),white,n,glm::vec2(0,1)));
    m_mesh->vertices.push_back(O3DVertex(glm::vec3(-0.5f,-0.5f,-0.5f),white,n,glm::vec2(0,0)));
    
    m_mesh->vertices.push_back(O3DVertex(glm::vec3(0.5f,-0.5f,-0.5f),white,n,glm::vec2(1,0)));
    m_mesh->vertices.push_back(O3DVertex(glm::vec3(0.5f,-0.5f,0.5f),white,n,glm::vec2(1,1)));
    m_mesh->vertices.push_back(O3DVertex(glm::vec3(-0.5f,-0.5f,-0.5f),white,n,glm::vec2(0,0)));
    
    // Top
    n = glm::vec3(0,1,0);
    m_mesh->vertices.push_back(O3DVertex(glm::vec3(-0.5f,0.5f,-0.5f),black,n,glm::vec2(0,0)));
    m_mesh->vertices.push_back(O3DVertex(glm::vec3(-0.5f,0.5f,0.5f),black,n,glm::vec2(0,1)));
    m_mesh->vertices.push_back(O3DVertex(glm::vec3(0.5f,0.5f,0.5f),black,n,glm::vec2(1,1)));
    m_mesh->vertices.push_back(O3DVertex(glm::vec3(-0.5f,0.5f,-0.5f),black,n,glm::vec2(0,0)));
    m_mesh->vertices.push_back(O3DVertex(glm::vec3(0.5f,0.5f,0.5f),black,n,glm::vec2(1,1)));
    m_mesh->vertices.push_back(O3DVertex(glm::vec3(0.5f,0.5f,-0.5f),black,n,glm::vec2(1,0)));
    
    m_mesh->calculateTangents();
    m_mesh->generateVAO();
}
