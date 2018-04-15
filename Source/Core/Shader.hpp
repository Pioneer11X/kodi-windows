//
//  Shader.hpp
//  Kodi
//
//  Created by Sravan Karuturi on 03-04-18.
//  Copyright © 2018 Sravan Karuturi. All rights reserved.
//

#pragma once

#ifndef GLEW_STATIC
#define GLEW_STATIC
#include <GL/glew.h>
#endif

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace kodi {
    
    class Shader{
      
    public:
        
        unsigned int ID;
        
        // అనసరంలేని వేరియబుల్లు. వాడివదిలించెయ్యి
        // క్రిందవాడే అవసరంలేనివన్నీ ఇక్కడ పెట్టెయ్యి
        
        // కనస్టరక్టరు
        Shader(const char * vertexFilePath, const char * fragmentFilePath);
        
        // activate the shader
        void use();
        
        // utility uniform functions
        inline void setBool(const std::string &name, bool value) const
        {
            glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
        }

        inline void setInt(const std::string &name, int value) const
        {
            glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
        }
        
        inline void setFloat(const std::string &name, float value) const
        {
            glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
        }
        
    private:
        // utility function for checking shader compilation/linking errors.
        void checkCompileErrors(unsigned int shader, std::string type)
        {
            int success;
            char infoLog[1024];
            if (type != "PROGRAM")
            {
                glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
                if (!success)
                {
                    glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                    std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
                }
            }
            else
            {
                glGetProgramiv(shader, GL_LINK_STATUS, &success);
                if (!success)
                {
                    glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                    std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
                }
            }
        }
        
    };
    
}
