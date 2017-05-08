//
//  O3DCubeRenderer.hpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 20/04/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#ifndef O3DCubeRenderer_hpp
#define O3DCubeRenderer_hpp

#include "O3DMeshRenderer.hpp"

namespace o3d {
    DEFINE_CLASS_PTR(O3DCubeRenderer, CubeRenderer);
    
    class O3DCubeRenderer : public O3DMeshRenderer{
    public:
        O3DCubeRenderer();
    };
}

#endif /* O3DCubeRenderer_hpp */
