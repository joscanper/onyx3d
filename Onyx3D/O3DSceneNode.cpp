//
//  O3DSceneNode.cpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 18/04/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#include "O3DSceneNode.hpp"
#include "O3DScene.hpp"

#include <iostream>

using namespace o3d;

O3DSceneNode::O3DSceneNode(const char* id) :
    m_id(id),
    m_active(true)
{
}

void O3DSceneNode::addChild(const SceneNode_ptr& node){
    if (node->hasParent() && node->getParent() == shared_from_this())
        return;
    
    node->setParent(shared_from_this());
}

void O3DSceneNode::setParent(const SceneNode_ptr& node){
    
    if (hasParent())
        getParent()->removeChild(shared_from_this());
    
    parent = node;
    
    if (hasParent())
        getParent()->children.push_back(shared_from_this());
}

void O3DSceneNode::removeChild(const SceneNode_ptr& node){
    children.erase(std::remove(children.begin(), children.end(), node), children.end());
}

void O3DSceneNode::updateChildren(){
    this->update();
    for(int i = 0; i < children.size(); ++i){
        if (children[i]->isActive()){
            children[i]->updateChildren();
        }
    }
}

void O3DSceneNode::removeAllChildren(){
    children.clear();
}
