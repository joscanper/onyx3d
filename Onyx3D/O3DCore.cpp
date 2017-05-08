//
//  O3DCore.cpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 18/04/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#include "O3DCore.hpp"
#include <iostream>
#include <GLFW/glfw3.h>

using namespace o3d;


O3DCore::O3DCore() :
    m_resources(),
    m_screenSize(0,0)
{
    
}

O3DCore::~O3DCore(){
    
}

void O3DCore::terminate(){
    glfwTerminate();
}



int O3DCore::init(GLint width, GLint height, const char* window_name)
{
    glfwInit();
    
    glfwSetErrorCallback([] (int a_iError, const char* a_szDiscription) {
        printf("GLFW Error occurred, Error ID: %i, Description: %s\n", a_iError, a_szDiscription);
    });
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    m_window = glfwCreateWindow(width, height, window_name, nullptr, nullptr);
    if (m_window == nullptr){
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(m_window);
    
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK){
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }
    
    GLint w, h;
    glfwGetFramebufferSize(m_window, &w, &h);
    glViewport(0,0,w,h);
    m_screenSize.x = w;
    m_screenSize.y = h;

    m_render.init(w, h);
    
    glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        //std::cout << "Pressed: " << key << " : " << action << std::endl;
    });
    
    glfwSetWindowFocusCallback(m_window, window_focus_callback);
    
    m_resources.init();
    
    return 1;
}


bool O3DCore::running(){
    return !glfwWindowShouldClose(m_window);
}

void O3DCore::update(){
    float time =glfwGetTime();
    m_elapsedTime = time - m_latestTime;
    m_latestTime = time;
    
    m_fpsTime += m_elapsedTime;
    m_fpsFrames += 1;
    if (m_fpsTime > 1){
        std::cout << m_fpsFrames << "fps" << std::endl;
        m_fps = m_fpsFrames;
        m_fpsTime = 0;
        m_fpsFrames = 0;
    }
    
    //O3DScene::getActiveScene()->update();
    
    glfwSwapBuffers(m_window);
    glfwPollEvents();
}

void O3DCore::render(){
    m_render.render();
}



