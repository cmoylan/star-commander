#ifndef ENEMY_H
#define ENEMY_H

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "OpenGL.h"
#include "Util.h"
#include "Constants.h"
#include "Entity.h"
#include "BulletRegistry.h"
#include "Game.h"


class Enemy : public Entity {

  // buffer objects
  GLuint vao, vbo, ebo;
  // uniforms
  GLuint uniTrans, uniColor;
  // compiled gl program
  GLuint shaderProgram;

  void initGL();

public:

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

  virtual void hit();
};

#endif
