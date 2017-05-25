//
//  O3DMeshRenderer.hpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 18/04/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#ifndef O3DMeshRenderer_hpp
#define O3DMeshRenderer_hpp

#include <GL/glew.h>

#include "O3DDefines.hpp"
#include "O3DRenderer.hpp"
#include "O3DMesh.hpp"

namespace o3d {
    DEFINE_CLASS_PTR(O3DMeshRenderer, MeshRenderer);
    
    class O3DMeshRenderer : public O3DRenderer{
       
    public:
        
        O3DMeshRenderer();
        ~O3DMeshRenderer(){
            DELETE_NOTIF("MESH RENDERER");
        };
        
        void release();
        void render(const glm::mat4& view, const glm::mat4& proj, const Shader_ptr& shader) override;
        
        Mesh_ptr getMesh() { return m_mesh; }
        void setMesh(const Mesh_ptr& m, bool generateAO = false){
            m_mesh = m;
            if (generateAO)
                m_mesh->generateVAO();
        }
        
        void copy(MeshRenderer_ptr other){
            setMaterial(other->getMaterial());
            m_mesh = other->m_mesh;
        }
        
    protected:
        Mesh_ptr m_mesh;
        
    
        
    };
}
#endif /* O3DMeshRenderer_hpp */
