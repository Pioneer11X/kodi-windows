//
//  KE_SDL.cpp
//  Kodi
//
//  Created by Sravan Karuturi on 28-03-18.
//  Copyright © 2018 Sravan Karuturi. All rights reserved.
//

#include "WindowSDL.hpp"

namespace kodi {
    
    KE_SDL::KE_SDL(){
        
        
        
    };
    
    void KE_SDL::Init(){
        
        this->isOpen = true;
        
        int windowResizable = 0;
        
        this->coreEvents = CoreEvents::getInstance();
        
        startingTime = 0;
        
        
        
        SDL_Init( SDL_INIT_EVERYTHING );
        
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
        SDL_GL_SetAttribute( SDL_GL_STENCIL_SIZE, 8 );
        SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 24 );
        
        this->window = SDL_CreateWindow( this->windowSettings.windowTitle.c_str(), 0, 0, this->windowSettings.windowWidth, this->windowSettings.windowHeight, SDL_WINDOW_OPENGL );
        
        this->context = SDL_GL_CreateContext( window );
        
    }
    
    bool KE_SDL::PollEvents(){
        
        if ( coreEvents->IsExplicitlySettingTime( ) )
        {
            startingTime = coreEvents->GetExplicitTime( );
            coreEvents->StopSettingTime( );
        }
        else
        {
            coreEvents->SetCumulativeTime( SDL_GetTicks( ) );
            coreEvents->SetTime( SDL_GetTicks( ) - startingTime );
        }
        
        if ( SDL_PollEvent( &this->windowEvent ) )
        {
            int x = 0, y = 0;
            
            switch( windowEvent.type )
            {
                    /* Keyboard event */
                    /* Pass the event data onto PrintKeyInfo() */
                case SDL_KEYDOWN:
                    this->coreEvents->SetKeyboardStatus( KEYSTATUS::KB_PRESSED );
                    this->coreEvents->SetKeyStatus( SDL_GetKeyFromScancode( windowEvent.key.keysym.scancode ), KEYSTATUS::KB_PRESSED );
                    
                    break;
                    
                case SDL_KEYUP:
                    this->coreEvents->SetKeyboardStatus( KEYSTATUS::KB_PRESSED );
                    this->coreEvents->SetKeyStatus( SDL_GetKeyFromScancode( windowEvent.key.keysym.scancode ), KEYSTATUS::KB_PRESSED );
                    
                    break;
                    
                case SDL_MOUSEBUTTONDOWN:
                    SDL_GetMouseState( &x, &y );
                    this->coreEvents->SetMousePosition( x, y );
                    this->coreEvents->SetMouseButtonStatus( windowEvent.button.button, MOUSE_BUTTON_STATUS::MOUSEKEY_PRESSED );
                    
                    break;
                    
                case SDL_MOUSEBUTTONUP:
                    SDL_GetMouseState( &x, &y );
                    this->coreEvents->SetMousePosition( x, y );
                    this->coreEvents->SetMouseButtonStatus( windowEvent.button.button, MOUSE_BUTTON_STATUS::MOUSEKEY_RELEASED );
                    
                    break;
                    
                case SDL_MOUSEWHEEL:
                    SDL_GetMouseState( &x, &y );
                    this->coreEvents->SetMousePosition( x, y );
                    this->coreEvents->SetScrollOffset( windowEvent.wheel.x, windowEvent.wheel.y );
                    
                    break;
                    
                case SDL_MOUSEMOTION:
                    SDL_GetMouseState( &x, &y );
                    this->coreEvents->SetMousePosition( x, y );
                    
                    break;
                    
                case SDL_WINDOWEVENT:
                    switch ( windowEvent.window.event )
                {
                    case SDL_WINDOWEVENT_ENTER:
                        this->coreEvents->SetMouseCursorInWindow( true );
                        
                        break;
                        
                    case SDL_WINDOWEVENT_LEAVE:
                        this->coreEvents->SetMouseCursorInWindow( false );
                        
                        break;
                }
                    
                    break;
                    
                    /* SDL_QUIT event (window close) */
                case SDL_QUIT:
                    this->isOpen = false;
                    
                    break;
                    
                default:
                    break;
            }
        }
        
        return false;
    };
    
    void KE_SDL::SwapBuffers(){
        SDL_GL_SwapWindow( this->window );
    };
    
    void KE_SDL::CleanUp(){
        
        SDL_GL_DeleteContext( this->context );
        SDL_DestroyWindow( this->window );
        SDL_Quit( );
        
    };
    
    bool KE_SDL::IsWindowOpen() const{
        return this->isOpen;
    }
    
}
