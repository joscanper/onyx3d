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
#include "O3DCubeRenderer.hpp"

namespace o3d {
    DEFINE_CLASS_PTR(O3DSkyboxRenderer, SkyboxRenderer)
    
    class O3DSkyboxRenderer : public O3DCubeRenderer{
    public:
        O3DSkyboxRenderer() : O3DCubeRenderer() {
            
        };
       
        void render(const glm::mat4& view, const glm::mat4& proj, const Shader_ptr& shader) override{
            
            setMVP(view, proj, shader);
            
            glDepthMask(GL_FALSE);
            glBindVertexArray(m_mesh->vao);
                glDrawArrays(GL_TRIANGLES, 0, (GLuint)m_mesh->vertices.size());
            glBindVertexArray(0);
            glDepthMask(GL_TRUE);
        }
        
        void onAttach() override{
            getGO()->setScale(glm::vec3(-1,1,1));
        }
    };
}

#endif /* O3DSkyboxRenderer_hpp */
