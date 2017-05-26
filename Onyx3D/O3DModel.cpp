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

#include <boost/algorithm/string.hpp>


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
}

void O3DModel::processNode(aiNode* node, const aiScene* scene)
{
    
    // Process all the node's meshes (if any)
    for(GLuint i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        
        std::vector<string> strs;
        std::string name = node->mName.C_Str();
        boost::split(strs, name, boost::is_any_of("."));
        const char* id = strs[0].c_str();
        
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
    
    
    if (!assimp_mesh->HasTangentsAndBitangents())
        std::cout << "WARNING: Model doesn't have tangents" << std::endl;
    
    for(GLuint i = 0; i < assimp_mesh->mNumVertices; i++)
    {
        aiVector3D p = assimp_mesh->mVertices[i];
        aiVector3D n = assimp_mesh->mNormals[i];
        
        
        O3DVertex vertex;
        vertex.m_position = glm::vec3(p.x,p.y,p.z);
        vertex.m_normal = glm::normalize(glm::vec3(n.x,n.y,n.z));
        
        if (assimp_mesh->HasTangentsAndBitangents()){
            aiVector3D t = assimp_mesh->mTangents[i];
            vertex.m_tangent = glm::vec3(t.x,t.y,t.z);
        }
        
        if (assimp_mesh->HasTextureCoords(0)){
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

