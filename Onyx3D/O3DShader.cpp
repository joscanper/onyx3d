//
//  O3DShader.cpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 18/04/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#include "O3DShader.hpp"
#include <glm/gtc/type_ptr.hpp>

using namespace o3d;

O3DShader::O3DShader(const GLchar* vert_file, const GLchar* frag_file)
{
    m_program = 0;
    fromFile(vert_file, frag_file);
    compile();
}


void O3DShader::fromFile(const GLchar* vert_file, const GLchar* frag_file)
{
    vertexFile(vert_file);
    fragmentFile(frag_file);
}


void O3DShader::vertexFile(const GLchar* vert_file)
{
    char* vertSrc = readShaderFile(vert_file);
    if (vertSrc != NULL)
        vertexCode(vertSrc);
    delete[] vertSrc;
}

void O3DShader::fragmentFile(const GLchar* frag_file)
{
    char* fragSrc = readShaderFile(frag_file);
    if (fragSrc != NULL)
        fragmentCode(fragSrc);
    delete[] fragSrc;
}

void O3DShader::vertexCode(const GLchar* vert_code)
{
    m_vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(m_vs, 1, &vert_code, NULL);
}

void O3DShader::fragmentCode(const GLchar* frag_code)
{
    m_fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(m_fs, 1, &frag_code, NULL);
}

bool O3DShader::compile()
{
    if (!compile(m_vs, "[Vertex Shader]")) return false;
    if (!compile(m_fs, "[Fragment Shader]")) return false;
    
    // Create a program object and attach the two compiled shaders
    m_program = glCreateProgram();
    glAttachShader(m_program, m_vs);
    glAttachShader(m_program, m_fs);
    
    // Link the program object and print out the info log
    glLinkProgram(m_program);
    GLint success;
    glGetProgramiv(m_program, GL_LINK_STATUS, &success);
    if (!success)
    {
        string log_str = "O3DShader : Error while linking shaders";
        std::cout << log_str << std::endl;
        GLchar infoLog[512];
        glGetProgramInfoLog(m_program, 512, NULL, infoLog);
        std::cout << infoLog;
        return false;
    }
    /*
    GLenum wasError = glGetError();
    if(wasError){
        string log_str = "O3DShader : Error compiling shader";
        std::cout << log_str << std::endl;
        GLchar infoLog[512];
        glGetProgramInfoLog(m_program, 512, NULL, infoLog);
        std::cout << infoLog;
        return false;
    }
    */
    
    glDeleteShader(m_vs);
    glDeleteShader(m_fs);
    
    return true;
}

bool O3DShader::compile(GLuint shader, char* id)
{
    glCompileShader(shader);
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        GLchar infoLog[512];
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "O3DShader : Error while compile shader" << ": " << id << std::endl;
        std::cout << infoLog << std::endl;
        return false;
    }
    return true;
}


void O3DShader::use()
{
    glUseProgram(m_program);
}


char* O3DShader::readShaderFile(const GLchar *fn)
{
    FILE *fp;
    char *content = NULL;
    long count=0;
    
    if (fn != NULL) {
        
        fp = fopen(fn,"rt");
        
        if (fp != NULL) {
            
            fseek(fp, 0, SEEK_END);
            count = ftell(fp);
            rewind(fp);
            if (count > 0) {
                content = (char *)malloc(sizeof(char) * (count+1));
                count = fread(content,sizeof(char),count,fp);
                content[count] = '\0';
            }
            fclose(fp);
            if (content == NULL)
            {
                string log_str = "O3DShader : The file was empty : ";
                log_str += fn;
                std::cout << log_str << std::endl;
            }
        }else{
            string log_str = "O3DShader : File not found : ";
            log_str += fn;
            std::cout << log_str << std::endl;
        }
    }
    
    return content;
}


void O3DShader::setUniform(const char* name, GLint val){
    GLuint loc = glGetUniformLocation(m_program, name);
    glUniform1i(loc, val);
}
    
void O3DShader::setUniform(const char* name, GLfloat val){
    GLuint loc = glGetUniformLocation(m_program, name);
    glUniform1f(loc, val);
}
void O3DShader::setUniform(const char* name, glm::vec2 v){
    GLuint loc = glGetUniformLocation(m_program, name);
    glUniform2f(loc, v.x, v.y);
}
void O3DShader::setUniform(const char* name, glm::vec3 v){
    GLuint loc = glGetUniformLocation(m_program, name);
    glUniform3f(loc, v.x, v.y, v.z);
}
void O3DShader::setUniform(const char* name, glm::vec4 v){
    GLuint loc = glGetUniformLocation(m_program, name);
    glUniform4f(loc, v.r, v.g, v.b, v.a);
}
void O3DShader::setUniform(const char* name, glm::mat4x4 m){
    GLuint loc = glGetUniformLocation(m_program, name);
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(m));
}
void O3DShader::setUniformTexture(const char* name, GLuint t, GLuint index){
    
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, t);
    glUniform1i(glGetUniformLocation(m_program, name), index);
}
void O3DShader::setUniformCubemap(const char* name, GLuint t, GLuint index){
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_CUBE_MAP, t);
    glUniform1i(glGetUniformLocation(m_program, name), index);
}
