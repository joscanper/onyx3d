//
//  O3DWaterRenderer.hpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 16/05/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#ifndef O3DWaterRenderer_hpp
#define O3DWaterRenderer_hpp

#include "O3DMeshRenderer.hpp"
#include "O3DFBO.hpp"

#include <vector>

namespace o3d {
    DEFINE_CLASS_PTR(O3DWaterRenderer, WaterRenderer);
    
    class O3DWaterRenderer : public O3DMeshRenderer{
    public:
        O3DWaterRenderer();
        
        void render(const glm::mat4& view, const glm::mat4& proj, const Shader_ptr& shader) override;
            
        void initFBOs(int w, int h);
        
        FBO_ptr getReflection(){ return reflection_fbo; }
        FBO_ptr getRefraction(){ return refraction_fbo; }
        
        void setSpecular(float spec){ m_specular = spec; }
        void setSpeed(float s){ m_speed = s; }
        void setWaveStrength(float ws){ m_waveStrength = ws; }
        void setDensity(float d){ m_density = d; }
        void setColor(glm::vec3 c){ m_color = c; }
        void setTiling(float t){ m_tiling = t; }
    private:
        float m_specular;
        float m_waveStrength;
        float m_speed;
        float m_density;
        float m_tiling;
        glm::vec3 m_color;
        
        FBO_ptr reflection_fbo;
        FBO_ptr refraction_fbo;
    };
}
#endif /* O3DWaterRenderer_hpp */
