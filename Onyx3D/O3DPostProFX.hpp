//
//  O3DPostProFX.hpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 09/05/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#ifndef O3DPostProFX_hpp
#define O3DPostProFX_hpp

#include "O3DShader.hpp"

#include <GL/glew.h>

namespace  o3d {
    class O3DPostProFX{
    public:
        void init(Shader_ptr shader, int w, int h);
        void use(GLuint frame);
        GLuint getTextureId(){ return fx_tex; }
    protected:
        Shader_ptr shader;
        GLuint fx_fbo;
        GLuint fx_tex;
    };
}
#endif /* O3DPostProFX_hpp */
