//
//  O3DDefaultMaterial.h
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 25/04/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#ifndef O3DDefaultMaterial_h
#define O3DDefaultMaterial_h

#include "O3DMaterial.hpp"

namespace o3d {
    DEFINE_CLASS_PTR(O3DDefaultMaterial, DefaultMaterial);
    
    class O3DDefaultMaterial : public O3DMaterial {
    public:
        explicit O3DDefaultMaterial(MaterialRenderingMode mode = MaterialRenderingMode::Opaque);
    };
}

#endif /* O3DDefaultMaterial_h */
