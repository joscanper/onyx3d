//
//  O3DModel.hpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 24/04/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#ifndef O3DModel_hpp
#define O3DModel_hpp

#include "O3DGameObject.hpp"
#include <unordered_map>

namespace o3d {
    DEFINE_CLASS_PTR(O3DModel, Model);
    
    class O3DModel : public O3DGameObject {
    public:
        O3DModel(const char*id);
        
        
        ~O3DModel(){
            m_submodels.clear();
            DELETE_NOTIF("MODEL");
        }
        
        void load(const char* path);
        GameObject_ptr getSubModel(const char* id);
        
        Model_ptr instantiate(const char* id);
        void copyChildren(GameObject_ptr from, GameObject_ptr to);
        
    private:
        std::unordered_map<std::string, GameObject_ptr> m_submodels;
    };
}
#endif /* O3DModel_hpp */
