#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "OpenGL.h"
#include "Util.h"
#include "Constants.h"
#include "BulletRegistry.h"


class Character {

  // opengl stuff
  // TODO: rename most of these, they are awful
  GLuint vao, vbo, ebo, tex, uniTrans;
  GLuint shaderProgram;

public:
  // the location of the character on the screen
  coordinate_t screenPos;

  // size of the actual character
  int width;
  int height;


  // constructor
  Character(std::string texture, coordinate_t startingPos);

  // destructor
  ~Character();

  void fire();

  void move(unsigned char direction);

  void render();

};

#endif
