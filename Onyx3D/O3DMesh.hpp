//
//  O3DMesh.hpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 18/04/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#ifndef O3DMesh_hpp
#define O3DMesh_hpp

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

namespace o3d {

    class O3DVertex{
        public:
        // Do not alter this order since it is given to the shader in this order
        glm::vec3 m_position;
        glm::vec3 m_color;
        glm::vec3 m_normal;
        glm::vec2 m_texcoord;
        glm::vec3 m_tangent;
        
        
        O3DVertex(glm::vec3 pos = glm::vec3(0,0,0), glm::vec3 col = glm::vec3(1,1,1), glm::vec3 n =  glm::vec3(0,0,0), glm::vec2 texc = glm::vec2(0,0)) :
            m_position(pos),
            m_color(col),
            m_normal(n),
            m_texcoord(texc),
            m_tangent()
        {   
        }
            };

    DEFINE_CLASS_PTR(O3DMesh, Mesh)
    
    class O3DMesh{
    private:
        GLuint m_vbo, m_ebo;
        
    public:
        ~O3DMesh(){
            DELETE_NOTIF("MESH");
            glDeleteVertexArrays(1, &vao);
        }
        
        GLuint vao;
        std::vector<O3DVertex> vertices;
        std::vector<GLuint> indices;
        
        
        void generateVAO(){
            glGenVertexArrays(1, &vao);
            glGenBuffers( 1, &m_vbo);
            
            
            glBindVertexArray(vao);
            
            glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(O3DVertex), &vertices[0], GL_STATIC_DRAW);
            
            if (indices.size() > 0){
                glGenBuffers(1, &m_ebo);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
            }
            
            // Position
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(O3DVertex), (GLvoid*)0);
            glEnableVertexAttribArray(0);
            // Color
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(O3DVertex), (GLvoid*)sizeof(glm::vec3));
            glEnableVertexAttribArray(1);
            // Normal
            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(O3DVertex), (GLvoid*)(sizeof(glm::vec3)*2));
            glEnableVertexAttribArray(2);
            // TextureCoords
            glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(O3DVertex), (GLvoid*)(sizeof(glm::vec3)*3));
            glEnableVertexAttribArray(3);
            // Tangent
            glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(O3DVertex), (GLvoid*)(sizeof(glm::vec3)*3 + sizeof(glm::vec2)));
            glEnableVertexAttribArray(4);
            
            glBindVertexArray(0);
            
            glDeleteBuffers(1, &m_vbo);
            if (indices.size() > 0)
                glDeleteBuffers(1, &m_ebo);
            
        }
        
        void calculateTangents(){
            for(int i=0; i< vertices.size(); i+=3){
                glm::vec3 tangent = calculateTangent(vertices[i],vertices[i+1],vertices[i+2]);
                vertices[i].m_tangent = tangent;
                vertices[i+1].m_tangent = tangent;
                vertices[i+2].m_tangent = tangent;
            }
        }
        
        glm::vec3 calculateTangent(const O3DVertex& v0,const O3DVertex& v1,const O3DVertex& v2){
            glm::vec3 edge1 = v1.m_position - v0.m_position;
            glm::vec3 edge2 = v2.m_position - v0.m_position;
            glm::vec2 deltaUV1 = v1.m_texcoord - v0.m_texcoord;
            glm::vec2 deltaUV2 = v2.m_texcoord - v0.m_texcoord;
            
            GLfloat f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);
            
            glm::vec3 tangent;
            tangent.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
            tangent.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
            tangent.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
            tangent = glm::normalize(tangent);
            
            return tangent;
        }
    };
}
#endif /* O3DMesh_hpp */
