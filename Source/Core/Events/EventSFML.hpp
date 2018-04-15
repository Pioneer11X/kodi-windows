//
//  KE_SFML.hpp
//  Kodi
//
//  Created by Sravan Karuturi on 28-03-18.
//  Copyright © 2018 Sravan Karuturi. All rights reserved.
//

#pragma once
#include "EventInterface.hpp"

#include <SFML/Window.hpp>

namespace kodi {
    
    class EventSFML : public EventInterface {
        
    public:
        
        EventSFML();
        
    private:
        sf::Window * window;
        
    };
    
}


