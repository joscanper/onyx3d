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

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <map>

namespace o3d {
    class O3DRender {
    
    public:
        
        
        void render();
        void init(int w, int h);
    private:
        
        QuadRenderer_Uptr screenQuad;
        
        Shader_ptr baseShader;
        Shader_Uptr screenShader;
        Shader_Uptr finalRenderShader;
        //Shader_Uptr screenFogShader;
        
        O3DShadowMapping shadowMaps;
        
        GLuint framebuffer;
        GLuint texColorBuffer;
        GLuint depthBuffer;
        
        SkyboxRenderer_Wptr m_skybox;
        std::map<float, Renderer_Wptr> m_opaque;
        std::map<float, Renderer_Wptr> m_transparent;
        
        void updateAndSortRenderers(const SceneNode_ptr& node, const Camera_ptr& cam);
        float getValidDistance(const Transform_ptr& node, const Camera_ptr& cam);
        void sortScene();
        void renderShadowMap(const Camera_ptr& cam);
        void renderObjects(const std::map<float, Renderer_Wptr>& list, const glm::mat4& view, const glm::mat4& proj, const Shader_ptr& shader = nullptr);
        void renderScreenQuad();
        void showDebugRender(int key, GLuint texture);
    };
}

#endif /* O3DRenderer_hpp */
