//
//  CoreEvents.hpp
//  Kodi
//
//  Created by Sravan Karuturi on 11-04-18.
//  Copyright © 2018 Sravan Karuturi. All rights reserved.
//

#pragma once

#include "Events/EventInterface.hpp"
#include "Events/KeyboardDefinitions.h"
#include "Events/MouseDefinitions.h"

#include "../DEFINITIONS.h"

#include "Events/EventSDL.hpp"
#include "Events/EventGLFW.hpp"
#include "Events/EventSFML.hpp"

#include <glm/vec2.hpp>

namespace kodi
{
    class CoreEvents: public EventInterface
    {
    public:
        static CoreEvents *getInstance( )
        {
            if ( !sInstance )
            {
                sInstance = new CoreEvents;
            }
            
            return sInstance;
        }
        
        bool Init(int eventFramework);
        
        bool CheckKeyboardStatus( int keyStatus );
        bool CheckKeyStatus( int keyStatus, int key );
        
        // sets the status of the keyboard
        void SetKeyboardStatus( int keyboardStatus );
        void SetKeyStatus( int key, int keyStatus );
        
        bool CheckMouseButtonStatus( int button, int buttonStatus );
        void SetMouseButtonStatus( int button, int buttonStatus );
        
        const glm::vec2& GetScrollOffset( ) const;
        void SetScrollOffset( float x, float y );
        
        const glm::vec2& GetMousePosition( ) const;
        void SetMousePosition( float x, float y );
        
        bool IsMouseCursorInWindow( );
        void SetMouseCursorInWindow( bool isInWindow );
        
        double GetTime( );
        double GetExplicitTime( );
        double GetCumulativeTime( );
        void SetTime( double time, bool isNormalSet = true );
        void SetCumulativeTime( double time );
        
        bool IsSettingTime( );
        bool IsExplicitlySettingTime( );
        void StopSettingTime( );
        
        void ResetTime( );
        
    private:
        CoreEvents( );
        
        static CoreEvents *sInstance;
        
//#ifdef SGE__SDL
//        EventsSDL eventsObject;
//#elif defined(SGE__SFML)
//        EventsSFML eventsObject;
//#elif defined(SGE__GLFW)
//        EventsGLFW eventsObject;
//#endif
        
        EventInterface * eventObject;
        
        // has a key been pressed or released (reset the value of this key once checked)
        int keyboardStatus;
        int mouseStatus;
        int scrollStatus;
        
        int keysStatus[101];
        int mouseButtonsStatus[3];
        glm::vec2 scrollOffset;
        glm::vec2 mousePosition;
        bool isInWindow;
        
        double time, explicitTime, cumulativeTime;
        bool isSettingTime, isExplicitlySettingTime;
        
        int GetKeyNumber( int key ) override;
        int GetMouseButtonNumber( int button ) override;
    };
}
