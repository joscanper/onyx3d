//
//  O3DSkyRenderer.cpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 26/05/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#include "O3DSkyRenderer.hpp"
#include "O3DCore.hpp"

using namespace o3d;

O3DSkyRenderer::O3DSkyRenderer() : O3DMeshRenderer() {
    generateSkyGeometry();
};

void O3DSkyRenderer::generateSkyGeometry(){
    Model_ptr skydome = O3D().getResources().getModel("o3d_models/skydome");
    GameObject_ptr go = skydome->getSubModel("Skydome");
    m_mesh = go->getComponent<O3DMeshRenderer>()->getMesh();
}

void O3DSkyRenderer::render(const glm::mat4& view, const glm::mat4& proj, const Shader_ptr& shader){
    Light_ptr sun = O3DScene::getActiveScene()->getLighting().getSun();
    shader->setUniform("sunDir", sun->getPosition());
    O3DMeshRenderer::render(view, proj, shader);
}
