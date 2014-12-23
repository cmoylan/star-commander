#ifndef ENEMY_H
#define ENEMY_H

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "OpenGL.h"
#include "Util.h"
#include "Constants.h"
#include "BulletRegistry.h"


class Enemy {

  // buffer objects
  GLuint vao, vbo, ebo;
  // uniforms
  GLuint uniTrans, uniColor;
  // compiled gl program
  GLuint shaderProgram;

public:
  // the location of the character on the screen
  coordinate_t screenPos;

  // size of the actual character
  int width;
  int height;


  // constructor
  Enemy(coordinate_t startingPos);

  // destructor
  ~Enemy();

  void fire();

  void initGL();

  void move(int x, int y);

  void render();

};

#endif
