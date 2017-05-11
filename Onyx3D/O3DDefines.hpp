//
//  O3DDefines.hpp
//  Onyx3D
//
//  Created by Josue Candela Perdomo on 25/04/2017.
//  Copyright © 2017 Josue Candela. All rights reserved.
//

#ifndef O3DDefines_h
#define O3DDefines_h

#include <iostream>

#define DEFINE_CLASS_PTR(C,N)           \
    class C;                            \
    typedef std::shared_ptr<C>  N##_ptr;  \
    typedef std::weak_ptr<C>    N##_Wptr; \
    typedef std::unique_ptr<C>  N##_Uptr;


#define NOTIF_DELETIONS 0

#define DELETE_NOTIF(N)             \
    if (NOTIF_DELETIONS)            \
        std::cout << "## DELETED " <<  N << std::endl;


#endif /* O3DDefines_h */
