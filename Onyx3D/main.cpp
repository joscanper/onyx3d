//
//  main.cpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 17/04/2017.
//  Copyright (c) 2017 Josue Candela. All rights reserved.
//

#include <iostream>
#include "O3DCore.hpp"
#include "O3DInput.hpp"
#include "O3DCamera.hpp"
#include "O3DGameObject.hpp"
#include "O3DScene.hpp"
#include "O3DSceneLoader.hpp"
#include "O3DUILoader.hpp"
#include "O3DModel.hpp"

#include "O3DTextRenderer.hpp"

#include <GL/glew.h>



const GLint WIDTH = 1024;
const GLint HEIGHT = 768;

using namespace o3d;

void showFPS(){
    static float time;
    time += O3D().getElapsedTime();
    
    if (time > 1){
        int fps = (int)O3D().getFPS();
        std::string sfps = std::to_string(fps) + "fps";
        std::string render = "Render:" + std::to_string(O3D().getRenderer().getRenderTime(fps));
        std::string drawc = "Draw calls: " + std::to_string(O3D().getRenderer().getDrawCalls());
        
        O3D().getUI().getObjectById<O3DUIText>("textFPS")->setText(sfps);
        O3D().getUI().getObjectById<O3DUIText>("textRender")->setText(render);
        O3D().getUI().getObjectById<O3DUIText>("textDrawCalls")->setText(drawc);
        
        time = 0;
    }
}

int main() {
    
    if (!O3D().init(WIDTH, HEIGHT, "Onyx3D Engine")){
        std::cout << "Failed to initialize Onyx3D" << std::endl;
        return -1;
    }
    
    
    //std::string scene_path = "resources/scenes/demo_dungeon.lua";
    std::string scene_path = "resources/scenes/test_ssao.lua";
    
    O3DUILoader::load("resources/ui/test.lua");
    
    Scene_ptr scene = O3DSceneLoader::load(scene_path.c_str());
    Camera_ptr camera = scene->getObjectById<O3DCamera>("main_camera");
    GameObject_ptr pivot = scene->getObjectById<O3DGameObject>("pivot");
    
    
    O3D().getRenderer().getMotionBlur().setEnabled(false);
    
    //Shader_ptr font_s = std::make_shared<O3DShader>("resources/shaders/text.vert","resources/shaders/text.frag");
    //O3DTextRenderer tr;
    //tr.setFont(font);
    //glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);
    
    
    bool wasFocused = true;
    float camspeed= 0;
    int reload = 0;
    while(O3D().running()){
        
        // Camera movement
        
        float mult = 1;
        if (O3DInput::isKeyPressed(Keys::Space))
            mult = 10;
        if (O3DInput::isKeyPressed(Keys::W))
            camera->translate(glm::vec3(0,0,-0.01*mult));
        if (O3DInput::isKeyPressed(Keys::S))
            camera->translate(glm::vec3(0,0,0.01*mult));
        if (O3DInput::isKeyPressed(Keys::A))
            camspeed -= 0.1f;
        if (O3DInput::isKeyPressed(Keys::D))
            camspeed += 0.1f;
        if (O3DInput::isKeyPressed(Keys::E))
            camera->rotate(glm::vec3(1,0,0));
        if (O3DInput::isKeyPressed(Keys::Q))
            camera->rotate(glm::vec3(-1,0,0));
    
        if (O3DInput::isKeyPressed(Keys::ArrowUp))
            camera->translate(glm::vec3(0,0.01*mult,0));
        if (O3DInput::isKeyPressed(Keys::ArrowDown))
            camera->translate(glm::vec3(0,-0.01*mult,0));
        if (O3DInput::isKeyPressed(Keys::ArrowRight))
            camera->translate(glm::vec3(0.01*mult,0,0));
        if (O3DInput::isKeyPressed(Keys::ArrowLeft))
            camera->translate(glm::vec3(-0.01*mult,0,0));
        
        camera->rotate(glm::vec3(0,camspeed,0));
        if (camspeed>0)
            camspeed-=0.01f;
        if (camspeed<0)
            camspeed+=0.01f;
        if (O3DInput::isKeyPressed(Keys::Numpad_4))
            pivot->rotate(glm::vec3(0,1,0));
        if (O3DInput::isKeyPressed(Keys::Numpad_6))
            pivot->rotate(glm::vec3(0,-1,0));
        
        
        
        if (O3DInput::isKeyPressed(Keys::R))
            reload = 2;
        
        /*
         if (O3DInput::isKeyPressed(Keys::Numpad_7))
         go->getTransform()->translate(glm::vec3(0,-0.1,0));
         if (O3DInput::isKeyPressed(Keys::Numpad_1))
         go->getTransform()->translate(glm::vec3(0,0.1,0));
         //if (O3DInput::isKeyPressed(Keys::Numpad_9))*/
        
        
        
        O3D().update();
        
        
        
        
        if (O3D().isFocused()){
            O3D().render();
            
            
            if (!wasFocused){
                reload = 1;
                wasFocused = true;
            }
            
            
            showFPS();
        }else{
            wasFocused = false;
        }
        
        
        if (reload){
            camspeed = 0;
            glm::vec3 prev_cam_pos = camera->getPosition();
            glm::vec3 prev_cam_rot = camera->getRotation();
            
            O3D().getResources().reloadDefaultShader();
            O3DUILoader::load("resources/ui/test.lua");
            
            scene = O3DSceneLoader::load(scene_path.c_str(), true, reload == 2);
            camera = scene->getObjectById<O3DCamera>("main_camera");
            camera->setPosition(prev_cam_pos);
            camera->setRotation(prev_cam_rot);
            
            pivot = scene->getObjectById<O3DGameObject>("pivot");
            reload = 0;
        }
    }
    
    O3D().terminate();
    
    return 1;
}
