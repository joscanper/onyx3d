//
//  O3DRenderComposition.hpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 09/05/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#ifndef O3DRenderComposition_hpp
#define O3DRenderComposition_hpp

#include "O3DPostProFX.hpp"

namespace o3d{
    class  O3DRenderComposition : public O3DPostProFX{
    public:
        
        void init(int w, int h){
            Shader_ptr s = std::make_shared<O3DShader>("resources/shaders/screen.vert", "resources/shaders/final_render.frag");
            O3DPostProFX::init(s, w, h);
        }
    
        void use(GLuint diffuse, GLuint shadows, GLuint depth, GLuint bloom){
            glViewport(0,0,width,height);
            glBindFramebuffer(GL_FRAMEBUFFER, fx_fbo);
            glClearColor(1,1,1,1);
            glClear(GL_COLOR_BUFFER_BIT);
            
            shader->use();
            shader->setUniformTexture("diffuse", diffuse,0);
            shader->setUniformTexture("shadows", shadows, 1);
            shader->setUniformTexture("depth", depth,2);
            shader->setUniformTexture("bloom", bloom,3);
        }
    };
}

#endif /* O3DRenderComposition_hpp */
