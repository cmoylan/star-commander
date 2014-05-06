#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>
#include <stdio.h>
#include "CImg.h"

#include "OpenGL.h"
#include "Constants.h"


class Level {

  // Representation of the level:
  // - will probably consist of a matrix of pointers
  // - each pointer will reference an instance of the type of surface
  // - will have multiple surface classes that share the same interface
  // - then in render, we'll just call #render for each surface instance
  // - alike or identical surfaces will point to the same instance,
  std::vector< std::vector<int> > levelMatrix;

  // current position of the camera in the level
  int cameraX;
  int cameraY;

  static GLuint texid;

  // whether or not there is gravity
  bool gravity;

public:
  // constructor
  Level();

  // destructor
  ~Level();

  void centerOn(int x, int y);

  void centerOnX(int x);

  void centerOnY(int y);

  int height();

  bool isCentered(int x, int y);

  bool isCenteredX(int x);

  bool isCenteredY(int y);

  bool isClear(int x, int y);

  bool loadFromFile(std::string path);

  void print();

  void render();

  int width();

  void initTexture();
};

#endif
