//
//  O3DSkyboxRenderer.hpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 26/04/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#ifndef O3DSkyboxRenderer_hpp
#define O3DSkyboxRenderer_hpp

#include "O3DDefines.hpp"
#include "O3DScene.hpp"
#include "O3DSkyRenderer.hpp"

namespace o3d {
    DEFINE_CLASS_PTR(O3DSkyboxRenderer, SkyboxRenderer)
    
    class O3DSkyboxRenderer : public O3DSkyRenderer{
    public:
        O3DSkyboxRenderer() : O3DSkyRenderer(){};
        
        void generateSkyGeometry() override{
            glm::vec3 white(1,1,1);
            
            //Back
            glm::vec3 n(0,0,-1);
            m_mesh->vertices.push_back(O3DVertex(glm::vec3(-0.5f,0.5f,-0.5f),white,n,glm::vec2(0,1)));
            m_mesh->vertices.push_back(O3DVertex(glm::vec3(0.5f,-0.5f,-0.5f),white,n,glm::vec2(1,0)));
            m_mesh->vertices.push_back(O3DVertex(glm::vec3(-0.5f,-0.5f,-0.5f),white,n,glm::vec2(0,0)));
            
            m_mesh->vertices.push_back(O3DVertex(glm::vec3(-0.5f,0.5f,-0.5f),white,n,glm::vec2(0,1)));
            m_mesh->vertices.push_back(O3DVertex(glm::vec3(0.5f,0.5f,-0.5f),white,n,glm::vec2(1,1)));
            m_mesh->vertices.push_back(O3DVertex(glm::vec3(0.5f,-0.5f,-0.5f),white,n,glm::vec2(1,0)));
            
            //Front
            n = glm::vec3(0,0,1);
            m_mesh->vertices.push_back(O3DVertex(glm::vec3(-0.5f,-0.5f,0.5f),white,n,glm::vec2(0,0)));
            m_mesh->vertices.push_back(O3DVertex(glm::vec3(0.5f,-0.5f,0.5f),white,n,glm::vec2(1,0)));
            m_mesh->vertices.push_back(O3DVertex(glm::vec3(-0.5f,0.5f,0.5f),white,n,glm::vec2(0,1)));
            m_mesh->vertices.push_back(O3DVertex(glm::vec3(0.5f,-0.5f,0.5f),white,n,glm::vec2(1,0)));
            m_mesh->vertices.push_back(O3DVertex(glm::vec3(0.5f,0.5f,0.5f),white,n,glm::vec2(1,1)));
            m_mesh->vertices.push_back(O3DVertex(glm::vec3(-0.5f,0.5f,0.5f),white,n,glm::vec2(0,1)));
            
            //Left
            n = glm::vec3(-1,0,0);
            m_mesh->vertices.push_back(O3DVertex(glm::vec3(-0.5f,-0.5f,-0.5f),white,n,glm::vec2(1,0)));
            m_mesh->vertices.push_back(O3DVertex(glm::vec3(-0.5f,-0.5f,0.5f),white,n,glm::vec2(0,0)));
            m_mesh->vertices.push_back(O3DVertex(glm::vec3(-0.5f,0.5f,0.5f),white,n,glm::vec2(0,1)));
            m_mesh->vertices.push_back(O3DVertex(glm::vec3(-0.5f,-0.5f,-0.5f),white,n,glm::vec2(1,0)));
            m_mesh->vertices.push_back(O3DVertex(glm::vec3(-0.5f,0.5f,0.5f),white,n,glm::vec2(0,1)));
            m_mesh->vertices.push_back(O3DVertex(glm::vec3(-0.5f,0.5f,-0.5f),white,n,glm::vec2(1,1)));
            
            
            //Right
            n = glm::vec3(1,0,0);
            m_mesh->vertices.push_back(O3DVertex(glm::vec3(0.5f,-0.5f,0.5f),white,n,glm::vec2(0,0)));
            m_mesh->vertices.push_back(O3DVertex(glm::vec3(0.5f,-0.5f,-0.5f),white,n,glm::vec2(1,0)));
            m_mesh->vertices.push_back(O3DVertex(glm::vec3(0.5f,0.5f,0.5f),white,n,glm::vec2(0,1)));
            m_mesh->vertices.push_back(O3DVertex(glm::vec3(0.5f,-0.5f,-0.5f),white,n,glm::vec2(1,0)));
            m_mesh->vertices.push_back(O3DVertex(glm::vec3(0.5f,0.5f,-0.5f),white,n,glm::vec2(1,1)));
            m_mesh->vertices.push_back(O3DVertex(glm::vec3(0.5f,0.5f,0.5f),white,n,glm::vec2(0,1)));
            
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
            m_mesh->vertices.push_back(O3DVertex(glm::vec3(-0.5f,0.5f,-0.5f),white,n,glm::vec2(0,0)));
            m_mesh->vertices.push_back(O3DVertex(glm::vec3(-0.5f,0.5f,0.5f),white,n,glm::vec2(0,1)));
            m_mesh->vertices.push_back(O3DVertex(glm::vec3(0.5f,0.5f,0.5f),white,n,glm::vec2(1,1)));
            m_mesh->vertices.push_back(O3DVertex(glm::vec3(-0.5f,0.5f,-0.5f),white,n,glm::vec2(0,0)));
            m_mesh->vertices.push_back(O3DVertex(glm::vec3(0.5f,0.5f,0.5f),white,n,glm::vec2(1,1)));
            m_mesh->vertices.push_back(O3DVertex(glm::vec3(0.5f,0.5f,-0.5f),white,n,glm::vec2(1,0)));
            
            m_mesh->calculateTangents();
            m_mesh->generateVAO();
        }
       
        void render(const glm::mat4& view, const glm::mat4& proj, const Shader_ptr& shader) override{
            
            setMVP(view, proj, shader);
            
            glBindVertexArray(m_mesh->vao);
                glDrawArrays(GL_TRIANGLES, 0, (GLuint)m_mesh->vertices.size());
            glBindVertexArray(0);
        }
        
        void onAttach() override{
            getGO()->setScale(glm::vec3(-1,1,1));
        }
    };
}

#endif /* O3DSkyboxRenderer_hpp */
