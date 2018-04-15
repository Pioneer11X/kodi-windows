//
//  KE_SFML.cpp
//  Kodi
//
//  Created by Sravan Karuturi on 28-03-18.
//  Copyright © 2018 Sravan Karuturi. All rights reserved.
//

#include "WindowSFML.hpp"

namespace kodi {
    
    KE_SFML::KE_SFML(){
        
        
        
    };
    
    void KE_SFML::Init(){
        
        sf::ContextSettings settings;
        settings.depthBits = 24;
        settings.stencilBits = 8;
        settings.majorVersion = 3;
        settings.minorVersion = 3;
        settings.attributeFlags = sf::ContextSettings::Core;
        
        this->coreEvents = CoreEvents::getInstance();
        
        this->window = new sf::Window( sf::VideoMode( this->windowSettings.windowWidth, this->windowSettings.windowHeight, 32 ), this->windowSettings.windowTitle, sf::Style::Titlebar | sf::Style::Close, settings );
        
    }
    
    // Returns True When Closed.
    bool KE_SFML::PollEvents(){
        sf::Event windowEvent;
        
        if ( coreEvents->IsExplicitlySettingTime( ) )
        {
            startingTime = coreEvents->GetExplicitTime( );
            coreEvents->StopSettingTime( );
        }
        else
        {
            coreEvents->SetCumulativeTime( clock.getElapsedTime( ).asMilliseconds( ) );
            coreEvents->SetTime( clock.getElapsedTime( ).asMilliseconds( ) - startingTime );
        }
        
        while ( this->window->pollEvent( windowEvent ) )
        {
            switch ( windowEvent.type )
            {
                case sf::Event::Closed:
                    this->window->close( );
                    
                    break;
                    
                case sf::Event::KeyPressed:
                    this->coreEvents->SetKeyboardStatus( KEYSTATUS::KB_PRESSED );
                    this->coreEvents->SetKeyStatus( windowEvent.key.code, KEYSTATUS::KB_PRESSED );
                    
                    break;
                    
                case sf::Event::KeyReleased:
                    this->coreEvents->SetKeyboardStatus( KEYSTATUS::KB_RELEASED );
                    this->coreEvents->SetKeyStatus( windowEvent.key.code, KEYSTATUS::KB_RELEASED );
                    
                    break;
                    
                case sf::Event::MouseButtonPressed:
                    this->coreEvents->SetMouseButtonStatus( windowEvent.mouseButton.button, MOUSE_BUTTON_STATUS::MOUSEKEY_PRESSED );
                    
                    break;
                    
                case sf::Event::MouseButtonReleased:
                    this->coreEvents->SetMouseButtonStatus( windowEvent.mouseButton.button, MOUSE_BUTTON_STATUS::MOUSEKEY_RELEASED );
                    
                    break;
                    
                case sf::Event::MouseWheelMoved:
                    this->coreEvents->SetScrollOffset( 0, windowEvent.mouseWheel.delta );
                    
                    break;
                    
                case sf::Event::MouseMoved:
                    this->coreEvents->SetMousePosition( windowEvent.mouseMove.x, windowEvent.mouseMove.y );
                    
                    break;
                    
                case sf::Event::MouseEntered:
                    this->coreEvents->SetMouseCursorInWindow( true );
                    
                    break;
                    
                case sf::Event::MouseLeft:
                    this->coreEvents->SetMouseCursorInWindow( false );
                    
                    break;
            }
        }
        return false;
    };
    
    void KE_SFML::SwapBuffers(){
        this->window->display();
    };
    
    void KE_SFML::CleanUp(){
        
        this->window->close();
        
    };
    
    bool KE_SFML::IsWindowOpen() const{
        return this->window->isOpen();
    };
    
}
