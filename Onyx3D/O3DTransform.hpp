//
//  O3DTransform.hpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 18/04/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//


#ifndef O3DTransform_hpp
#define O3DTransform_hpp

#include "O3DDefines.hpp"

#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "O3DSceneNode.hpp"

namespace o3d {
   DEFINE_CLASS_PTR(O3DTransform, Transform)
    
    class O3DTransform : public O3DSceneNode{
    public:
        explicit O3DTransform(const char* id);
        ~O3DTransform(){
            DELETE_NOTIF("TRANSFORM");
        }
        
        void setPosition(glm::vec3);
        void setScale(glm::vec3);
        void setRotation(glm::vec3);
        
        void setLocalPosition(glm::vec3);
        void setLocalScale(glm::vec3);
        void setLocalRotation(glm::vec3);
        
        virtual void translate(glm::vec3);
        void scale(glm::vec3);
        void rotate(glm::vec3);
        
        virtual glm::mat4 getModelMatrix();
        glm::mat4 generateModelMatrix();
        glm::mat4 getTranslationMatrix();
        glm::mat4 getRotationMatrix();
        glm::mat4 getScaleMatrix();
        
        static glm::mat4 getYawMatrix(float angle);
        static glm::mat4 getPitchMatrix(float angle);
        static glm::mat4 getRollMatrix(float angle);
        
        glm::vec3 getPosition();
        glm::vec3 getRotation();
        glm::vec3 getScale();
        
        virtual glm::vec3 getLocalPosition(){ return m_position; }
        virtual glm::vec3 getLocalRotation(){ return m_rotation; }
        virtual glm::vec3 getLocalScale(){ return m_scale; }
        
        glm::vec3 getDirection();
        Transform_ptr getParentTransform();
        
    private:
        
        bool m_model_dirty;
        bool m_rotation_dirty;
        
        // This is stored in local
        glm::vec3 m_position;
        glm::vec3 m_rotation;
        glm::vec3 m_scale;
        
        glm::mat4 m_model_matrix;
        glm::mat4 m_rotation_matrix;
    };
}
#endif /* O3DTransform_hpp */
