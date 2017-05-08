//
//  O3DCamera.cpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 18/04/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#include "O3DCamera.hpp"
#include "O3DCore.hpp"


using namespace o3d;

O3DCamera::O3DCamera(const char* id) :
    O3DGameObject(id){
    setPerspective(45, O3D().getScreenSize().x/O3D().getScreenSize().y, 0.01f, 5000.0f);
}

void O3DCamera::setOrtho(float size, float zNear, float zFar){
    m_projection = glm::ortho(-size, size, -size, size, zNear, zFar);
}

void O3DCamera::setPerspective(float fovy,float aspect,float zNear,float zFar){
    m_projection = glm::perspective(fovy, aspect, zNear, zFar);
}

const glm::mat4 O3DCamera::getViewMatrix(){
    if (Transform_ptr parent = getParentTransform())
        return parent->getModelMatrix() * getViewRotationMatrix() * getViewTranslationMatrix() ;
    else
        return getViewRotationMatrix() * getViewTranslationMatrix();
}

const glm::mat4& O3DCamera::getProjectionMatrix(){
    return m_projection;
}
