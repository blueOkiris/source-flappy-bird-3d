#pragma once

/*
 * This is to wrap all the OpenGL stuff away
 * so code can be cleaner
 */

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <exception>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace flappybird {
    namespace gl {
        struct InvalidShaderPathException : public std::exception {
            private:
                const std::string _msg;
                
            public:
                InvalidShaderPathException(const std::string &fileName) :
                        _msg("Couldn't find shader file '" + fileName + "'") {
                }
                
                const char *what() const throw() {
                    return _msg.c_str();
                }
        };
        
        inline uint loadShaders(
                const std::string &vertexFileName,
                const std::string &fragmentFileName) {
            // Create temporary shader storages
            const auto vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
            const auto fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
            
            // Read the vertex shader from the file
            std::ifstream vertexShaderFile(vertexFileName);
            if(!vertexShaderFile.is_open()) {
                throw InvalidShaderPathException(vertexFileName);
            }
            std::stringstream vertexShaderData;
            vertexShaderData << vertexShaderFile.rdbuf();
            const auto vertexShaderCode = vertexShaderData.str();
            vertexShaderFile.close();
            
            // Read the frag shader from file
            std::ifstream fragmentShaderFile(fragmentFileName);
            if(!fragmentShaderFile.is_open()) {
                throw InvalidShaderPathException(fragmentFileName);
            }
            std::stringstream fragmentShaderData;
            fragmentShaderData << fragmentShaderFile.rdbuf();
            const auto fragmentShaderCode = fragmentShaderData.str();
            fragmentShaderFile.close();
            
            int result = 0;
            int infoLogLen;
            
            // Compile vertex shader
            const auto vertexSourcePtr = vertexShaderCode.c_str();
            glShaderSource(vertexShaderId, 1, &vertexSourcePtr, nullptr);
            glCompileShader(vertexShaderId);
            
            // Check vertex shader
            glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &result);
            glGetShaderiv(vertexShaderId, GL_INFO_LOG_LENGTH, &infoLogLen);
            if(infoLogLen > 0) {
                std::vector<char> vertexShaderErrorMessage(infoLogLen + 1);
                glGetShaderInfoLog(
                    vertexShaderId, infoLogLen, nullptr,
                    &vertexShaderErrorMessage[0]
                );
                std::cerr
                    << "There was an error compiling vertex shader '"
                    << vertexFileName << "':" << std::endl
                    << &vertexShaderErrorMessage[0] << std::endl;
            }
            
            // Compile fragment shader
            const auto fragmentSourcePtr = fragmentShaderCode.c_str();
            glShaderSource(fragmentShaderId, 1, &fragmentSourcePtr, nullptr);
            glCompileShader(fragmentShaderId);
            
            // Check fragment shader
            glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &result);
            glGetShaderiv(fragmentShaderId, GL_INFO_LOG_LENGTH, &infoLogLen);
            if(infoLogLen > 0) {
                std::vector<char> fragmentShaderErrorMessage(infoLogLen + 1);
                glGetShaderInfoLog(
                    fragmentShaderId, infoLogLen, nullptr,
                    &fragmentShaderErrorMessage[0]
                );
                std::cerr
                    << "There was an error compiling fragment shader '"
                    << fragmentFileName << "':" << std::endl
                    << &fragmentShaderErrorMessage[0] << std::endl;
            }
            
            // Link the program
            const auto progId = glCreateProgram();
            glAttachShader(progId, vertexShaderId);
            glAttachShader(progId, fragmentShaderId);
            glLinkProgram(progId);
            
            // Check the program
            glGetProgramiv(progId, GL_LINK_STATUS, &result);
            glGetProgramiv(progId, GL_INFO_LOG_LENGTH, &infoLogLen);
            if(infoLogLen > 0) {
                std::vector<char> programErrorMessage(infoLogLen + 1);
                glGetProgramInfoLog(
                    progId, infoLogLen, nullptr, &programErrorMessage[0]
                );
                std::cerr
                    << "There was an error linking shader program with "
                    << "vertex shader '" << vertexFileName << "' and "
                    << "fragment shader '" << fragmentFileName << "'"
                    << std::endl
                    << &programErrorMessage[0] << std::endl;
            }
            
            // Clean up
            glDetachShader(progId, vertexShaderId);
            glDetachShader(progId, fragmentShaderId);
            
            glDeleteShader(vertexShaderId);
            glDeleteShader(fragmentShaderId);
            
            return progId;
        }
    }
}
