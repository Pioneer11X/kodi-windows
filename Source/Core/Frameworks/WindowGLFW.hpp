//
//  KE_GLFW.hpp
//  Kodi
//
//  Created by Sravan Karuturi on 28-03-18.
//  Copyright © 2018 Sravan Karuturi. All rights reserved.
//

#pragma once
#include "WindowInterface.h"

#include <GLFW/glfw3.h>

namespace kodi {
    
    class KE_GLFW : public FrameworkInterface {
        
    public:
        
        KE_GLFW();
        
    protected:
        
        void Init();
        bool PollEvents();
        void SwapBuffers();
        void CleanUp();
        bool IsWindowOpen() const;
		void WindowShouldClose();
        
        static void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mods );
        static void MouseButtonCallback( GLFWwindow *window, int button, int action, int mods );
        static void MouseScrollCallback( GLFWwindow *window, double xoffset, double yoffset );
        static void CursorCallback( GLFWwindow *window, double xpos, double ypos );
        static void CursorEnterWindowCallback( GLFWwindow *window, int entered );
        
    private:
        GLFWwindow * window;
        
    };
    
}


