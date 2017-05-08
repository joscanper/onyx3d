//
//  O3DGameObject.hpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 18/04/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#include "O3DDefines.hpp"
#include "O3DTransform.hpp"
#include "O3DComponent.hpp"
#include "O3DSceneNode.hpp"

#include <vector>
#include <iostream>

#ifndef O3DGameObject_hpp
#define O3DGameObject_hpp

namespace o3d {
    DEFINE_CLASS_PTR(O3DGameObject, GameObject)
    
    class O3DGameObject : public O3DTransform{
    public:
        O3DGameObject(const char* id) : O3DTransform(id){};
        ~O3DGameObject(){
            DELETE_NOTIF("GAMEOBJECT");
        }
        
        template<class T>
        std::shared_ptr<T> getComponent(){
            for(int i = 0; i< m_components.size(); ++i)
                if (std::shared_ptr<T> ptr = std::dynamic_pointer_cast<T>(m_components[i]))
                    return ptr;
            return nullptr;
        }
        /*
        template<class T, typename... Args>
        std::shared_ptr<T> addComponent(Args... args){
            std::shared_ptr<T> c = std::make_shared<T>(shared_from_thisargs);
        }
        */
        
        void addComponent(Component_ptr c){
            m_components.push_back(c);
            
            // TODO - CHANGE THIS! , it's fucking ugly!!
            c->m_gameobject = std::dynamic_pointer_cast<O3DGameObject>(shared_from_this());
            c->onAttach();
        }
        
        
        void update() override{
            updateComponents();
        }
        
    private:
        std::vector<Component_ptr> m_components;
        void updateComponents(){
            for(int i = 0; i < m_components.size(); ++i){
                m_components[i]->update();
            }
        }
    };
}

#endif /* O3DGameObject_hpp */
