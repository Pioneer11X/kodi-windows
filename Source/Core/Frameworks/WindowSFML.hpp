//
//  KE_SFML.hpp
//  Kodi
//
//  Created by Sravan Karuturi on 28-03-18.
//  Copyright © 2018 Sravan Karuturi. All rights reserved.
//

#pragma once
#include "WindowInterface.h"

#include <SFML/Window.hpp>

namespace kodi {
    
    class KE_SFML : public FrameworkInterface {
        
    public:
        
        KE_SFML();
        
    protected:
        
        void Init();
        bool PollEvents();
        void SwapBuffers();
        void CleanUp();
        bool IsWindowOpen() const;
        
    private:
        sf::Window * window;
        
        sf::Clock clock;
        
        sf::Uint64 startingTime;
        
    };
    
}


