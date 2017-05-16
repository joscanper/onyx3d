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


using namespace o3d;

O3DModel::O3DModel(const char*id) : O3DGameObject(id){}

void O3DModel::load(const char* path){

    std::string err;
   
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(O3D().getResources().getResourcesPath(path).c_str(), aiProcess_Triangulate | aiProcess_CalcTangentSpace);
    
    std::cout << "Loading model: " << path << std::endl;
    
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        cout << "ERROR::ASSIMP::" << importer.GetErrorString() << endl;
        return;
    }
    //this->directory = path.substr(0, path.find_last_of('/'));
    
    this->processNode(scene->mRootNode, scene);
    
    /*
    bool ret = tinyobj::LoadObj(&atts, &shapes, &materials, &err, );

    
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
                
                
                glm::vec3 edge1 = face[1].m_position - face[0].m_position;
                glm::vec3 edge2 = face[2].m_position - face[0].m_position;
                glm::vec2 deltaUV1 = face[1].m_texcoord - face[0].m_texcoord;
                glm::vec2 deltaUV2 = face[2].m_texcoord - face[0].m_texcoord;
                
                GLfloat f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);
                
                glm::vec3 tangent = (edge1 * deltaUV2.y   - edge2 * deltaUV1.y) * f;
                glm::vec3 bitangent = (edge2 * deltaUV1.x   - edge1 * deltaUV2.x) * f;
            
                for (char vi = 0; vi < 3; ++vi){
                    face[vi].m_tangent = tangent;
                    face[vi].m_bitangent = bitangent;
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
    */
    
}

void O3DModel::processNode(aiNode* node, const aiScene* scene)
{
    
    // Process all the node's meshes (if any)
    for(GLuint i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        const char* id = node->mName.C_Str();
        GameObject_ptr go = this->processSubModel(id, mesh, scene);
        m_submodels[id] = go;
    }
    // Then do the same for each of its children
    for(GLuint i = 0; i < node->mNumChildren; i++)
    {
         this->processNode( node->mChildren[i], scene);
    }
}

GameObject_ptr O3DModel::processSubModel(const char* id, aiMesh *assimp_mesh, const aiScene *scene)
{
    
    std::cout << "Submodel: " << id << std::endl;
    GameObject_ptr go = O3DScene::createObject<O3DGameObject>(id);
    MeshRenderer_ptr r = std::make_shared<O3DMeshRenderer>();
    go->addComponent(r);
    Mesh_ptr mesh = std::make_shared<O3DMesh>();
    
    for(GLuint i = 0; i < assimp_mesh->mNumVertices; i++)
    {
        aiVector3D p = assimp_mesh->mVertices[i];
        aiVector3D n = assimp_mesh->mNormals[i];
        aiVector3D t = assimp_mesh->mTangents[i];
        
        
        O3DVertex vertex;
        vertex.m_position = glm::vec3(p.x,p.y,p.z);
        vertex.m_normal = glm::normalize(glm::vec3(n.x,n.y,n.z));
        vertex.m_tangent = glm::vec3(t.x,t.y,t.z);
        if (assimp_mesh->mTextureCoords[0]){
            aiVector3D uv = assimp_mesh->mTextureCoords[0][i];
            vertex.m_texcoord = glm::vec2(uv.x, uv.y);
        }
        
        mesh->vertices.push_back(vertex);
    }
    
    
    
    for(GLuint i = 0; i < assimp_mesh->mNumFaces; i++)
    {
        aiFace face = assimp_mesh->mFaces[i];
        for(GLuint j = 0; j < face.mNumIndices; j++)
            mesh->indices.push_back(face.mIndices[j]);
    }
    
    r->setMaterial(O3D().getResources().getDefaultMaterial());
    r->setMesh(mesh, true);
    go->setParent(shared_from_this());
    
    return go;
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

