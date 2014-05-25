#ifndef CHARACTER_H
#define CHARACTER_H

#include "OpenGL.h"
#include "Constants.h"


//const GLchar* characterVertexSrc =
//  "#version 150 core"
//  "in vec2 position;"
//  "void main() {"
//  "  gl_Position = vec4(position.x, position.y, 0.0, 1.0);"
//  "}";
//
//const GLchar* characterFragmentSrc =
//  "#version 150 core"
//  "out vec4 outColor;"
//  "void main() {"
//  "  outColor = vec4(1.0, 1.0, 1.0, 1.0);"
//  "}";


class Character {

  // opengl stuff
  GLuint vao, vbo;
  GLuint shaderProgram;

public:
  // the location of the character on the screen
  coordinate_t screenPos;

  // size of the actual character
  int width;
  int height;


  // constructor
  Character();

  // destructor
  ~Character();

  void move(unsigned char direction);

  void render();

};

#endif
