//
//  EventInterface.hpp
//  Kodi
//
//  Created by Sravan Karuturi on 11-04-18.
//  Copyright © 2018 Sravan Karuturi. All rights reserved.
//

#pragma once

#include <stdio.h>
#ifndef GLEW_STATIC
#define GLEW_STATIC
#include <GL/glew.h>
#endif

#include <vector>
#include <map>

#include "KeyboardDefinitions.h"
#include "MouseDefinitions.h"

namespace kodi {
    class EventInterface{
    public:
        void Construct();
        
        virtual int GetKeyNumber(int key);
        virtual int GetMouseButtonNumber(int key);
        
    protected:
        
        std::multimap<int, int> keyTranslations;
        std::multimap<int, int> mouseButtonTranslations;
        
    };
}

