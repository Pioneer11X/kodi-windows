//
//  vec2.h
//  Kodi
//
//  Created by Sravan Karuturi on 11-04-18.
//  Copyright © 2018 Sravan Karuturi. All rights reserved.
//

#ifndef vec2_h
#define vec2_h

namespace kodi
{
    // vector with 2 pieces of data
    template <typename T>
    struct vec2
    {
        typedef T value_type;
        
        // unify the different sets of data in one area in memory
        union
        {
            struct { T x, y; };
            struct { T r, g; };
            struct { T width, height; };
            struct { T major, minor; };
        };
    };
}



#endif /* vec2_h */
