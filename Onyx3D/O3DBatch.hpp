//
//  O3DBatch.hpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 25/05/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#ifndef O3DBatch_hpp
#define O3DBatch_hpp

#include "O3DDefines.hpp"
#include "O3DGameObject.hpp"
#include "O3DMaterial.hpp"
#include "O3DMeshRenderer.hpp"
#include <vector>

namespace o3d {
    DEFINE_CLASS_PTR(O3DBatch, Batch);
    
    class O3DBatch {
    public:
        O3DBatch(const char* id) : m_id(id){}
        
        void add(GameObject_ptr go){
            m_objects.push_back(go);
        }
        
        const char* getId(){ return m_id; }
        
        void setMaterial(Material_ptr m){ m_material = m; }
        Material_ptr getMaterial(){ return m_material; }
        
        GameObject_ptr generate(){
            m_mesh = std::make_shared<O3DMesh>();
            MeshRenderer_ptr go_renderer;
            for(auto go : m_objects){
                batch(go);
            }
            
            GameObject_ptr go = std::make_shared<O3DGameObject>(m_id);
            
            MeshRenderer_ptr mr = std::make_shared<O3DMeshRenderer>();
            mr->setMaterial(m_material);
            mr->setMesh(m_mesh);
            m_mesh->generateVAO();
            
            go->addComponent(mr);
            
            return go;
        }
    private:
        const char* m_id;
        std::vector<GameObject_ptr> m_objects;
        Material_ptr m_material;
        Mesh_ptr m_mesh;
        
        void batch(GameObject_ptr go){
            MeshRenderer_ptr go_renderer = go->getComponent<O3DMeshRenderer>();
            
            if (go_renderer){
                std::cout << "batched: " << go->getId() << std::endl;
                Mesh_ptr go_mesh = go_renderer->getMesh();
                unsigned long indexOffset = m_mesh->vertices.size();
                for (auto v : go_mesh->vertices){
                    v.m_position = glm::vec3(go->getModelMatrix() * glm::vec4(v.m_position,1));
                    m_mesh->vertices.push_back(v);
                }
                for (auto i : go_mesh->indices){
                    m_mesh->indices.push_back(i + indexOffset);
                }
                
            }
            
            for (int i = 0; i < go->childrenCount(); ++i)
                if (GameObject_ptr child_go = std::dynamic_pointer_cast<O3DGameObject>(go->getChild(i)))
                    batch(child_go);
        }
    };
}
#endif /* O3DBatch_hpp */
