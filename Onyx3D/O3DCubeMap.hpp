//
//  O3DCubeMap.hpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 26/04/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#ifndef O3DCubeMap_hpp
#define O3DCubeMap_hpp

#include "O3DDefines.hpp"
#include <GL/glew.h>
#include <stdio.h>
#include <vector>
#include <string>

namespace o3d {
    DEFINE_CLASS_PTR(O3DCubeMap,CubeMap);
    
    class O3DCubeMap {
    public:
        O3DCubeMap(std::vector<std::string> textures);
        ~O3DCubeMap();
        
        GLuint getTextureId(){ return m_texture; };
    private:
        GLuint m_texture;
    };
}

#endif /* O3DCubeMap_hpp */
