//
//  O3DGridRenderer.hpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 22/04/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#ifndef O3DGridRenderer_hpp
#define O3DGridRenderer_hpp

#include "O3DMeshRenderer.hpp"

namespace o3d {
    DEFINE_CLASS_PTR(O3DGridRenderer, GridRenderer)
    
    class O3DGridRenderer : public O3DMeshRenderer{
    public:
        O3DGridRenderer();
        O3DGridRenderer(int cellsizex, int cellsizey, int cellnumx, int cellnumy);
        
        void initGrid(int cellsizex, int cellsizey, int cellnumx, int cellnumy);
        void render(const glm::mat4& view, const glm::mat4& proj, const Shader_ptr& shader) override;
    };
}
#endif /* O3DGridRenderer_hpp */
