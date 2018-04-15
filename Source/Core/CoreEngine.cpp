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

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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
        
        // set up vertex data (and buffer(s)) and configure vertex attributes
        // ------------------------------------------------------------------
        float vertices[] = {
            // positions         // colors			// Tex Coords.
			0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // top right
            0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,	1.0f, 0.0f,// bottom right
            -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,	0.0f, 0.0f, // bottom left
            -0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,	0.0f, 1.0f,  // top left
		};

		unsigned int indices[] = {  // note that we start from 0!
			0, 2, 3,  // first Triangle
			0, 1, 2  // second Triangle
		};

		int width, height, nrChaneels;
		stbi_set_flip_vertically_on_load(true);

		std::string test(TEXTURE_FOLDER_PATH);
		test += "\\container.jpg";

		unsigned char * data = stbi_load( test.c_str(), &width, &height, &nrChaneels, 0);
        
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		glGenTextures(1, &texture);

        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(VAO);
        
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);
        
        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);					
        // color attribute								
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);					
		// Texture Attribute.							
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);
        
        // Ideally return true.
        return true;
        
    };
    
    // Return true if we want to quit.
    bool CoreEngine::GameLoop(){
        
        bool returnValue = this->frameworkPtr->PollEvents();
        
        
        
        // Clear the colorbuffer
        glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT );
        
        {
            
            // Actual Logic for the Game Loop.
            ShaderDictionary["first"]->use();
			glBindTexture(GL_TEXTURE_2D, texture);
            glBindVertexArray(VAO);
            // glDrawArrays(GL_TRIANGLES, 0, 6);
			glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
            
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
    
    bool CoreEngine::WindowIsOpen( ) const
    {
        // return coreFramework.WindowIsOpen( );
        return this->frameworkPtr->IsWindowOpen();
    }
    
}
