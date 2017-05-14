//
//  O3DUIDraw.hpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 14/05/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#ifndef O3DUIDraw_hpp
#define O3DUIDraw_hpp

#include "O3DUIRect.hpp"
#include "O3DTexture.hpp"

namespace o3d {
    DEFINE_CLASS_PTR(O3DUIDraw, UIDraw);
    
    class O3DUIDraw : public O3DUIRect {
    public:
        O3DUIDraw(const char* id, Texture_Wptr texture, float x, float y, float w, float h) :
        O3DUIRect(id, x, y, w, h),
        m_texture(texture)
        {
            
        }
        
        void setTexture(Texture_Wptr t){ m_texture = t; }
        GLuint getTextureId(){
            if (Texture_ptr t = m_texture.lock())
                return t->getTextureId();
            return 0;
        }
    private:
        Texture_Wptr m_texture;
        
    };
}
#endif /* O3DUIDraw_hpp */
