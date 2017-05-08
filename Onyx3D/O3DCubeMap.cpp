//
//  O3DCubeMap.cpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 26/04/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#include "O3DCubeMap.hpp"
#include "utils/SOIL2/SOIL2.h"

using namespace o3d;

O3DCubeMap::O3DCubeMap(std::vector<std::string> paths){
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture);
    
    unsigned char* image;
    int width, height;
    for(GLuint i = 0; i < paths.size(); i++)
    {
        image = SOIL_load_image(paths[i].c_str(), &width, &height, 0, SOIL_LOAD_RGB);
        glTexImage2D(
                     GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                     0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image
                     );
        
        SOIL_free_image_data(image);
    }
    
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

O3DCubeMap::~O3DCubeMap(){
    glDeleteTextures(1, &m_texture);
    DELETE_NOTIF("CUBEMAP");
}
