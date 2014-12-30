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
  GLuint uniColor; // temp
  GLuint shaderProgram;

  void initGL(std::string texture);

public:

  Vector2D origin;
  Vector2D size;

  // constructor
  Character(std::string texture, Coordinate potision);

  // destructor
  ~Character();

  void center();

  void fire();

  // TODO: probably should take a heading or something...
  void move(unsigned char direction);

  void render();

};

#endif
