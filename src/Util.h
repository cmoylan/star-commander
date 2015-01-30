#pragma once

#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>

#include <SOIL.h>

#include "OpenGL.h"


namespace Util
{

    void createAndBindContext(GLuint* vao);

    GLuint createProgram(const std::vector<GLuint>& shaderList);

    GLuint createProgramFromShaders(std::string vertexFile,
                                    std::string fragmentFile);

    GLuint createShader(GLenum shaderType, const std::string& strShaderFile);

    std::string loadStringFromFile(const std::string& filename);

    void loadTexture(GLuint buffer, const std::string& filename);

    /**
    * Reset OpenGL state machine
    *
    * Sets texture buffer, vertex array, and shader program to 0.
    */
    void resetGlState();

}