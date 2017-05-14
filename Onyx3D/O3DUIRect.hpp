//
//  O3DUIRect.hpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 14/05/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#ifndef O3DUIRect_hpp
#define O3DUIRect_hpp

#include "O3DGameObject.hpp"
#include "O3DQuadRenderer.hpp"
#include <glm/glm.hpp>

namespace o3d {
    DEFINE_CLASS_PTR(O3DUIRect,UIRect);
    
    class O3DUIRect : public O3DGameObject {
    public:
        O3DUIRect(const char*id, float x, float y, float w, float h) :
            O3DGameObject(id),
            m_size(w, h),
            m_color(1,1,1,1)
        {
            setPosition(glm::vec3(x, y, 0));
        }
        
        void setSize(glm::vec2 size){ m_size = size; }
        glm::vec2 getSize(){ return m_size; }
        
        void setColor(glm::vec4 c){ m_color = c; }
        glm::vec4 getColor(){ return m_color; }
    private:
        glm::vec4 m_color;
        glm::vec2 m_size;

    };
}

#endif /* O3DUIRect_hpp */
