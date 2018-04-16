//
//  CoreEngine.hpp
//  Kodi
//
//  Created by Sravan Karuturi on 28-03-18.
//  Copyright © 2018 Sravan Karuturi. All rights reserved.
//
#pragma once

#ifndef CoreEngine_hpp
#define CoreEngine_hpp

#include "../DEFINITIONS.h"

#include "Frameworks/WindowInterface.h"

// TODO: How can we only include stuff that we need? Can we?
// TODO: పైగా మనం ఇక్కడ ఫ్రేమువర్కు ఇంటరుఫేసుని మొత్తం నాలుగుసార్లు పెడుతున్నాం.
// TODO: మనకు కావలిసినవి మాత్రమే పెట్టేటట్టు చూడు.
#include "Frameworks/WindowSDL.hpp"
#include "Frameworks/WindowSFML.hpp"
#include "Frameworks/WindowGLFW.hpp"

#include "Shader.hpp"
#include "Texture.h"

#include <map>

#include "CoreEvents.hpp"

namespace kodi {
    
    class CoreEngine{
        
        std::map<std::string, std::string> vertexShaderFiles;
        std::map<std::string, std::string> fragmentShaderFiles;
        std::map<std::string, Shader * > ShaderDictionary;

		// ఒక vector చేసి పెట్టు వీటిని. మనం ఒక folder లోంచి ఒకేసారి అన్నీ load చేసి పెట్టుకోవచ్చు
		Texture * texture;

        // ఆ ఒక్క దానికి.
        unsigned int VBO, VAO, EBO;
      
    public:
        // Constructor.
        CoreEngine(int framework = 0);
        
        // Initialise the Framework.
        bool Init();
        
        // Game Loop Run, Every Frame.
        bool GameLoop();
        
        // is the window still open. Returns true if it is
        bool WindowIsOpen( ) const;
        
        // Cleanup
        void Cleanup();
        
        CoreEvents *getEvents( ) { return this->coreEvents; }
        
    private:

        FrameworkInterface * frameworkPtr;
        CoreEvents *coreEvents;
    };
    
}

#endif /* CoreEngine_hpp */
