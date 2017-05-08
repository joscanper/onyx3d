//
//  O3DComponent.hpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 18/04/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#ifndef O3DComponent_hpp
#define O3DComponent_hpp

#include "O3DDefines.hpp"
#include <memory>

namespace o3d {
    DEFINE_CLASS_PTR(O3DGameObject, GameObject)
    DEFINE_CLASS_PTR(O3DComponent, Component)

    class O3DComponent{
        friend O3DGameObject;
    public:
        
        virtual ~O3DComponent(){};
        GameObject_ptr getGO(){ return m_gameobject.lock(); }
        
        virtual void update() = 0;
        virtual void onAttach() {};
    private:
        GameObject_Wptr m_gameobject;
    };
}

#endif /* O3DComponent_hpp */
