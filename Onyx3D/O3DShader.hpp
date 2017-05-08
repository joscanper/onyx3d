//
//  O3DShader.hpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 18/04/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#ifndef O3DShader_hpp
#define O3DShader_hpp

#include "O3DDefines.hpp"

#include <GL/glew.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include <iostream>
#include <fstream>

using namespace std;

namespace o3d
{
    DEFINE_CLASS_PTR(O3DShader,Shader);
    
    class O3DShader
    {
    public:
        
        O3DShader() = delete;
        O3DShader(O3DShader* sh) = delete;
        
        explicit O3DShader(const GLchar* vert_file, const GLchar* frag_file);
        virtual ~O3DShader(){
            glDeleteProgram(m_program);
            DELETE_NOTIF("SHADER");
        };
        
        void fromFile(const GLchar* vert_file, const GLchar* frag_file);
        void vertexFile(const GLchar* vert_file);
        void fragmentFile(const GLchar* frag_file);
        void vertexCode(const GLchar* vert_code);
        void fragmentCode(const GLchar* frag_code);
        
        virtual void use();
        
        void setUniform(const char* name, GLint val);
        void setUniform(const char* name, GLfloat val);
        void setUniform(const char* name, glm::vec2 v);
        void setUniform(const char* name, glm::vec3 v);
        void setUniform(const char* name, glm::vec4 v);
        void setUniform(const char* name, glm::mat4x4 m);
        
        void setUniformTexture(const char* name, GLuint texture, GLuint index);
        void setUniformCubemap(const char* name, GLuint texture, GLuint index);
    private:
        
        GLuint m_vs,m_fs;
        GLuint m_program;
        
        bool compile();
        bool compile(GLuint shader, char* id);
        char* readShaderFile(const GLchar* file);
        
    };
    
}

#endif /* O3DShader_hpp */
