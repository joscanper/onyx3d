//
//  O3DShadowMapFBO.hpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 03/05/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//



#ifndef O3DShadowMapFBO_hpp
#define O3DShadowMapFBO_hpp

#include <GL/glew.h>

namespace o3d {

    class O3DShadowMapFBO{
    public:
        O3DShadowMapFBO(int size){
            m_size = size;
            
            glGenFramebuffers(1, &m_smap_fbo);
            glGenTextures(1, &m_smap_tex);
            glBindTexture(GL_TEXTURE_2D, m_smap_tex);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, size, size,0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
            
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
            GLfloat borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
            glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
            glBindTexture(GL_TEXTURE_2D, 0);
            
            glBindFramebuffer(GL_FRAMEBUFFER, m_smap_fbo);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_smap_tex, 0);
            glDrawBuffer(GL_NONE);
            glReadBuffer(GL_NONE);
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            
            if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
                std::cout << "ERROR: Shadow Map framebuffer is not complete" << std::endl;
        }
        
        void setup(){
            glViewport(0, 0, m_size, m_size);
            glBindFramebuffer(GL_FRAMEBUFFER, m_smap_fbo);
            glClear(GL_DEPTH_BUFFER_BIT);
            //glCullFace(GL_FRONT);
        }
        
        
        
        GLuint getTextureId(){ return m_smap_tex; }
        
    private:
        GLuint m_size;
        GLuint m_smap_fbo;
        GLuint m_smap_tex;
        
        
    };

}
#endif /* O3DShadowMapFBO_hpp */
