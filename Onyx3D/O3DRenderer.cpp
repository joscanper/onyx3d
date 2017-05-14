//
//  O3DRenderer.cpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 27/04/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#include "O3DCore.hpp"
#include "O3DRenderer.hpp"

using namespace o3d;

O3DRenderer::O3DRenderer() : m_material(O3D().getResources().getDefaultMaterial()) {}

void O3DRenderer::setMVP(const glm::mat4& view, const glm::mat4& proj, const Shader_ptr& shader){
    Shader_ptr s = shader == nullptr ? m_material->getShader() : shader;
    GameObject_ptr go = getGO();
    if (go != nullptr)
        s->setUniform("model", go->getModelMatrix());
    s->setUniform("view", view);
    s->setUniform("projection", proj);
}
