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

  void initGL();

public:

  // allow direct access to these...why not
  Vector2D origin;
  Vector2D size;

  // constructor
  Enemy(Coordinate position);

  // destructor
  ~Enemy();

  int edgeBottom();
  int edgeLeft();
  int edgeRight();
  int edgeTop();

  void fire();

  void move(int x, int y);

  void render();

};

#endif
