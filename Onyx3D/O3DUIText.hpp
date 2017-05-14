//
//  O3DUIText.hpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 14/05/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#ifndef O3DUIText_hpp
#define O3DUIText_hpp

#include <string>
#include "O3DUIRect.hpp"

namespace o3d {
    DEFINE_CLASS_PTR(O3DUIText, UIText);
    
    class O3DUIText : public O3DUIRect {
    public:
        O3DUIText(const char* id, const char* text, float x, float y, float w, float h) :
        O3DUIRect(id, x, y, w, h),
        m_text(text)
        {
            
        }
        
        void setText(std::string text){ m_text = text; }
        std::string getText(){ return m_text; }
    private:
        std::string m_text;
        
    };
}
#endif /* O3DUIText_hpp */
