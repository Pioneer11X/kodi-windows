//
//  CoreEngine.cpp
//  Kodi
//
//  Created by Sravan Karuturi on 28-03-18.
//  Copyright © 2018 Sravan Karuturi. All rights reserved.
//

#include "CoreEngine.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/regex.hpp>
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const GLint WIDTH = 600, HEIGHT = 600;

namespace kodi {
    
    CoreEngine::CoreEngine(int framework){
        
        // The events need to be initialised before Framework, since the frameworks make use o fthe files.
        coreEvents = CoreEvents::getInstance();
        
        switch (framework) {
            case KE__SDL:
                frameworkPtr = new kodi::KE_SDL();
                break;
            case KE__SFML:
                frameworkPtr = new kodi::KE_SFML();
                break;
            case KE__GLFW:
                frameworkPtr = new kodi::KE_GLFW();
                break;
            default:
                // We shall use GLFW as the default case.
                frameworkPtr = new kodi::KE_GLFW();
                break;
        }
        
        coreEvents->Init(framework);
        
    };
    
    bool CoreEngine::Init(){
        
        namespace fs = boost::filesystem;
        
        this->frameworkPtr->SetWindowParameters(800, 600, "Kodi Engine v0.0.1");
        
        this->frameworkPtr->Init();
        
        // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
        glewExperimental = GL_TRUE;
        // Initialize GLEW to setup the OpenGL Function pointers
        if ( GLEW_OK != glewInit( ) )
        {
            std::cout << "Failed to initialize GLEW" << std::endl;
            return EXIT_FAILURE;
        }

		/***************************************************************
		3D ఐతే Depth Buffer Enable చెయ్యాలి
		****************************************************************/
		glEnable(GL_DEPTH_TEST);
        
        // Define the viewport dimensions
        glViewport( 0, 0, this->frameworkPtr->screenWidth, this->frameworkPtr->screenHeight );
        
        /******************************************************************************
         Boost ఫైలుసిస్టము వాడి షేడరు ఫోల్డరులో వున్నవన్నీ ఇక్కడే లోడ్చేసెయ్యి
         *******************************************************************************/
        /* Boost Filusystam ikkada nundi vaaduthunnaamu */
        
        std::string dirPath( SHADER_FOLDER_PATH );
        
        boost::filesystem::path directory(dirPath);
        
        try {
            if (boost::filesystem::exists(directory) || boost::filesystem::is_directory(directory)) {
                for (fs::directory_entry& x : fs::directory_iterator(directory)) {
                    fs::path filePath = x.path();
                    std::string filePathAndName = filePath.generic_string();
                    std::vector<std::string> stringsBrokenDown;
                    
                    boost::algorithm::split_regex(stringsBrokenDown, filePathAndName, boost::regex("(\/Shaders\/)"));
                    // std::string fileName = stringsBrokenDown[stringsBrokenDown.size()];
                    std::string fileName = stringsBrokenDown[1];
                    
                    // Now split for file Extensions.
                    // boost::algorithm::split_regex(stringsBrokenDown, fileName, boost::regex("[.]"));
                    
                    // Switch on Char should be faster than breaking it up for extensions.
                    switch (fileName.back()) {
                        case 'g':
                            // ఇది Fragment Shader. దీన్ని దాన్సో పెట్టు
                            // మనం ఒక ఐదు అక్షరాలతో మాత్రమే ఫైలుపేరుపెడతాం
                            boost::algorithm::split_regex(stringsBrokenDown, fileName, boost::regex("(.frag)"));
                            fragmentShaderFiles[stringsBrokenDown[0]] = filePathAndName;
                            break;
                            
                        case 's':
                            // ఇది Vertex Shader. దీన్ని కూడాదాన్సోపెట్టు
                            boost::algorithm::split_regex(stringsBrokenDown, fileName, boost::regex("(.vs)"));
                            vertexShaderFiles[stringsBrokenDown[0]] = filePathAndName;
                            break;
                            
                        default:
                            std::cout << "The files in the Shader directory has an unsupported extension. " << std::endl;
                            std::cout << "షేడర్ల ఫాల్డర్లో మనం వాడని Extension వున్నాయి. అవి,  " << fileName << std::endl;
                            break;
                    }
                }
            }
        }
        catch (const fs::filesystem_error& ex) {
            std::cout << ex.what() << std::endl;
        }
        
        /* Boost FiluSystam ikkada varaku vaadaamu */
                
        // Ippudu anni fileski shaderlu thayaaruchesukoni pettuko.
        for ( auto const &fileName: fragmentShaderFiles){
            ShaderDictionary[fileName.first] = new Shader(vertexShaderFiles[fileName.first].c_str(), fragmentShaderFiles[fileName.first].c_str());
            // TODO: Moththam ayyipoyina tharuvaatha veetini vidudhala cheseyyi.
        }

		/***************************************************************
			మళ్ళీ boost వాడి మెత్తం వున్న Texture లు అన్నీ ఒకేసారి load చేసెయ్యి
		***************************************************************/

		dirPath = std::string(TEXTURE_FOLDER_PATH);

		directory = boost::filesystem::path(dirPath);

		try {
			if (boost::filesystem::exists(directory) || boost::filesystem::is_directory(directory)) {
				for (fs::directory_entry& x : fs::directory_iterator(directory)) {
					fs::path filePath = x.path();
					std::string filePathAndName = filePath.generic_string();
					std::vector<std::string> stringsBrokenDown;

					// boost::cmatch regex_result;
					boost::algorithm::split_regex(stringsBrokenDown, filePathAndName, boost::regex("(\/Textures\/)"));
					// boost::regex_match(filePathAndName.c_str(), regex_result, boost::regex("(\/Textures\/(.*)[\.])"));
					// std::string fileName = stringsBrokenDown[stringsBrokenDown.size()];
					std::string fileName = stringsBrokenDown[1];

					// TODO: Find a better way, but for now, we split it again.
					boost::algorithm::split_regex(stringsBrokenDown, fileName, boost::regex("([\.])"));

					fileName = stringsBrokenDown[0];
					// ఇప్పుడు అన్ని Texture files నీ load చెయ్యి
					TextureDictionary[fileName] = new Texture(filePathAndName.c_str());

				}
			}
		}
		catch (const fs::filesystem_error& ex) {
			std::cout << ex.what() << std::endl;
		}

		/***************************************************************
			Boost ఇక్కడితో అయిపోయింది
		****************************************************************/


		float cubeVertices[] = {
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
			0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
			0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
		};

		unsigned int indices[] = {  // note that we start from 0!
			0, 2, 3,  // first Triangle
			0, 1, 2  // second Triangle
		};

		std::string test(TEXTURE_FOLDER_PATH);
		test += "\\container.jpg";

		// texture = new Texture(test.c_str());
        
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
		// glGenBuffers(1, &EBO);

        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(VAO);
        
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
        
        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);					

