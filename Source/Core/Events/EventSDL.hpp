//
//  KE_SDL.hpp
//  Kodi
//
//  Created by Sravan Karuturi on 28-03-18.
//  Copyright © 2018 Sravan Karuturi. All rights reserved.
//

#pragma once
#include "EventInterface.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

namespace kodi {
    
    class EventSDL : public EventInterface {
        
    public:
        
        EventSDL();
        
    private:
        SDL_GLContext context;
        SDL_Window *window;
        SDL_Event windowEvent;
        
    };
    
}


