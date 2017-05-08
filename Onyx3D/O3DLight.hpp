//
//  O3DLight.hpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 21/04/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#ifndef O3DLight_hpp
#define O3DLight_hpp

#include "O3DGameObject.hpp"
#include <iostream>

namespace o3d {
    DEFINE_CLASS_PTR(O3DLight, Light);
    
    class O3DLight : public O3DGameObject{
    public:
        O3DLight(const char* id):
            O3DGameObject(id),
            m_specular(glm::vec3(1,1,1)),
            m_range(1),
            m_intensity(1),
            m_color(glm::vec3(1,1,1))
        {
        }
        ~O3DLight(){
            DELETE_NOTIF("LIGHT");
        }
        

        void setColor(glm::vec3 col){ m_color = col; }
        void setSpecular(glm::vec3 s){ m_specular = s; }
        void setRange(float s){ m_range = s; }
        void setIntensity(float s){ m_intensity = s; }
        
        glm::vec3 getColor() { return m_color; }
        glm::vec3 getSpecular() { return m_specular; }
        float getRange() { return m_range; }
        float getIntensity() { return m_intensity; }
        
        
    private:

        glm::vec3 m_specular;
        float m_range;
        float m_intensity;
        glm::vec3 m_color;
        
        
    };
}
#include <stdio.h>

#endif /* O3DLight_hpp */
