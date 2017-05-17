//
//  O3DCamera.hpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 18/04/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#ifndef O3DCamera_hpp
#define O3DCamera_hpp

#include "O3DDefines.hpp"
#include "O3DSceneNode.hpp"
#include "O3DGameObject.hpp"

#include <glm/glm.hpp>

#include <iostream>

namespace o3d {
    DEFINE_CLASS_PTR(O3DCamera, Camera)
    
    class O3DCamera :  public O3DGameObject{
        
    public:
        O3DCamera(const char* id);
        ~O3DCamera(){
            DELETE_NOTIF("CAMERA");
        }
        
        void setOrtho(float size,float zNear, float zFar);
        void setPerspective(float fovy,float aspect,float zNear,float zFar);
        
        const glm::mat4 getViewMatrix();
        const glm::mat4& getProjectionMatrix();
        
        void update() override{}
        
        void lookAt(glm::vec3 pos){ m_projection = glm::lookAt(getPosition(), pos, glm::vec3(0,1,0)); }
    
        glm::vec3 getLocalRotation() override{
            glm::vec3 r =  O3DTransform::getLocalRotation();
            return glm::vec3(r.x, -r.y, r.z);
        }
        void translate(glm::vec3 v) override{
            glm::vec3 newpos = getLocalPosition() + glm::vec3(glm::vec4(v,1) * getViewRotationMatrix());
            setPosition(newpos);
        };
        
        glm::mat4 getViewRotationMatrix(){
            // TODO - Use a flag to avoid computing this all the time
            glm::vec3 rot = O3DTransform::getLocalRotation();
            return getRollMatrix(-rot.z) * getYawMatrix(rot.y) * getPitchMatrix(-rot.x);
        }
        
        glm::mat4 getViewTranslationMatrix(){
            glm::vec3 pos = getLocalPosition();
            glm::mat4 translation;
            translation[3][0] = -pos.x;
            translation[3][1] = -pos.y;
            translation[3][2] = -pos.z;
            return translation;
        }
        
        void invertPitch(){
            glm::vec3 rot = O3DTransform::getLocalRotation();
            rot.x = -rot.x;
            setLocalRotation(rot);
        }
        
        glm::vec4 getClippingPlane(){ return m_clippingPlane; }
        void setClippingPlane(glm::vec4 plane){ m_clippingPlane = plane; };
    private:
        glm::mat4 m_projection;
        glm::vec4 m_clippingPlane;
    };
    

}
#endif /* O3DCamera_hpp */
