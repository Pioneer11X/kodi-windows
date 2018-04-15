//
//  MouseDefinitions.h
//  Kodi
//
//  Created by Sravan Karuturi on 11-04-18.
//  Copyright © 2018 Sravan Karuturi. All rights reserved.
//

#pragma once

enum MOUSE_STATUS
{
    MOUSE_NOTHING = 1113,
    MOUSE_MOVING = 1114,
    MOUSE_RELEASED = 1115,
    MOUSE_MOUSE_ENTERED = 1116,
    MOUSE_MOUSE_LEFT = 1117,
};

enum MOUSE_BUTTON_STATUS
{
    MOUSEKEY_NOT_PRESSED = 1221,
    MOUSEKEY_PRESSED = 1222,
    MOUSEKEY_RELEASED = 1223
};

enum MOUSE_BUTTONS
{
    MOUSEKEY_ANY = -1,
    MOUSEKEY_LEFT = 0,
    MOUSEKEY_RIGHT = 1,
    MOUSEKEY_MIDDLE = 2
};
