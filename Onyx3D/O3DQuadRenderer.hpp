//
//  O3DQuadRenderer.hpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 18/04/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#ifndef O3DQuadRenderer_hpp
#define O3DQuadRenderer_hpp

#include "O3DMeshRenderer.hpp"

namespace o3d {
    DEFINE_CLASS_PTR(O3DQuadRenderer, QuadRenderer);
    
    class O3DQuadRenderer : public O3DMeshRenderer{
    public:
        O3DQuadRenderer(float sizex=0.5f, float sizey=0.5f);
    };
}

#endif /* O3DQuadRenderer_hpp */
