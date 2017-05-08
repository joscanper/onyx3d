//
//  O3DLighting.hpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 21/04/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#ifndef O3DLighting_hpp
#define O3DLighting_hpp

#include "O3DLight.hpp"
#include "O3DSpotLight.hpp"
#include "O3DShadowMapFBO.hpp"

#include <glm/vec3.hpp>
#include <vector>

namespace o3d {
    
    
    struct ShadowEmitter{
        
        ShadowEmitter(int size) : fbo(size){}
        
        Light_ptr light;
        float near;
        float far;
        float range;
        O3DShadowMapFBO fbo;
        //bool m_castshadows;
        glm::mat4 lightSpace;
        //uint m_shadowmap;
    };
    
    class O3DLighting{
    public:
        const int MAX_SHADOW_EMITTERS = 4;
        
        O3DLighting() :
            m_ambientLight(glm::vec3(0.5,0.5,0.5)){}
        
        void setAmbientLight(glm::vec3 color) { m_ambientLight = color; }
        inline glm::vec3 getAmbientLight(){ return m_ambientLight; }
        
        void addDirectionalLight(Light_ptr l){ m_directionalLights.push_back(l); }
        void addSpotLight(SpotLight_ptr l){ m_spotLights.push_back(l); }
        void addPointLight(Light_ptr l){ m_pointLights.push_back(l); }
        
        const std::vector<Light_ptr>& getDirectionalLights(){ return m_directionalLights; }
        const std::vector<SpotLight_ptr>& getSpotLights(){ return m_spotLights; }
        const std::vector<Light_ptr>& getPointLights(){ return m_pointLights; }
        
        void addShadowEmitter(ShadowEmitter emitter){
            if (m_shadowEmitters.size() == MAX_SHADOW_EMITTERS)
                throw ("Lighting : Reached max number of shadow emitting lights");
            m_shadowEmitters.push_back(emitter);
        };
        std::vector<ShadowEmitter>& getShadowEmitters(){ return m_shadowEmitters; }
        
    private:
        std::vector<Light_ptr> m_directionalLights;
        std::vector<SpotLight_ptr> m_spotLights;
        std::vector<Light_ptr> m_pointLights;
        
        std::vector<ShadowEmitter> m_shadowEmitters;
        
        
        glm::vec3 m_ambientLight;
    };
    
}
#endif /* O3DLighting_hpp */
