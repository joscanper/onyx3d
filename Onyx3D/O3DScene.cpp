//
//  O3DScene.cpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 18/04/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#include "O3DScene.hpp"
#include <iostream>

using namespace o3d;


Scene_ptr O3DScene::g_activeScene = nullptr;


O3DScene::O3DScene() :
    m_root(std::make_shared<O3DSceneNode>("Root")),
    m_activeCamera(nullptr),
    m_lighting()
{
}

void O3DScene::update(){
    m_root->updateChildren();
}

void O3DScene::add(SceneNode_ptr node){
    m_root->addChild(node);
    
    if (m_idmap.find(node->getId()) != m_idmap.end())
        throw (("O3DScene : An object with the id " + std::string(node->getId()) + " already exists in the scene").c_str());

    m_idmap[node->getId()] = node;
    
}

