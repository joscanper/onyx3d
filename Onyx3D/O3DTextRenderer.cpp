//
//  O3DTextRenderer.cpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 13/05/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#include "O3DTextRenderer.hpp"
#include "O3DCore.hpp"

using namespace o3d;

O3DTextRenderer::O3DTextRenderer() : O3DRenderer() {
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    setMaterial(O3D().getResources().getMaterial("o3d_materials/ui"));
    setFont(O3D().getResources().getFont("o3d_fonts/default"));
};

void O3DTextRenderer::render(const glm::mat4& view, const glm::mat4& proj, const Shader_ptr& shader){

    setMVP(view, proj, shader);
    
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(m_vao);
    
    // Iterate through all characters
    std::string::const_iterator c;
    
    GameObject_ptr go = getGO();
    //glm::vec3 go_scale = go->getScale();
    
    float x = 0;
    float y = 0;
    float scalex = 1;//go_scale.x;
    float scaley = 1;//go_scale.y;
    
    std::string text = "";
    if (UIText_ptr uitext = std::dynamic_pointer_cast<O3DUIText>(go)){
        text = uitext->getText();
        shader->setUniform("color", uitext->getColor());
    }
    
    if (Font_ptr f = m_font.lock()){
        for (c = text.begin(); c != text.end(); c++)
        {
            Character ch = f->getCharacter(*c);
            
            GLfloat xpos = x + ch.bearing.x * scalex;
            GLfloat ypos = y - (ch.size.y - ch.bearing.y) * scaley;
            
            GLfloat w = ch.size.x * scalex;
            GLfloat h = ch.size.y * scaley;
            // Update VBO for each character
            GLfloat vertices[6][4] = {
                { xpos,     ypos + h,   0.0, 0.0 },
                { xpos,     ypos,       0.0, 1.0 },
                { xpos + w, ypos,       1.0, 1.0 },
                
                { xpos,     ypos + h,   0.0, 0.0 },
                { xpos + w, ypos,       1.0, 1.0 },
                { xpos + w, ypos + h,   1.0, 0.0 }
            };
            // Render glyph texture over quad
            glBindTexture(GL_TEXTURE_2D, ch.textureID);
            // Update content of VBO memory
            glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            // Render quad
            glDrawArrays(GL_TRIANGLES, 0, 6);
            // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
            x += (ch.advance >> 6) * scalex; // Bitshift by 6 to get value in pixels (2^6 = 64)
        }
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}
