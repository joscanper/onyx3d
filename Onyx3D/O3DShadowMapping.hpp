//
//  O3DShadowMapping.hpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 28/04/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#ifndef O3DShadowMapping_hpp
#define O3DShadowMapping_hpp

#include "O3DScene.hpp"
#include "O3DShader.hpp"
#include "O3DShadowMapFBO.hpp"

#include <GL/glew.h>
#include <functional>

#define FINAL_RENDER_W 800
#define FINAL_RENDER_H 600

namespace o3d {
    
    struct LightSetup{
        glm::mat4 view;
        glm::mat4 proj;
    };
    
    
    class O3DShadowMapping{
        
    public:
        void init();
        LightSetup setup(int index);
        void setupProjected();
        
        Shader_ptr getShadowProjectionShader() { return m_projected_shader; }
        Shader_ptr getShadowMapShader(){ return m_shadowmap_shader; }
        
        GLuint getProjectedShadowTexture() { return m_projected_tex; }
        GLuint getShadowMap(int index) {
            std::vector<ShadowEmitter> emitters = O3DScene::getActiveScene()->getLighting().getShadowEmitters();
            if (index < emitters.size())
                return emitters[index].fbo.getTextureId();
            else
                return 0;
        }
        
    private:
        GLuint m_projected_fbo;
        GLuint m_projected_rbo;
        GLuint m_projected_tex;
        
        Shader_ptr m_shadowmap_shader;
        Shader_ptr m_projected_shader;
        
        //O3DShadowMapFBO* m_shadow_fbo;
        
        LightSetup getLightSetup(const ShadowEmitter& emitter);
        
    };
}
#endif /* O3DShadowMapping_hpp */
