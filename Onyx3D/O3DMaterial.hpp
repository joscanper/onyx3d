//
//  O3DMaterial.hpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 20/04/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#ifndef O3DMaterial_hpp
#define O3DMaterial_hpp

#include "O3DDefines.hpp"
#include "O3DShader.hpp"
#include "O3DTexture.hpp"
#include "O3DCubeMap.hpp"

#include <string>
#include <map>

namespace o3d {
  
    DEFINE_CLASS_PTR(O3DMaterial, Material);
    
    enum MaterialRenderingMode{
        Opaque = 0,
        Transparent = 1,
        Cutout = 2
    };
    
    class O3DMaterial{
    public:
        
        DEFINE_CLASS_PTR(Property, Property);
        
        enum PropertyType{
            VEC4,
            VEC3,
            VEC2,
            FLOAT,
            INT,
            TEXTURE,
            CUBEMAP
        };
        
        class Property{
        public:
            PropertyType type;
            Property(PropertyType t) : type(t) {};
            virtual ~Property(){};
        };
        
        template< typename T >
        class PropertyValue : public Property{
        public:
            T value;
            PropertyValue(PropertyType t, T val) :
                Property(t),
                value(val)
            {}
            ~PropertyValue(){};
        };
        
        template< typename T >
        class TexturePropertyValue : public Property{
        public:
            TexturePropertyValue(PropertyType t, T tex, GLuint i) :
                Property(t),
                texture(tex),
                index(i)
            {}
            ~TexturePropertyValue(){};
            T texture;
            GLuint index;
        };
        
        explicit O3DMaterial(Shader_ptr shader, MaterialRenderingMode mode) :
            m_shader(shader),
            m_render_mode(mode)
        {
        };
        
        virtual ~O3DMaterial(){ DELETE_NOTIF("MATERIAL"); }
        
        void setShader(const Shader_ptr& shader){ m_shader = shader; }
        Shader_ptr getShader(){ return m_shader; }
        
        void setVector2(const char* id, glm::vec2 v){ m_properties[id] = Property_ptr(new PropertyValue<glm::vec2>(VEC2, v)); }
        void setVector3(const char* id, glm::vec3 v){ m_properties[id] = Property_ptr(new PropertyValue<glm::vec3>(VEC3, v)); }
        void setVector4(const char* id, glm::vec4 v){ m_properties[id] = Property_ptr(new PropertyValue<glm::vec4>(VEC4, v)); }
        void setFloat(const char* id, float v){ m_properties[id] = Property_ptr(new PropertyValue<float>(FLOAT, v)); }
        void setInt(const char* id, int v){ m_properties[id] = Property_ptr(new PropertyValue<int>(INT, v)); }
        void setColor(const char* id, glm::vec4 c){ setVector4(id, c); }
        void setTexture(const char* id, Texture_ptr t, GLuint index){ m_properties[id] = Property_ptr(new TexturePropertyValue<Texture_ptr>(TEXTURE, t, index)); }
        void setCubemap(const char* id, CubeMap_ptr map, GLuint index){ m_properties[id] = Property_ptr(new TexturePropertyValue<CubeMap_ptr>(CUBEMAP, map, index)); }
        
        void use(Shader_ptr shader = nullptr);
        MaterialRenderingMode getRenderingMode(){ return m_render_mode; }
        
        static MaterialRenderingMode getRenderingMode(const char* mode){
            
            
            MaterialRenderingMode mat_mode = MaterialRenderingMode::Opaque;
            if (mode==nullptr)
                return mat_mode;
            std::cout << "MODE: >" << mode << "<" << std::endl;
            if (strcmp(mode, "TRANSPARENT") == 0){
                mat_mode = MaterialRenderingMode::Transparent;
            }else if (strcmp(mode, "CUTOUT") == 0){
                mat_mode = MaterialRenderingMode::Cutout;
            }
            return mat_mode;
        }
        
    private:
        std::map<std::string, Property_ptr> m_properties;
        Shader_ptr m_shader;
        MaterialRenderingMode m_render_mode;
    };
}

#endif /* O3DMaterial_hpp */