		// Texture Attribute.							
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
        
		ShaderDictionary["first"]->use();
		ShaderDictionary["first"]->setInt("ourTexture", 0);
		ShaderDictionary["first"]->setInt("ourSecondTexture", 1);

        // Ideally return true.
        return true;
        
    };
    
    // Return true if we want to quit.
    bool CoreEngine::GameLoop(){
        
        bool returnValue = this->frameworkPtr->PollEvents();
        
        // Clear the colorbuffer
        glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        {
            
            // Actual Logic for the Game Loop.
            ShaderDictionary["first"]->use();

			// Bind and Activate Textures.
			glActiveTexture(GL_TEXTURE0);
			TextureDictionary["container"]->Use();
			glActiveTexture(GL_TEXTURE1);
			TextureDictionary["awesomeface"]->Use();
			glBindVertexArray(VAO);

			// create transformations
			glm::mat4 model;
			glm::mat4 view;
			glm::mat4 projection;
			model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
			view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
			projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
			// retrieve the matrix uniform locations
			ShaderDictionary["first"]->setMat4("model", model);
			ShaderDictionary["first"]->setMat4("view", view);
			ShaderDictionary["first"]->setMat4("projection", projection);
			
			// render box
			glDrawArrays(GL_TRIANGLES, 0, 36);
            
        }
        
        // draw OpenGL
        this->frameworkPtr->SwapBuffers();
        
        return returnValue;
        
    }
    
    // Cleanup
    void CoreEngine::Cleanup(){
        
        glDeleteVertexArrays(1, &VAO);
        
        this->frameworkPtr->CleanUp();
        
    }

	void CoreEngine::HandleInputs()
	{
		if (this->getEvents()->CheckKeyStatus(KEYSTATUS::KB_PRESSED, KEYS::Escape)) {
			this->frameworkPtr->WindowShouldClose();
		}

		if (this->getEvents()->CheckKeyboardStatus(KEYSTATUS::KB_PRESSED))
		{
			if (this->getEvents()->CheckKeyStatus(KEYSTATUS::KB_PRESSED, KEYS::A))
			{
				std::cout << "A pressed" << std::endl;

			}
		}
		else if (this->getEvents()->CheckKeyboardStatus(KEYSTATUS::KB_RELEASED))
		{
			std::cout << "Release" << std::endl;

		}

		if (this->getEvents()->CheckMouseButtonStatus(MOUSE_BUTTONS::MOUSEKEY_ANY, MOUSE_BUTTON_STATUS::MOUSEKEY_PRESSED))
		{
			this->getEvents()->ResetTime();
		}
	}
    
    bool CoreEngine::WindowIsOpen( ) const
    {
        // return coreFramework.WindowIsOpen( );
        return this->frameworkPtr->IsWindowOpen();
    }
    
}
