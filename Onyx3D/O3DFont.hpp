//
//  O3DFont.hpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 13/05/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#ifndef O3DFont_hpp
#define O3DFont_hpp

#include "O3DDefines.hpp"
#include <GL/glew.h>
#include <iostream>
#include <unordered_map>
#include <glm/glm.hpp>
#include <freetype2/ft2build.h>
#include <freetype2/freetype/freetype.h>


struct Character {
    GLuint     textureID;  // ID handle of the glyph texture
    glm::ivec2 size;       // Size of glyph
    glm::ivec2 bearing;    // Offset from baseline to left/top of glyph
    GLuint     advance;    // Offset to advance to next glyph
};

namespace o3d {
    DEFINE_CLASS_PTR(O3DFont, Font);
    
    class O3DFont{
    public:
        
        O3DFont(const char* path = "resources/fonts/Consolas.ttf"){
            
            FT_Library ft;
            if (FT_Init_FreeType(&ft))
            std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
            
            FT_Face face;
            if (FT_New_Face(ft, path, 0, &face))
            std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
            
            FT_Set_Pixel_Sizes(face, 0, 12);
            
            
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction
            
            for (GLubyte c = 0; c < 128; c++)
            {
                // Load character glyph
                if (FT_Load_Char(face, c, FT_LOAD_RENDER))
                {
                    std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
                    continue;
                }
                // Generate texture
                GLuint texture;
                glGenTextures(1, &texture);
                glBindTexture(GL_TEXTURE_2D, texture);
                glTexImage2D(
                             GL_TEXTURE_2D,
                             0,
                             GL_RED,
                             face->glyph->bitmap.width,
                             face->glyph->bitmap.rows,
                             0,
                             GL_RED,
                             GL_UNSIGNED_BYTE,
                             face->glyph->bitmap.buffer
                             );
                // Set texture options
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                // Now store character for later use
                Character character = {
                    texture,
                    glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                    glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                    (GLuint)face->glyph->advance.x
                };
                m_characters.insert(std::pair<GLchar, Character>(c, character));
            }
            
            FT_Done_Face(face);
            FT_Done_FreeType(ft);
            
            std::cout << "Font loaded : " << path << std::endl;
        }
        
        Character getCharacter(GLchar c){ return m_characters[c]; }
    private:
        std::unordered_map<GLchar, Character> m_characters;
    };
}

#endif /* O3DFont_hpp */
