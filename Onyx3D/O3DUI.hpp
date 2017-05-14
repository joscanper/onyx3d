//
//  O3DUI.hpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 14/05/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#ifndef O3DUI_hpp
#define O3DUI_hpp

#include <stdio.h>
#include <unordered_map>

#include "O3DUIDraw.hpp"
#include "O3DUIText.hpp"

namespace o3d{
    class O3DUI{
    public:
        O3DUI();
        
        void render();
        
        void update();
        
        void add(SceneNode_ptr node);
        
        void clear();
        
        template<class T>
        std::shared_ptr<T> getObjectById(const char * id){
            
            SceneNode_ptr so = m_idmap[id];
            try{
                if(so == nullptr)
                    throw ("O3DUI : UI object with id " + std::string(id) + " not found ").c_str();
                
                if(std::shared_ptr<T> obj = std::dynamic_pointer_cast<T>(so))
                    return obj;
                else
                    throw ("O3DUI : UI object with id " + std::string(id) + " is not of the type " + typeid(T).name()).c_str();
                
            }catch(const char msg){
                std::cout << msg << std::endl;
                return nullptr;
            }
        }
        
        UIRect_ptr createRect(const char* id, int x, int y, int w, int h);
        UIDraw_ptr createDraw(const char* id, const char* texture, int x, int y, int w, int h);
        UIText_ptr createText(const char* id, const char* txt, int x, int y, int w, int h);
    private:
        
        void renderNode(SceneNode_ptr node);
        
        glm::mat4 m_view;
        glm::mat4 m_projection;
        
        SceneNode_ptr   m_root;
        std::unordered_map<std::string, SceneNode_ptr> m_idmap;
    };
}

#endif /* O3DUI_hpp */
