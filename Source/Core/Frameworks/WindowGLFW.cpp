//
//  KE_GLFW.cpp
//  Kodi
//
//  Created by Sravan Karuturi on 28-03-18.
//  Copyright © 2018 Sravan Karuturi. All rights reserved.
//

#include "WindowGLFW.hpp"
#include <iostream>

namespace kodi {
    
    KE_GLFW::KE_GLFW(){
        
        
        
    };
    
    void KE_GLFW::Init(){
        
        // Init GLFW
        glfwInit( );
        
        // Set all the required options for GLFW
        glfwWindowHint(GLFW_DEPTH_BITS, 24);
        glfwWindowHint(GLFW_STENCIL_BITS, 8);
        glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
        glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
        glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
        glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
        
        glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );
        
        // Create a GLFWwindow object that we can use for GLFW's functions
        window = glfwCreateWindow( this->windowSettings.windowWidth, this->windowSettings.windowHeight, (this->windowSettings.windowTitle.c_str()), nullptr, nullptr );
        
        glfwGetFramebufferSize( window, &this->screenWidth, &this->screenHeight );
        
        if ( nullptr == window )
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate( );
            
            return;
        }
        
        glfwSetKeyCallback( window, KeyCallback );
        glfwSetMouseButtonCallback( window, MouseButtonCallback );
        glfwSetScrollCallback( window, MouseScrollCallback );
        glfwSetCursorPosCallback( window, CursorCallback );
        glfwSetCursorEnterCallback( window, CursorEnterWindowCallback );
        
        glfwSetInputMode( window, GLFW_STICKY_MOUSE_BUTTONS, 1 );
        
        glfwMakeContextCurrent( window );
        
        coreEvents = CoreEvents::getInstance();
        
    }
    
    // Returns True When Closed.
    bool KE_GLFW::PollEvents(){
        
        if ( coreEvents->IsSettingTime( ) )
        {
            glfwSetTime( coreEvents->GetTime( ) );
            coreEvents->StopSettingTime( );
        }
        else
        {
            coreEvents->SetTime( glfwGetTime( ) );
        }
        
        glfwPollEvents( );
        
//        if (glfwWindowShouldClose(this->window)) {
//            return true;
//        }
//
//        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
//        glfwPollEvents( );
        return false;
    };
    
    void KE_GLFW::SwapBuffers(){
        // Swap the screen buffers
        glfwSwapBuffers( window );
    };
    
    void KE_GLFW::CleanUp(){
        
        // Terminate GLFW, clearing any resources allocated by GLFW.
        glfwTerminate( );
        
    };
    
    bool KE_GLFW::IsWindowOpen() const{
        return !glfwWindowShouldClose(this->window);
    }
    
    void KE_GLFW::KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mods )
    {
        CoreEvents *tempEventsObject = CoreEvents::getInstance( );
        
        if ( GLFW_PRESS == action )
        {
            tempEventsObject->SetKeyboardStatus( KEYSTATUS::KB_PRESSED );
            tempEventsObject->SetKeyStatus( key, KEYSTATUS::KB_PRESSED );
        }
        else if ( GLFW_RELEASE == action )
        {
            tempEventsObject->SetKeyboardStatus( KEYSTATUS::KB_RELEASED );
            tempEventsObject->SetKeyStatus( key, KEYSTATUS::KB_RELEASED );
        }
    }
    
    void KE_GLFW::MouseButtonCallback( GLFWwindow *window, int button, int action, int mods )
    {
        CoreEvents *tempEventsObject = CoreEvents::getInstance( );
        
        if ( GLFW_PRESS == action )
        {
            tempEventsObject->SetMouseButtonStatus( button, MOUSE_BUTTON_STATUS::MOUSEKEY_PRESSED );
        }
        else if ( GLFW_REPEAT == action )
        {
            tempEventsObject->SetMouseButtonStatus( button, MOUSE_BUTTON_STATUS::MOUSEKEY_RELEASED );
        }
        
        double xPos, yPos;
        glfwGetCursorPos( window, &xPos, &yPos );
        
        tempEventsObject->SetMousePosition( xPos, yPos );
    }
    
    void KE_GLFW::MouseScrollCallback( GLFWwindow *window, double xoffset, double yoffset )
    {
        CoreEvents *tempEventsObject = CoreEvents::getInstance( );
        
        tempEventsObject->SetScrollOffset( xoffset, yoffset );
        
        double xPos, yPos;
        glfwGetCursorPos( window, &xPos, &yPos );
        
        tempEventsObject->SetMousePosition( xPos, yPos );
    }
    
    void KE_GLFW::CursorCallback( GLFWwindow *window, double xpos, double ypos )
    {
        CoreEvents *tempEventsObject = CoreEvents::getInstance( );
        
        tempEventsObject->SetMousePosition( xpos, ypos );
    }
    
    void KE_GLFW::CursorEnterWindowCallback( GLFWwindow *window, int entered )
    {
        CoreEvents *tempEventsObject = CoreEvents::getInstance( );
        
        if ( entered )
        {
            tempEventsObject->SetMouseCursorInWindow( true );
        }
        else
        {
            tempEventsObject->SetMouseCursorInWindow( false );
        }
    }
    
}
