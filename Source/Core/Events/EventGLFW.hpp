//
//  KE_GLFW.hpp
//  Kodi
//
//  Created by Sravan Karuturi on 28-03-18.
//  Copyright © 2018 Sravan Karuturi. All rights reserved.
//

#pragma once
#include "EventInterface.hpp"

#include <GLFW/glfw3.h>

namespace kodi {
    
    class EventGLFW : public EventInterface {
        
    public:
        
        EventGLFW();
        
    private:
        GLFWwindow * window;
        
    };
    
}


