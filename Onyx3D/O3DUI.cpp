//
//  O3DUI.cpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 14/05/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#include "O3DUI.hpp"
#include "O3DGameObject.hpp"
#include "O3DCore.hpp"

#include "O3DImageRenderer.hpp"
#include "O3DTextRenderer.hpp"



using namespace o3d;

O3DUI::O3DUI() : m_root(std::make_shared<O3DSceneNode>("Root")){}


void O3DUI::render(){
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    m_projection = glm::ortho(0.0f, O3D().getScreenSize().x, 0.0f, O3D().getScreenSize().y);
    renderNode(m_root);
}


void O3DUI::clear(){
    m_root->removeAllChildren();
    m_idmap.clear();
}

void O3DUI::update(){
    m_root->updateChildren();
}

void O3DUI::add(SceneNode_ptr node){
    m_root->addChild(node);
    
    if (m_idmap.find(node->getId()) != m_idmap.end())
        throw (("O3DUI : An object with the id " + std::string(node->getId()) + " already exists in the scene").c_str());
    
    m_idmap[node->getId()] = node;
}

void O3DUI::renderNode(SceneNode_ptr node){
    for (int i = 0; i < node->childrenCount(); i++){
        SceneNode_ptr child = node->getChild(i);
        GameObject_ptr go = std::dynamic_pointer_cast<O3DGameObject>(child);
        if (go){
            if (Renderer_ptr r = go->getComponent<O3DRenderer>()){
                r->getMaterial()->use();
                r->render(m_view, m_projection, r->getMaterial()->getShader());
            }
        }
        
        renderNode(child);
    }
}

UIRect_ptr O3DUI::createRect(const char* id, int x, int y, int w, int h){
    UIRect_ptr rect = std::make_shared<O3DUIRect>(id, x, y, w, h);
    QuadRenderer_ptr quadRend = std::make_shared<O3DQuadRenderer>();
    rect->addComponent(quadRend);
    add(rect);
    return rect;
}

UIText_ptr O3DUI::createText(const char* id, const char* txt, int x, int y, int w, int h){
    UIText_ptr text = std::make_shared<O3DUIText>(id,txt,x,y,w,h);
    TextRenderer_ptr textRend = std::make_shared<O3DTextRenderer>();
    text->addComponent(textRend);
    add(text);
    return text;
}

UIDraw_ptr O3DUI::createDraw(const char* id, const char* texture, int x, int y, int w, int h){
    Texture_ptr tptr = O3D().getResources().getTexture(texture);
    UIDraw_ptr d = std::make_shared<O3DUIDraw>(id, tptr, x, y, w, h);
    ImageRenderer_ptr imgRend = std::make_shared<O3DImageRenderer>(w, h);
    d->addComponent(imgRend);
    add(d);
    return d;
}
