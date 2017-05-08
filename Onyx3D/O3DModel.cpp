//
//  O3DModel.cpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 24/04/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#include "O3DCore.hpp"
#include "O3DModel.hpp"
#include "O3DScene.hpp"
#include "O3DGameObject.hpp"
#include "O3DMeshRenderer.hpp"

#include <glm/glm.hpp>
#include <iostream>
#include <string>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

using namespace o3d;

O3DModel::O3DModel(const char*id) : O3DGameObject(id){}

void O3DModel::load(const char* path){
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    tinyobj::attrib_t atts;
    std::string err;
    
    bool ret = tinyobj::LoadObj(&atts, &shapes, &materials, &err, path);
    
    
    if (!ret){
        if(!err.empty()){
            std::cerr << err << std::endl;
        }
        return;
    }
    
    std::cout << "The model has :" << shapes.size() << " shapes" << std::endl;
    for (int i = 0; i < shapes.size(); i++) {
        //O3DMesh m;
        
        GameObject_ptr go = O3DScene::createObject<O3DGameObject>(shapes[i].name.c_str());
        MeshRenderer_ptr r = std::make_shared<O3DMeshRenderer>();
        go->addComponent(r);
        Mesh_ptr mesh = std::make_shared<O3DMesh>();
        
        std::cout << "Loading mesh:" << shapes[i].name << std::endl;
        
        std::vector<tinyobj::index_t> indices = shapes[i].mesh.indices;
        unsigned long n = indices.size();
        char face_vertices = 0;
        O3DVertex face[3];
        for (unsigned long  j= 0; j < n; j++){
            
            glm::vec3 vertex;
            vertex.x = atts.vertices[indices[j].vertex_index*3];
            vertex.y = atts.vertices[indices[j].vertex_index*3+1];
            vertex.z = atts.vertices[indices[j].vertex_index*3+2];
            
            glm::vec2 texcoord(0,0);
            if (atts.texcoords.size()>0){
                texcoord.x = atts.texcoords[indices[j].texcoord_index*2];
                texcoord.y = atts.texcoords[indices[j].texcoord_index*2+1];
            }
            
            glm::vec3 normal;
            if (atts.normals.size()>0){
                normal.x = atts.normals[indices[j].normal_index*3];
                normal.y = atts.normals[indices[j].normal_index*3+1];
                normal.z = atts.normals[indices[j].normal_index*3+2];
            }
            
            O3DVertex v = O3DVertex(vertex, glm::vec3(), normal, texcoord);
            
            face[face_vertices] = v;
            face_vertices++;
            if (face_vertices == 3){
                glm::vec3 tangent = mesh->calculateTangent(face[0],face[1],face[2]);
                for (char vi = 0; vi < 3; ++vi){
                    face[vi].m_tangent = tangent;
                    mesh->vertices.push_back(face[vi]);
                }
                face_vertices = 0;
            }
            
        }
        r->setMaterial(O3D().getResources().getDefaultMaterial());
        r->setMesh(mesh, true);
        go->setParent(shared_from_this());
        m_submodels[shapes[i].name] = go;
    }
    
    std::cout << "Loaded model" << std::endl;
}

Model_ptr O3DModel::instantiate(const char* id){
    Model_ptr m = std::make_shared<O3DModel>(id);
    copyChildren(std::dynamic_pointer_cast<O3DGameObject>(shared_from_this()),  m);
    return m;
}

void O3DModel::copyChildren(GameObject_ptr fromnode, GameObject_ptr tonode){
    for(int i = 0; i < fromnode->childrenCount(); ++i)
    {
        GameObject_ptr fromgo = std::dynamic_pointer_cast<O3DGameObject>(fromnode->getChild(i));
        if (fromgo != nullptr){
            GameObject_ptr go = O3DScene::createObject<O3DGameObject>(fromgo->getId().c_str());
            MeshRenderer_ptr fromr = fromgo->getComponent<O3DMeshRenderer>();
            MeshRenderer_ptr r = std::make_shared<O3DMeshRenderer>();
            r->copy(fromr);
            go->addComponent(r);
            go->setParent(tonode);
            
            copyChildren(fromgo,go);
        }
    }
}

GameObject_ptr O3DModel::getSubModel(const char* id){
    return m_submodels[id];
}
