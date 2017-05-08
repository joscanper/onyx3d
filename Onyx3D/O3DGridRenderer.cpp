//
//  O3DGridRenderer.cpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 22/04/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#include "O3DGridRenderer.hpp"

using namespace o3d;

O3DGridRenderer::O3DGridRenderer() : O3DMeshRenderer(){
    initGrid(1,1,10,10);
};

O3DGridRenderer::O3DGridRenderer(int cellsizex, int cellsizey, int cellnumx, int cellnumy) : O3DMeshRenderer(){
    initGrid(cellsizex, cellsizey, cellnumx, cellnumy);
}

void O3DGridRenderer::initGrid(int cellsizex, int cellsizey, int cellnumx, int cellnumy){
    for (int i=0; i <= cellnumx; i++){
        m_mesh->vertices.push_back(O3DVertex(glm::vec3(i*cellsizex,0,0)));
        m_mesh->vertices.push_back(O3DVertex(glm::vec3(i*cellsizex,0,cellnumx*cellsizey)));
    }
    
    for (int j=0; j <= cellnumy; j++){
        m_mesh->vertices.push_back(O3DVertex(glm::vec3(0,0,j*cellsizey)));
        m_mesh->vertices.push_back(O3DVertex(glm::vec3(cellnumx*cellsizex,0,j*cellsizey)));
    }
    
    m_mesh->generateVAO();
}

void O3DGridRenderer::render(const glm::mat4& view, const glm::mat4& proj, const Shader_ptr& shader){
    setMVP(view,proj,shader);
    
    glBindVertexArray(m_mesh->vao);
    glDrawArrays(GL_LINES, 0, (GLuint)m_mesh->vertices.size());
    glBindVertexArray(0);
}
