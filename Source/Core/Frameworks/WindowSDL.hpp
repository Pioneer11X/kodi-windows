//
//  KE_SDL.hpp
//  Kodi
//
//  Created by Sravan Karuturi on 28-03-18.
//  Copyright © 2018 Sravan Karuturi. All rights reserved.
//

#pragma once
#include "WindowInterface.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

namespace kodi {
    
    class KE_SDL : public FrameworkInterface {
        
    public:
        
        KE_SDL();
        
    protected:
        
        void Init();
        bool PollEvents();
        void SwapBuffers();
        void CleanUp();
        bool IsWindowOpen() const;
        
    private:
        SDL_GLContext context;
        SDL_Window *window;
        SDL_Event windowEvent;
        
        bool isOpen;
        Uint64 startingTime;
    };
    
}


