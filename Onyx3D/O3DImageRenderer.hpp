//
//  O3DImageRenderer.hpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 14/05/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#ifndef O3DImageRenderer_hpp
#define O3DImageRenderer_hpp

#include "O3DUIDraw.hpp"

namespace o3d {
    DEFINE_CLASS_PTR(O3DImageRenderer, ImageRenderer)
    
    class O3DImageRenderer : public O3DQuadRenderer{
    public:
        O3DImageRenderer(float w, float h) : O3DQuadRenderer(w, h){
            setMaterial(O3D().getResources().getMaterial("o3d_materials/ui"));
        }
        
        void render(const glm::mat4& view, const glm::mat4& proj, const Shader_ptr& shader) override{
            
            setMVP(view, proj, shader);        
            
            GLuint texture = 0;
            if (UIDraw_ptr uidraw = std::dynamic_pointer_cast<O3DUIDraw>(getGO())){
                texture = uidraw->getTextureId();
                shader->setUniform("color", uidraw->getColor());
            }
            
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture);
            glBindVertexArray(m_mesh->vao);
            glDrawArrays(GL_TRIANGLES, 0, (GLuint)m_mesh->vertices.size());
            glBindVertexArray(0);
        };
        
    private:
    };
    
}
#endif /* O3DImageRenderer_hpp */
