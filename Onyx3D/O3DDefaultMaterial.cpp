//
//  O3DDefaultMaterial.cpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 25/04/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#include "O3DCore.hpp"
#include "O3DDefaultMaterial.hpp"

using namespace o3d;

O3DDefaultMaterial::O3DDefaultMaterial(bool transparent) :
    O3DMaterial(O3D().getResources().getShader("o3d_shaders/default"), transparent)
{
    
    setColor("color", glm::vec4(0.8,0.8,0.8,1));
    setTexture("diffuse", O3D().getResources().getTexture("o3d_textures/white"), 0);
    setTexture("specular", O3D().getResources().getTexture("o3d_textures/black"), 1);
    setTexture("normal", O3D().getResources().getTexture("o3d_textures/normal"), 2);
    setCubemap("environment", O3D().getResources().getCubemap("o3d_cubemaps/white"), 3);
    setFloat("shininess", 1);
    setFloat("reflectivity", 0);
    setFloat("fresnel", 0);
}
