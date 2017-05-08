//
//  O3DSpotLight.hpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 24/04/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#ifndef O3DSpotLight_hpp
#define O3DSpotLight_hpp

#include "O3DLight.hpp"

namespace o3d{
    DEFINE_CLASS_PTR(O3DSpotLight, SpotLight);
    
    class O3DSpotLight : public O3DLight{
    public:
        O3DSpotLight(const char* id) :
            O3DLight(id),
            m_angle(30)
        {}
        ~O3DSpotLight(){
            DELETE_NOTIF("SPOTLIGHT");
        }
        
        void setAngle(float a){ m_angle = a; };
        float getAngle(){ return m_angle; };
    private:
        float m_angle;
    };
}
#endif /* O3DSpotLight_hpp */
