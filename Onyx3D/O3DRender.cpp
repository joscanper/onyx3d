//
//  O3DRenderer.cpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 27/04/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#include "O3DRender.hpp"
#include "O3DScene.hpp"
#include "O3DCore.hpp"
#include "O3DInput.hpp"


#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>
//#include <gtx/norm.hpp>

using namespace o3d;

void O3DRender::init(int w, int h){
    
    screenQuad = unique_ptr<O3DQuadRenderer>(new O3DQuadRenderer(1));
    baseShader = shared_ptr<O3DShader>(new O3DShader("resources/shaders/basic.vert", "resources/shaders/unlit.frag"));
    screenShader = unique_ptr<O3DShader>(new O3DShader("resources/shaders/screen.vert", "resources/shaders/screen.frag"));
    finalRenderShader = unique_ptr<O3DShader>(new O3DShader("resources/shaders/screen.vert", "resources/shaders/finalrender.frag"));
    //screenFogShader = unique_ptr<O3DShader>(new O3DShader("resources/shaders/screen.vert", "resources/shaders/fog.frag"));
    
    glEnable(GL_MULTISAMPLE);
    
    glGenFramebuffers(1, &framebuffer);
    
    glGenTextures(1, &texColorBuffer);
    glBindTexture(GL_TEXTURE_2D, texColorBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    glGenTextures(1, &depthBuffer);
    glBindTexture(GL_TEXTURE_2D, depthBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, w, h, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthBuffer, 0);
    
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
        
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
    shadowMaps.init();
}

void O3DRender::render(){

    m_opaque.clear();
    m_transparent.clear();
    
    Scene_ptr scene = O3DScene::getActiveScene();
    Camera_ptr cam = scene->getActiveCamera();
    SceneNode_ptr root = scene->getRoot();
    updateAndSortRenderers(root, cam);
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    
    
    glm::mat4 viewM = cam->getViewMatrix();
    glm::mat4 projM = cam->getProjectionMatrix();
    
    
    // ----------------------------------------------------
    // Shadow Mapping -------------------------------------
    // ----------------------------------------------------
    int emitters = (int)scene->getLighting().getShadowEmitters().size();
    for (int i = 0; i < emitters; ++i){
        LightSetup ls = shadowMaps.setup(i);
        renderObjects(m_opaque, ls.view, ls.proj, shadowMaps.getShadowMapShader());
    }
    shadowMaps.setupProjected();
    renderObjects(m_opaque, viewM, projM, shadowMaps.getShadowProjectionShader());
    
    /// ----------------------------------------------------
    
    
    // ----------------------------------------------------
    // Difusse & Lighting ---------------------------------
    // ----------------------------------------------------
    
    glViewport(0, 0, O3D().getScreenSize().x, O3D().getScreenSize().y);
    
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // We're not using stencil buffer now
    glCullFace(GL_BACK);
    
    // Skybox ------------------------------
    if (!m_skybox.expired()){
        SkyboxRenderer_ptr skybox = m_skybox.lock();
        skybox->getMaterial()->use();
        skybox->render(viewM, projM, skybox->getMaterial()->getShader());
    }
    
    // Opaque objects ----------------------
    renderObjects(m_opaque, viewM, projM);
    
    // Transparent objects -----------------
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    renderObjects(m_transparent, viewM, projM);
    glDisable(GL_BLEND);
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0); // back to default
    
    // ----------------------------------------------------
    
    
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    
    
    /// POST FX SHADERS - HERE WE SHOULD DO.
    /*
    
    for (auto s : postFXShaders){
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
        s->use();
        glBindVertexArray(screenQuad->getMesh()->vao);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texColorBuffer);
        glDrawElements(GL_TRIANGLES, (GLuint)screenQuad->getMesh()->indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        glBindFramebuffer(GL_FRAMEBUFFER, 0); // back to default
    }
    */
    
    // ----------------------------------------------------
    // Final composition  ---------------------------------
    // ----------------------------------------------------
    
    finalRenderShader->use();
    finalRenderShader->setUniformTexture("diffuse", texColorBuffer,0);
    finalRenderShader->setUniformTexture("shadows", shadowMaps.getProjectedShadowTexture(), 1);
    finalRenderShader->setUniformTexture("depth", depthBuffer,2);
    renderScreenQuad();
    
    // -------- DEBUG RENDERS -----------------------------
    
    showDebugRender(Keys::Num1, shadowMaps.getShadowMap(0));
    showDebugRender(Keys::Num2, shadowMaps.getShadowMap(1));
    showDebugRender(Keys::Num3, shadowMaps.getShadowMap(2));
    showDebugRender(Keys::Num4, shadowMaps.getShadowMap(3));
    
    showDebugRender(Keys::F, shadowMaps.getProjectedShadowTexture());
    showDebugRender(Keys::G, texColorBuffer);
}

void O3DRender::showDebugRender(int key, GLuint texture){
    if(O3DInput::isKeyPressed(key)){
        screenShader->use();
        screenShader->setUniformTexture("screen", texture, 0);
        renderScreenQuad();
    }
}

void O3DRender::renderScreenQuad(){
    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glBindVertexArray(screenQuad->getMesh()->vao);
        glDrawElements(GL_TRIANGLES, (GLuint)screenQuad->getMesh()->indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}


void O3DRender::updateAndSortRenderers(const SceneNode_ptr& node, const Camera_ptr& cam){
    for (int i = 0; i < node->childrenCount(); i++){
        SceneNode_ptr child = node->getChild(i);
        GameObject_ptr go = std::dynamic_pointer_cast<O3DGameObject>(child);
        if (go){
            
            if (Renderer_ptr r = go->getComponent<O3DRenderer>()){
                if (SkyboxRenderer_ptr sbr = std::dynamic_pointer_cast<O3DSkyboxRenderer>(r)){
                    m_skybox = sbr;
                    continue;
                }
                
                float d = getValidDistance(go, cam);
                if (r->getMaterial()->isTransparent())
                    m_transparent[d] = r;
                else
                    m_opaque[d] = r;
            }
        }
        
        updateAndSortRenderers(child, cam);
    }
}



float O3DRender::getValidDistance(const Transform_ptr& t, const Camera_ptr& cam){
    
    float d = glm::length2(t->getPosition() - cam->getPosition());
    while(m_opaque.find(d) != m_opaque.end()){
        d += 0.0001f;
    }
    return d;
}



void O3DRender::renderObjects(const std::map<float, Renderer_Wptr>& list,const glm::mat4& view,const glm::mat4& projection, const Shader_ptr& shader){
    int i(0);
    for(auto r : list){
        if (!r.second.expired()){
            Renderer_ptr rptr = r.second.lock();
            
            if (shader == nullptr){
                rptr->getMaterial()->use();
                rptr->render(view, projection, rptr->getMaterial()->getShader());
            }else{
                shader->use();
                rptr->render(view, projection, shader);
            }
            
            ++i;
        }
    }
}
