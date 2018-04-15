//
//  main.cpp
//  Kodi
//
//  Created by Sravan Karuturi on 27-03-18.
//  Copyright © 2018 Sravan Karuturi. All rights reserved.
//

/* Code taken from https://raw.githubusercontent.com/SonarSystems/Modern-OpenGL-Tutorials/master/%5BGETTING%20STARTED%5D/%5B1%5D%20Triangle/main.cpp to test GLFW */

/* Code taken from https://raw.githubusercontent.com/SonarSystems/Modern-OpenGL-Tutorials/master/%5BSETUP%5D/SFML/Mac/SFMLOpenGL/main.cpp to test SFML initially. */

/* Code taken from https://raw.githubusercontent.com/SonarSystems/Modern-OpenGL-Tutorials/master/%5BSETUP%5D/SDL/Mac/SDLOpenGL/main.cpp  to test SDL */

#include "windows.h"
#include <iostream>
#include "Core\CoreEngine.hpp"
#include "KodiConfig.h"

using namespace kodi;

int WINAPI WinMain(HINSTANCE hinstance,
	HINSTANCE hprevinstance,
	LPSTR lpcmdline,
	int ncmdshow)
// int main()
{

	// 1 --> SDL
	// 2 --> SFML
	// 3 --> GLFW.
	// Defaults to GLFW
	CoreEngine ce(0);

	int currentTimeInSeconds = 0;

	ce.Init();

	std::cout << "Here" << std::endl;

	while (ce.WindowIsOpen()) {

		if (ce.getEvents()->CheckKeyStatus(KEYSTATUS::KB_PRESSED, KEYS::Escape)) {
			break;
		}

		if (ce.getEvents()->CheckKeyboardStatus(KEYSTATUS::KB_PRESSED))
		{
			if (ce.getEvents()->CheckKeyStatus(KEYSTATUS::KB_PRESSED, KEYS::A))
			{
				std::cout << "A pressed" << std::endl;

			}
		}
		else if (ce.getEvents()->CheckKeyboardStatus(KEYSTATUS::KB_RELEASED))
		{
			std::cout << "Release" << std::endl;

		}

		if (ce.getEvents()->CheckMouseButtonStatus(MOUSE_BUTTONS::MOUSEKEY_ANY, MOUSE_BUTTON_STATUS::MOUSEKEY_PRESSED))
		{
			ce.getEvents()->ResetTime();
		}

		ce.GameLoop();

	}

	ce.Cleanup();

	return EXIT_SUCCESS;

}
