//
//  O3DScene.hpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 18/04/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//
#ifndef O3DScene_hpp
#define O3DScene_hpp

#include "O3DDefines.hpp"
#include "O3DSceneNode.hpp"
#include "O3DGameObject.hpp"
#include "O3DLighting.hpp"
#include "O3DCamera.hpp"


#include <iostream>
#include <string>
#include <unordered_map>



namespace o3d {
    
    DEFINE_CLASS_PTR(O3DScene,Scene);
    
    class O3DScene{
   
    public:
        explicit O3DScene();
        ~O3DScene(){
            DELETE_NOTIF("SCENE");
        }
        
        O3DLighting& getLighting(){ return m_lighting; }
        const SceneNode_ptr getRoot(){ return m_root; }
        
        Camera_ptr getActiveCamera() { return m_activeCamera; }
        void setActiveCamera(Camera_ptr cam) { m_activeCamera = cam; }
        
        template<class ObjectType>
        static std::shared_ptr<ObjectType> createObject(const char* id){
            std::shared_ptr<ObjectType> obj = std::make_shared<ObjectType>(id);
            return obj;
        }
        
        static Camera_ptr createCamera(const char*id, bool active = true){
            Camera_ptr cam = createObject<O3DCamera>(id);
            if (active && g_activeScene != nullptr)
                g_activeScene->setActiveCamera(cam);
            return cam;
        }
        
        void add(SceneNode_ptr node);
        
        template<class T>
        std::shared_ptr<T> getObjectById(const char * id){
            
            SceneNode_ptr so = m_idmap[id];
            try{
                if(so == nullptr)
                    throw ("O3DScene : Scene object with id " + std::string(id) + " not found ").c_str();
                
                if(std::shared_ptr<T> obj = std::dynamic_pointer_cast<T>(so))
                    return obj;
                else
                    throw ("O3DScene : Scene object with id " + std::string(id) + " is not of the type " + typeid(T).name()).c_str();
                    
            }catch(const char msg){
                std::cout << msg << std::endl;
                return nullptr;
            }
        }
        
        // ---------- Scene Management ---------- // 
        static void loadScene(const char* scenepath);
        static void setActiveScene(Scene_ptr scene){ g_activeScene = scene; }
        static Scene_ptr getActiveScene(){ return g_activeScene; }
        
        void update();
    private:
        
        static Scene_ptr g_activeScene;

        Camera_ptr      m_activeCamera;
        SceneNode_ptr   m_root;
        
        O3DLighting     m_lighting;
        
        std::unordered_map<std::string, SceneNode_ptr> m_idmap;
    };
}



#endif /* O3DScene_hpp */
