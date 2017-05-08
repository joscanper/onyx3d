//
//  O3DRenderer.hpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 27/04/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#ifndef O3DRenderer_hpp
#define O3DRenderer_hpp

#include "O3DDefines.hpp"
#include "O3DCamera.hpp"
#include "O3DMaterial.hpp"
#include "O3DComponent.hpp"

#include <stdio.h>

namespace o3d {
    
    DEFINE_CLASS_PTR(O3DRenderer,Renderer);
    
    class O3DRenderer : public O3DComponent{
    public:
        O3DRenderer();
        
        virtual void render(const glm::mat4& view, const glm::mat4& proj, const Shader_ptr& shader) = 0;
        void update() override {};
        
        void setMaterial(Material_ptr m){ m_material = m; }
        virtual Material_ptr getMaterial(){ return m_material; }
        
        void setMVP(const glm::mat4& view, const glm::mat4& proj, const Shader_ptr& shader);
    private:
        Material_ptr m_material;
    };
}

#endif /* O3DIRenderer_hpp */
