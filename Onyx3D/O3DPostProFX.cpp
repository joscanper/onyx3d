//
//  O3DPostProFX.cpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 09/05/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#include "O3DCore.hpp"
#include "O3DPostProFX.hpp"

using namespace o3d;

void O3DPostProFX::init(Shader_ptr shader, int w, int h){
    this->shader = shader;
    
    glGenFramebuffers(1, &fx_fbo);
    glGenTextures(1, &fx_tex);
    glBindTexture(GL_TEXTURE_2D, fx_tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, O3D().getScreenSize().x, O3D().getScreenSize().y,0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    glBindFramebuffer(GL_FRAMEBUFFER, fx_fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fx_tex, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR: PostProFX framebuffer is not complete" << std::endl;
}

void O3DPostProFX::use(GLuint frame){
    glBindFramebuffer(GL_FRAMEBUFFER, fx_fbo);
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);
    
    shader->use();
    shader->setUniformTexture("screen", frame, 0);
}

