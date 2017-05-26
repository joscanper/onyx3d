//
//  O3DSkyRenderer.hpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 26/05/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//


#ifndef O3DSkyRenderer_hpp
#define O3DSkyRenderer_hpp

#include "O3DMeshRenderer.hpp"
#include "O3DModel.hpp"


namespace o3d {
    DEFINE_CLASS_PTR(O3DSkyRenderer, SkyRenderer)
    
    class O3DSkyRenderer : public O3DMeshRenderer{
    public:
        O3DSkyRenderer();
        
        virtual void generateSkyGeometry();
        void render(const glm::mat4& view, const glm::mat4& proj, const Shader_ptr& shader) override;
    };
}

#endif /* O3DSkyRenderer_hpp */
