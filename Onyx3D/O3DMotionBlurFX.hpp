//
//  O3DMotionBlurFX.hpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 09/05/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#ifndef O3DMotionBlurFX_hpp
#define O3DMotionBlurFX_hpp

#include "O3DPostProFX.hpp"


namespace o3d {
    class O3DMotionBlurFX : public O3DPostProFX {
    public:
        void init(int w, int h){
            Shader_ptr s = std::make_shared<O3DShader>("resources/shaders/screen.vert", "resources/shaders/motionblur.frag");
            O3DPostProFX::init(s, w, h);
        }
        
        void use(GLuint screen, GLuint depth, GLuint prevDepth, glm::mat4 viewProj){
            
            glBindFramebuffer(GL_FRAMEBUFFER, fx_fbo);
            glClearColor(1,1,1,1);
            glClear(GL_COLOR_BUFFER_BIT);
            
            shader->use();
            shader->setUniformTexture("screen", screen,0);
            shader->setUniformTexture("depthTexture", depth,1);
            shader->setUniformTexture("prevDepthTexture", prevDepth,2);
            shader->setUniform("viewProjectionInverseM", glm::inverse(viewProj));
            shader->setUniform("previousViewProjectionM", m_prevViewProj);
            
            m_prevViewProj = viewProj;
        }
        
    private:
        glm::mat4 m_prevViewProj;
    };
}
#endif /* O3DMotionBlurFX_hpp */
