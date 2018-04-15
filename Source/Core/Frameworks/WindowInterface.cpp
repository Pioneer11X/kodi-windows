//
//  FrameworkInterface.cpp
//  Kodi
//
//  Created by Sravan Karuturi on 28-03-18.
//  Copyright © 2018 Sravan Karuturi. All rights reserved.
//

#include "WindowInterface.h"

namespace kodi {
    
    void FrameworkInterface::SetWindowParameters(GLint _width, GLint _height, std::string _title) {
        
        this->windowSettings.windowWidth     =   (_width     >   0) ? _width :   0;
        this->windowSettings.windowHeight    =   (_height    >   0) ? _height: 0;
        this->windowSettings.windowTitle     =   (_title);
    };
    
}
