//
//  O3DResources.cpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 23/04/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#include "O3DResources.hpp"

using namespace o3d;

void O3DResources::init(){
    
    createShader("o3d_shaders/default", "resources/shaders/default.vert","resources/shaders/default.frag");
    createShader("o3d_shaders/unlit", "resources/shaders/basic.vert","resources/shaders/unlit.frag");
    createShader("o3d_shaders/unlit_color", "resources/shaders/basic.vert","resources/shaders/unlit_color.frag");
    createShader("o3d_shaders/skybox", "resources/shaders/skybox.vert","resources/shaders/skybox.frag");
    createShader("o3d_shaders/ui", "resources/shaders/ui.vert","resources/shaders/ui.frag");
    
    
    createTexture("o3d_textures/white", "resources/textures/white.png");
    createTexture("o3d_textures/black", "resources/textures/black.png");
    createTexture("o3d_textures/normal", "resources/textures/normal.png");
    
    createCubemap("o3d_cubemaps/white", {
        "resources/textures/white.png",
        "resources/textures/white.png",
        "resources/textures/white.png",
        "resources/textures/white.png",
        "resources/textures/white.png",
        "resources/textures/white.png"
    });
    
    
    createFont("o3d_fonts/default", "resources/fonts/Consolas.ttf");
    
    Material_ptr text_mat = std::make_shared<O3DMaterial>(getShader("o3d_shaders/ui"), MaterialRenderingMode::Opaque);
    addMaterial("o3d_materials/ui", text_mat);
    
    m_default_mat = std::make_shared<O3DDefaultMaterial>();
    addMaterial("o3d_materials/default", m_default_mat);
    
}
