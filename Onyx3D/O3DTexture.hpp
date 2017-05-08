//
//  O3DTexture.hpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 18/04/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#ifndef O3DTexture_hpp
#define O3DTexture_hpp

#include "O3DDefines.hpp"
#include <GL/glew.h>
#include <iostream>
#include <memory>

namespace o3d {
    
    DEFINE_CLASS_PTR(O3DTexture, Texture);
    
    class O3DTexture{
    public:
        explicit O3DTexture(const char* filename);
        ~O3DTexture(){
            glDeleteTextures(1, &m_texture);
            DELETE_NOTIF("TEXTURE");
        }
        
        GLuint getTextureId(){ return m_texture; };
    private:
        GLuint m_texture;
    };
}


#endif /* O3DTexture_hpp */
