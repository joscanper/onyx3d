//
//  O3DShadowMapping.cpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 28/04/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#include "O3DShadowMapping.hpp"

using namespace o3d;

void O3DShadowMapping::init(){

    glGenFramebuffers(1, &m_projected_fbo);
    glGenTextures(1, &m_projected_tex);
    glBindTexture(GL_TEXTURE_2D, m_projected_tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, FINAL_RENDER_W, FINAL_RENDER_H,0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    glGenRenderbuffers(1, &m_projected_rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, m_projected_rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, FINAL_RENDER_W, FINAL_RENDER_H);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    

    glBindFramebuffer(GL_FRAMEBUFFER, m_projected_fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_projected_tex, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_projected_rbo);
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR: ShadowMapping framebuffer is not complete" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    

    m_projected_shader = std::make_shared<O3DShader>("resources/shaders/shadows.vert", "resources/shaders/shadows.frag");
    m_shadowmap_shader = std::make_shared<O3DShader>("resources/shaders/basic.vert", "resources/shaders/shadowmap.frag");
    
}


LightSetup O3DShadowMapping::setup(int index){
    ShadowEmitter& emitter = O3DScene::getActiveScene()->getLighting().getShadowEmitters()[index];
    
    emitter.fbo.setup();
    LightSetup ls = getLightSetup(emitter);
    emitter.lightSpace = ls.proj * ls.view;
    
    m_shadowmap_shader->setUniform("near", emitter.near);
    m_shadowmap_shader->setUniform("far", emitter.far);
    
    return ls;
}

LightSetup O3DShadowMapping::getLightSetup(const ShadowEmitter& emitter){
    Light_ptr l = emitter.light;
    LightSetup ls;
    ls.view = glm::lookAt(l->getPosition(), l->getPosition() - l->getDirection(), glm::vec3(0,1,0));
    if(SpotLight_ptr spot = dynamic_pointer_cast<O3DSpotLight>(l))
        ls.proj = glm::perspective(45.0f * (emitter.range/5.0f), 1.0f, emitter.near, emitter.far);
    else
        ls.proj = glm::ortho(-emitter.range, emitter.range, -emitter.range, emitter.range, emitter.near, emitter.far);
        
    return ls;
}

void O3DShadowMapping::setupProjected(){
    glViewport(0, 0, FINAL_RENDER_W, FINAL_RENDER_H);
    glBindFramebuffer(GL_FRAMEBUFFER, m_projected_fbo);
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    const std::vector<ShadowEmitter> emitters = O3DScene::getActiveScene()->getLighting().getShadowEmitters();
    
    m_projected_shader->use();
    m_projected_shader->setUniform("shadowEmitters.number", (int)emitters.size());
    
    for (int i = 0; i < emitters.size(); i++){
        ShadowEmitter se = emitters[i];
        std::string index = std::to_string(i);
        m_projected_shader->setUniform(("shadowEmitters.lightSpace["+index+"]").c_str(), se.lightSpace);
        m_projected_shader->setUniformTexture(("shadowEmitters.shadowMap["+index+"]").c_str(), se.fbo.getTextureId(), i);
        m_projected_shader->setUniform(("shadowEmitters.lightDir["+index+"]").c_str(), se.light->getDirection());
    }
}
