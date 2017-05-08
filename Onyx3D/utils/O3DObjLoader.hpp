//
//  O3DObjLoader.hpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 24/04/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#ifndef O3DObjLoader_hpp
#define O3DObjLoader_hpp

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <vector>

namespace o3d {
    class O3DObjLoader{
    public:
        O3DObjLoader(const char* path);
    private:
        std::vector<glm::vec4> m_vertices;
        std::vector<GLushort> m_elements;
        std::vector<glm::vec3> m_normals;
    };
}

#endif /* O3DObjLoader_hpp */
