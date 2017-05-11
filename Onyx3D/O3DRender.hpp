//
//  O3DRender.hpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 27/04/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#ifndef O3DRender_hpp
#define O3DRender_hpp

#include "O3DRenderer.hpp"
#include "O3DQuadRenderer.hpp"
#include "O3DSkyboxRenderer.hpp"
#include "O3DScene.hpp"
#include "O3DTransform.hpp"
#include "O3DShadowMapping.hpp"
#include "O3DRenderComposition.hpp"
#include "O3DMotionBlurFX.hpp"
#include "O3DBloomFX.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <map>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>

namespace o3d {
    
    class O3DRenderFBO{
    public:
        ~O3DRenderFBO(){
            glDeleteBuffers(1, &framebuffer);
            glDeleteTextures(1, &colorBuffer);
            glDeleteTextures(1, &depthBuffer);
        }
        
        void init(int w, int h){
            glGenFramebuffers(1, &framebuffer);
            
            glGenTextures(1, &colorBuffer);
            glBindTexture(GL_TEXTURE_2D, colorBuffer);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glBindTexture(GL_TEXTURE_2D, 0);
            
            glGenTextures(1, &depthBuffer);
            glBindTexture(GL_TEXTURE_2D, depthBuffer);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, w, h, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glBindTexture(GL_TEXTURE_2D, 0);
            
            glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorBuffer, 0);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthBuffer, 0);
            
            if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
                std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
            
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }
        
        
        GLuint framebuffer;
        GLuint colorBuffer;
        GLuint depthBuffer;
    };
    
    class O3DRender {
    
    public:
        void render();
        void init(int w, int h);
        float getRenderTime(int frames) {
            float time = m_renderTime / frames;
            m_renderTime = 0;
            return time;
        }
        O3DMotionBlurFX& getMotionBlur() { return m_motionBlurFX; }
    private:
        float m_renderTime;
        
        QuadRenderer_Uptr m_screenQuad;
        Shader_Uptr m_screenShader;
        
        O3DRenderComposition m_finalRender;
        O3DMotionBlurFX m_motionBlurFX;
        O3DBloomFX m_bloomFX;
        O3DShadowMapping m_shadowMaps;
        
        O3DRenderFBO m_renderFBO;
        O3DRenderFBO m_prevRenderFBO;
        
        SkyboxRenderer_Wptr m_skybox;
        std::map<float, Renderer_Wptr> m_opaque;
        std::map<float, Renderer_Wptr> m_transparent;
        
        void updateAndSortRenderers(const SceneNode_ptr& node, const Camera_ptr& cam);
        float getValidDistance(const Transform_ptr& node, const Camera_ptr& cam);
        void sortScene();
        void renderShadowMap(const Camera_ptr& cam);
        void renderObjects(const std::map<float, Renderer_Wptr>& list, const glm::mat4& view, const glm::mat4& proj, const Shader_ptr& shader = nullptr);
        void renderScreenQuad();
        void renderShadowMaps(Scene_ptr scene, glm::mat4 viewM, glm::mat4 projM);
        void showDebugRender(int key, GLuint texture);
        void prepareBuffers(int w, int h);
        
    };
}

#endif /* O3DRenderer_hpp */
