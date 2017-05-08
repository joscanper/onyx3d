//
//  O3DTransform.cpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 18/04/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#include "O3DTransform.hpp"
#include "O3DGameObject.hpp"

#include <iostream>
#include <memory>
#include <math.h>

using namespace o3d;


O3DTransform::O3DTransform(const char* id) :
    O3DSceneNode(id),
    m_model_dirty(true),
    m_rotation_dirty(true),
    m_position(glm::vec3(0,0,0)),
    m_rotation(glm::vec3(0,0,0)),
    m_scale(glm::vec3(1,1,1)),
    m_model_matrix(),
    m_rotation_matrix()
{
    
}


glm::mat4 O3DTransform::getModelMatrix(){
    
    if (m_model_dirty || m_rotation_dirty){
        m_model_matrix = generateModelMatrix();
        m_model_dirty = false;
    }
    
    if (hasParent()){
        if (Transform_ptr t = getParentTransform())
            return t->getModelMatrix() * m_model_matrix;
    }
    
    return m_model_matrix;
}

glm::mat4 O3DTransform::generateModelMatrix(){
    glm::mat4 translation = getTranslationMatrix();
    glm::mat4 rotation = getRotationMatrix();
    glm::mat4 scale = getScaleMatrix();
    return translation * rotation * scale;
}

glm::mat4 O3DTransform::getScaleMatrix(){
    glm::mat4 s = glm::mat4();
    glm::vec3 scale = getLocalScale();
    s[0][0] = scale.x;
    s[1][1] = scale.y;
    s[2][2] = scale.z;
    return s;
}

glm::mat4 O3DTransform::getTranslationMatrix(){
    glm::mat4 t = glm::mat4();
    glm::vec3 pos = getLocalPosition();
    t[3][0] = pos.x;
    t[3][1] = pos.y;
    t[3][2] = pos.z;
    return t;
}

glm::mat4 O3DTransform::getRotationMatrix(){
    if (m_rotation_dirty){
        glm::vec3 rot = getLocalRotation();
        m_rotation_matrix = getRollMatrix(rot.z) * getYawMatrix(rot.y) * getPitchMatrix(rot.x);
        m_rotation_dirty = false;
        m_model_dirty = true;
    }
    
    return m_rotation_matrix;
}

glm::mat4 O3DTransform::getYawMatrix(float angle){
    glm::mat4 yaw = glm::mat4();
    yaw[0][0] = cos( angle );
    yaw[0][2] = -sin( angle );
    yaw[2][0] = sin( angle );
    yaw[2][2] = cos( angle );
    return yaw;
}

glm::mat4 O3DTransform::getPitchMatrix(float angle){
    glm::mat4 pitch = glm::mat4();
    pitch[1][1] = cos( angle );
    pitch[2][1] = -sin( angle );
    pitch[1][2] = sin( angle );
    pitch[2][2] = cos( angle );
    return pitch;
}

glm::mat4 O3DTransform::getRollMatrix(float angle){
    glm::mat4 roll = glm::mat4();
    roll[0][0] = cos( angle );
    roll[1][0] = -sin( angle );
    roll[0][1] = sin( angle );
    roll[1][1] = cos( angle );
    return roll;
}

void O3DTransform::setPosition(glm::vec3 p){
    m_model_dirty = true;
    if (Transform_ptr t = getParentTransform())
        m_position = glm::inverse(t->getModelMatrix()) * glm::vec4(p,1);
    else
        m_position = p;
}


void O3DTransform::setScale(glm::vec3 s){
    m_model_dirty = true;
    if (Transform_ptr t = getParentTransform())
        m_scale = 1.0f/t->getScale() * s;
    else
        m_scale = s;
}

void O3DTransform::setRotation(glm::vec3 r){
    m_rotation_dirty = true;
    if (Transform_ptr t = getParentTransform())
        m_rotation = glm::inverse(t->getModelMatrix()) * glm::vec4(glm::radians(r),1);
    else
        m_rotation = glm::radians(r);
}


void O3DTransform::setLocalPosition(glm::vec3 p){
    m_model_dirty = true;
    m_position = p;
}


void O3DTransform::setLocalScale(glm::vec3 s){
    m_model_dirty = true;
    m_scale = s;
}

void O3DTransform::setLocalRotation(glm::vec3 r){
    m_rotation_dirty = true;
    m_rotation = glm::radians(r);
}

void O3DTransform::rotate(glm::vec3 v){
    m_rotation += glm::radians(v);
    m_rotation_dirty = true;
}


void O3DTransform::scale(glm::vec3 v){
    m_model_dirty = true;
    m_scale *= v;
}


void O3DTransform::translate(glm::vec3 v){
    m_model_dirty = true;
    glm::vec4 mov = glm::vec4(v,1) * getRotationMatrix();
    m_position += glm::vec3(mov);
}

Transform_ptr O3DTransform::getParentTransform(){
    if (!hasParent()) return nullptr;
    return std::dynamic_pointer_cast<O3DTransform>(getParent());
}

glm::vec3 O3DTransform::getDirection(){
    if (Transform_ptr t = getParentTransform())
        return glm::vec3(t->getModelMatrix() * getRotationMatrix()[2]);
    else
        return getRotationMatrix()[2];
}

glm::vec3 O3DTransform::getPosition(){
    if (Transform_ptr t = getParentTransform())
        return glm::vec3( t->getModelMatrix() * glm::vec4(m_position,1));
    else
        return m_position;
}
glm::vec3 O3DTransform::getRotation(){
    if (Transform_ptr t = getParentTransform())
        return glm::degrees(glm::vec3( t->getModelMatrix() * glm::vec4(m_rotation,1)));
    else
        return glm::degrees(m_rotation);
}
glm::vec3 O3DTransform::getScale(){
    if (Transform_ptr t = getParentTransform())
        return t->getScale() * m_scale;
    else
        return m_scale;
}
