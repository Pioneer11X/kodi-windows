//
//  FrameworkInterface.h
//  Kodi
//
//  Created by Sravan Karuturi on 28-03-18.
//  Copyright © 2018 Sravan Karuturi. All rights reserved.
//

#pragma once

#include <string>

#define GLEW_STATIC
#include <GL/glew.h>

#include "../CoreEvents.hpp"

namespace kodi {
    
    struct WindowSettings{
        
        GLint windowWidth;
        GLint windowHeight;
        std::string windowTitle;
        
    };
    
    class FrameworkInterface{
        
    protected:
        
        WindowSettings windowSettings;
        
        CoreEvents * coreEvents;
        
    public:
        
        // ఇది రెటీనా డిస్ప్లేలకోసం
        int screenWidth;
        int screenHeight;
        
        virtual void Init() = 0;
        
        // An abstraction for Poll Events.
        virtual bool PollEvents() = 0;
        
        virtual void SwapBuffers() = 0;
        
        virtual void CleanUp() = 0;
        
        virtual bool IsWindowOpen() const = 0;
        
        // A Virtual function to set the Window size when we initialies the window.
        void SetWindowParameters(GLint _width, GLint _height, std::string _title);
        
        // TODO: Implement a getter function for the Parameters.
        inline GLint GetWindowWidth(){
            return this->windowSettings.windowWidth;
        };
        
        inline GLint GetWindowHeight(){
            return this->windowSettings.windowHeight;
        };
        
        inline std::string GetWindowTitle(){
            return this->windowSettings.windowTitle;
        };
        
    };
    
}
