//
//  O3DModelProxy.h
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 26/04/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#ifndef O3DModelProxy_hpp
#define O3DModelProxy_hpp

#include "O3DDefines.hpp"
#include "O3DModel.hpp"
#include "O3DScene.hpp"
#include <memory>

namespace o3d {
    DEFINE_CLASS_PTR(O3DModelProxy,ModelProxy);
    
    class O3DModelProxy : public O3DGameObject{
    public:
        O3DModelProxy(const char* id) : O3DGameObject(id){};
        
        void setProxy(const Model_ptr& model){
            children.clear();
            
        }
        
        
    private:
        
    };
}

#endif /* O3DModelProxy_h */
