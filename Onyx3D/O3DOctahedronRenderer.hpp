//
//  O3DOctahedronRenderer.hpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 22/04/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#ifndef O3DOctahedronRenderer_hpp
#define O3DOctahedronRenderer_hpp

#include "O3DMeshRenderer.hpp"

namespace o3d {
    DEFINE_CLASS_PTR(O3DOctahedronRenderer, OctahedronRenderer)
    
    class O3DOctahedronRenderer : public O3DMeshRenderer{
    public:
        O3DOctahedronRenderer();
    };
}
#endif /* O3DOctahedronRenderer_hpp */
