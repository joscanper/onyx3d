//
//  O3DTextRenderer.hpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 13/05/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#ifndef O3DTextRenderer_hpp
#define O3DTextRenderer_hpp

#include "O3DDefines.hpp"
#include "O3DRender.hpp"
#include "O3DFont.hpp"
#import <GL/glew.h>

namespace o3d {
    DEFINE_CLASS_PTR(O3DTextRenderer, TextRenderer)
    
    class O3DTextRenderer : public O3DRenderer{
    public:
        O3DTextRenderer();
        
        void render(const glm::mat4& view, const glm::mat4& proj, const Shader_ptr& shader) override;
        
        void setFont(const Font_Wptr& f){
            m_font = f;
        }
        
    private:
        Font_Wptr m_font;
        GLuint m_vao, m_vbo;
    };

}
#endif /* O3DTextRenderer_hpp */
