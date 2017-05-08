//
//  O3DSceneNode.hpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 18/04/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//


#ifndef O3DSceneNode_hpp
#define O3DSceneNode_hpp

#include "O3DDefines.hpp"

#include <string>
#include <vector>

namespace o3d {
    DEFINE_CLASS_PTR(O3DSceneObject, SceneObject)
    DEFINE_CLASS_PTR(O3DSceneNode, SceneNode)
    
    class O3DSceneObject;
    
    class O3DSceneNode : public std::enable_shared_from_this<O3DSceneNode>{
    
    public:
        explicit O3DSceneNode(const char* id);
        virtual ~O3DSceneNode(){
            DELETE_NOTIF("SCENENODE");
        };
        
        void addChild(const SceneNode_ptr& node);
        void removeChild(const SceneNode_ptr& node);

        void setActive(bool active){ this->m_active = active; }
        bool isActive(){ return m_active; }
        
        void setParent(const SceneNode_ptr& node);
        SceneNode_ptr getParent(){
            if (parent.expired())
                throw("The pointer expired");
            return parent.lock();
        }
        
        bool hasParent(){
            return !parent.expired();
        }
        
        std::string getId(){ return m_id; }
        
        int childrenCount() { return (int)children.size(); }
        SceneNode_ptr getChild(int index){ return children[index]; }
        
        virtual void update(){};
        void updateChildren();
        
    protected:
        SceneNode_Wptr parent;
        std::vector<SceneNode_ptr> children;
        
    private:
        std::string m_id;
        bool m_active;
        
    };
}

#endif /* O3DSceneNode_hpp */
