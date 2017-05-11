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



using namespace o3d;

void O3DRender::init(int w, int h){
    
    m_screenQuad = unique_ptr<O3DQuadRenderer>(new O3DQuadRenderer(1));
    m_screenShader = unique_ptr<O3DShader>(new O3DShader("resources/shaders/screen.vert", "resources/shaders/screen.frag"));
    
    //glEnable(GL_MULTISAMPLE);
    
    m_renderFBO.init(w,h);
    m_prevRenderFBO.init(w,h);
    
    m_shadowMaps.init();
    m_finalRender.init(w,h);
    m_motionBlurFX.init(w,h);
    m_bloomFX.init(w/2,h/2);
    
}


void O3DRender::render(){
    float initTime =glfwGetTime();
    
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
    
    
    renderShadowMaps(scene, viewM, projM);
    
    
    // ----------------------------------------------------
    // Difusse & Lighting ---------------------------------
    // ----------------------------------------------------
    
    glViewport(0, 0, O3D().getScreenSize().x, O3D().getScreenSize().y);
    
    glBindFramebuffer(GL_FRAMEBUFFER, m_renderFBO.framebuffer);
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
    
    // ----------------------------------------------------
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    
    // ----------------------------------------------------
    // Final composition  ---------------------------------
    // ----------------------------------------------------
    GLuint bloom = 0;
    if(!O3DInput::isKeyPressed(Keys::B)){
        m_bloomFX.use(m_renderFBO.colorBuffer);
        renderScreenQuad();
       bloom = m_bloomFX.getTextureId();
    }
    
    GLuint resultBuffer;
    // Final render to texture
    m_finalRender.use(m_renderFBO.colorBuffer, m_shadowMaps.getProjectedShadowTexture(), m_renderFBO.depthBuffer, bloom);
    renderScreenQuad();
    resultBuffer = m_finalRender.getTextureId();
    
    // FINAL FXs---------------
   
    
    if (m_motionBlurFX.isEnabled()){
        m_motionBlurFX.use(resultBuffer,m_renderFBO.depthBuffer, m_prevRenderFBO.depthBuffer, projM * viewM);
        renderScreenQuad();
        resultBuffer = m_motionBlurFX.getTextureId();
    }
   
    
    // Final composition to screen
    glBindFramebuffer(GL_FRAMEBUFFER, 0); // back to default
    m_screenShader->use();
    m_screenShader->setUniformTexture("screen", resultBuffer, 0);
    renderScreenQuad();
    
    // ----------------------------------------------------
    // -------- DEBUG RENDERS -----------------------------
    // ----------------------------------------------------
    
    showDebugRender(Keys::Num1, m_shadowMaps.getShadowMap(0));
    showDebugRender(Keys::Num2, m_shadowMaps.getShadowMap(1));
    showDebugRender(Keys::Num3, m_shadowMaps.getShadowMap(2));
    showDebugRender(Keys::Num4, m_shadowMaps.getShadowMap(3));
    
    showDebugRender(Keys::Num8, m_bloomFX.getTextureId());
    showDebugRender(Keys::Num9, m_shadowMaps.getProjectedShadowTexture());
    showDebugRender(Keys::Num0, m_renderFBO.colorBuffer);
    
    
    
    int w = O3D().getScreenSize().x;
    int h = O3D().getScreenSize().y;
    
    glBindFramebuffer(GL_READ_FRAMEBUFFER, m_renderFBO.framebuffer);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_prevRenderFBO.framebuffer);
    glBlitFramebuffer(0, 0, w, h, 0, 0, w, h, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
    m_renderTime += glfwGetTime() - initTime;
}

void O3DRender::showDebugRender(int key, GLuint texture){
    if(O3DInput::isKeyPressed(key)){
        m_screenShader->use();
        m_screenShader->setUniformTexture("screen", texture, 0);
        renderScreenQuad();
    }
}

void O3DRender::renderScreenQuad(){
    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glBindVertexArray(m_screenQuad->getMesh()->vao);
        glDrawArrays(GL_TRIANGLES, 0, (GLuint)m_screenQuad->getMesh()->vertices.size());
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
                if (r->getMaterial()->getRenderingMode() != MaterialRenderingMode::Opaque)
                    m_transparent[d] = r;
                else
                    m_opaque[d] = r;
            }
        }
        
        updateAndSortRenderers(child, cam);
    }
}

void O3DRender::renderShadowMaps(Scene_ptr scene, glm::mat4 viewM, glm::mat4 projM){
    int emitters = (int)scene->getLighting().getShadowEmitters().size();
    for (int i = 0; i < emitters; ++i){
        LightSetup ls = m_shadowMaps.setup(i);
        renderObjects(m_opaque, ls.view, ls.proj, m_shadowMaps.getShadowMapShader());
        renderObjects(m_transparent, ls.view, ls.proj, m_shadowMaps.getShadowMapShader());
    }
    m_shadowMaps.setupProjected();
    renderObjects(m_opaque, viewM, projM, m_shadowMaps.getShadowProjectionShader());
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
                rptr->getMaterial()->use(shader);
                rptr->render(view, projection, shader);
            }
            
            ++i;
        }
    }
}
