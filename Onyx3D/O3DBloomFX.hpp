//
//  O3DBloomFX.hpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 10/05/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#ifndef O3DBloomFX_hpp
#define O3DBloomFX_hpp


#include "O3DPostProFX.hpp"

namespace o3d {
 
    class O3DBloomFX : public O3DPostProFX {
    public:
        void init(int w, int h){
            Shader_ptr s = std::make_shared<O3DShader>("resources/shaders/screen.vert", "resources/shaders/bloom.frag");
            O3DPostProFX::init(s, w, h);
        }
    };
}

#endif /* O3DBloomFX_hpp */
