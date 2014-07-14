#ifndef UTIL_H
#define UTIL_H

#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>

#include "OpenGL.h"

GLuint createProgram(const std::vector<GLuint> &shaderList);

GLuint createShader(GLenum shaderType, const std::string& strShaderFile);

std::string loadStringFromFile(const std::string& filename);

#endif
