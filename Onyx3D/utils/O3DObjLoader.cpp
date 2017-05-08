//
//  O3DObjLoader.cpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 24/04/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#include "O3DObjLoader.hpp"


#include <iostream>
#include <fstream>
#include <sstream>
#include <ios>

using namespace o3d;

O3DObjLoader::O3DObjLoader(const char* path){
    std::ifstream in(path, std::ios::in);
    if (!in){
        std::cerr << "Cannot open " << path << std::endl;
        return;
    }
    
    std::string line;
    while (getline(in, line))
    {
        if (line.substr(0,2) == "v ")
        {
            std::istringstream s(line.substr(2));
            glm::vec4 v; s >> v.x; s >> v.y; s >> v.z; v.w = 1.0f;
            m_vertices.push_back(v);
        }
        else if (line.substr(0,2) == "f ")
        {
            std::istringstream s(line.substr(2));
            GLushort a,b,c;
            s >> a; s >> b; s >> c;
            a--; b--; c--;
            m_elements.push_back(a); m_elements.push_back(b); m_elements.push_back(c);
        }
        else if (line[0] == '#')
        {
            /* ignoring this line */
        }
        else
        {
            /* ignoring this line */
        }
    }
    
    m_normals.resize(m_vertices.size(), glm::vec3(0.0, 0.0, 0.0));
    for (int i = 0; i < m_elements.size(); i+=3)
    {
        GLushort ia = m_elements[i];
        GLushort ib = m_elements[i+1];
        GLushort ic = m_elements[i+2];
        glm::vec3 normal = glm::normalize(glm::cross(
                                                     glm::vec3(m_vertices[ib]) - glm::vec3(m_vertices[ia]),
                                                     glm::vec3(m_vertices[ic]) - glm::vec3(m_vertices[ia])));
        m_normals[ia] = m_normals[ib] = m_normals[ic] = normal;
    }
    
    for (int i = 0; i < m_elements.size(); i+=3){
        
    }
    
    std::cout << "Vertices: " << m_vertices.size() << std::endl;
    std::cout << "Normals: " << m_normals.size() << std::endl;
    std::cout << "Indices: " << m_elements.size() << std::endl;
}
