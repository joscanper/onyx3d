//
//  O3DInput.hpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 20/04/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#ifndef O3DInput_hpp
#define O3DInput_hpp

#include "O3DCore.hpp"

namespace o3d {
    
    
    /* Namespace with enumeration of keyboard keys. */
    namespace Keys
    {
        enum
        {
            NoKey =				-1,
            
            A =					'A',
            B =					'B',
            C =					'C',
            D =					'D',
            E =					'E',
            F =					'F',
            G =					'G',
            H =					'H',
            I =					'I',
            J =					'J',
            K =					'K',
            L =					'L',
            M =					'M',
            N =					'N',
            O =					'O',
            P =					'P',
            Q =					'Q',
            R =					'R',
            S =					'S',
            T =					'T',
            U =					'U',
            V =					'V',
            W =					'W',
            X =					'X',
            Y =					'Y',
            Z =					'Z',
            
            Num0 =				'0',
            Num1 =				'1',
            Num2 =				'2',
            Num3 =				'3',
            Num4 =				'4',
            Num5 =				'5',
            Num6 =				'6',
            Num7 =				'7',
            Num8 =				'8',
            Num9 =				'9',
            
            Backspace =			8,
            Tab =				9,
            //Caps =				20,
            //CapsLock =			20,
            //ShiftLock =			20,
            
            Return =			13,
            Enter =				13,
            
            //Shift =				16,
            
            //Ctrl =				17,
            //Control =			17,
            
            Pause =				19,
            
            Escape =			27,
            Space =				32,
            SpaceBar =			32,
            
            PageUp =			105,
            PageDown =			104,
            End =				107,
            Home =				106,
            
            Left =				100,
            Up =				101,
            Right =				102,
            Down =				103,
            
            Insert =		    108,
            Delete =			127,
            
            //Windows =			91,			/* Windows-flag key. */
            //Shortcut =			93,			/* Shortcut menu key, usually between Alt Gr and Ctrl. */
            
            /* Numpad keys. */
            /* Windows?
            Numpad_0 =			48,
            Numpad_1 =			49,
            Numpad_2 =			50,
            Numpad_3 =			51,
            Numpad_4 =			52,
            Numpad_5 =			53,
            Numpad_6 =			54,
            Numpad_7 =			55,
            Numpad_8 =			56,
            Numpad_9 =			57,
            */
            Numpad_0 =			320,
            Numpad_1 =			321,
            Numpad_2 =			322,
            Numpad_3 =			323,
            Numpad_4 =			324,
            Numpad_5 =			325,
            Numpad_6 =			326,
            Numpad_7 =			327,
            Numpad_8 =			328,
            Numpad_9 =			329,
            
            /* Numeric keyboard part keys. */
            Asterisk =			42,		/* Asterisk key right of Num Lock. */
            Minus =				45,		/* Minus key right of Num Lock. */
            Plus =				43,		/* Plus key right of Num Lock. */
            Add =				43,
            Slash =				47,		/* Slash key right of Num Lock. */
            Dot =               46,      /* Dot key right of Num Lock. */
            
            /* Function keys. */
            F1 =				1,
            F2 =				2,
            F3 =				3,
            F4 =				4,
            F5 =				5,
            F6 =				6,
            F7 =				7,
            F8 =				8,
            F9 =				9,
            F10 =				10,
            F11 =				11,
            F12 =				12,
            
            //NumLock =			144,
            
            ArrowLeft =				263,
            ArrowUp =				265,
            ArrowRight =			262,
            ArrowDown =				264,
            
            /* Media keyboard keys. */
            Next =				176,
            Forward =			176,
            Previous =			177,
            Stop =				178,
            Continue =			179,
            PauseMedia =		179,
            
            Special =			500, /* Special key on media keyboards, can be media, calculator, ... */
            
            /* Non-ASCII-based keys */
            //LeftAlt =			800,
            //RightAlt =			801,
            //AltGr =				801
        };
    }
    
    class O3DInput{
    public:
        static bool isKeyPressed(int key){
            return glfwGetKey(O3D().getWindow(), key) == GLFW_PRESS;
        }
    };
}
#endif /* O3DInput_hpp */
