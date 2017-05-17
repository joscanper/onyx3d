//
//  O3DFBO.hpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 16/05/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#ifndef O3DFBO_hpp
#define O3DFBO_hpp

#include "O3DDefines.hpp"
#include <GL/glew.h>
#include <iostream>

namespace o3d {
    DEFINE_CLASS_PTR(O3DFBO, FBO);
    
    class O3DFBO{
    public:
        O3DFBO(GLuint w, GLuint h) :
            m_w(w),
            m_h(h)
        {
            glGenFramebuffers(1, &m_fbo);
        }
        
        ~O3DFBO(){
            glDeleteBuffers(1, &m_fbo);
            glDeleteTextures(1, &m_color);
            glDeleteTextures(1, &m_depth);
        }
        
        void bind(){
            glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
            glViewport(0,0,m_w, m_h);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }
        
        void unbind(){
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }
        
        void addColorTexture(){
            
            glGenTextures(1, &m_color);
            glBindTexture(GL_TEXTURE_2D, m_color);
            
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_w, m_h,0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            
            glBindTexture(GL_TEXTURE_2D, 0);
            
            glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_color, 0);
            
        }
        
        void addDepthTexture(){
            glGenTextures(1, &m_depth);
            glBindTexture(GL_TEXTURE_2D, m_depth);
            
            glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, m_w, m_h, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            
            glBindTexture(GL_TEXTURE_2D, 0);
            
            glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depth, 0);
        }
        
        void checkStatus(){
            if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
                std::cout << "ERROR: O3DFBO framebuffer is not complete" << std::endl;
        }
        
        GLuint getColorTextureId(){ return m_color; }
        GLuint getDepthTextureId(){ return m_depth; }
        
    private:
        GLuint m_fbo;
        GLuint m_color;
        GLuint m_depth;
        
        int m_w;
        int m_h;
        
    };
}
#endif /* O3DFBO_hpp */
