#include "Util.h"
#include "Level.h"
#include "Character.h"


// level
Level *level;

// main character
Character *character;


bool
initGL()
{
  //  printf("character x,y is: %f, %f", character.x, character.y);

  // set the viewport
  glViewport(0.f, 0.f, SCREEN_WIDTH, SCREEN_HEIGHT);

  // initialize projection matrix
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, 1.0, -1.0);

  // initialize modelview matrix
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // initialize clear color
  glClearColor(0.f, 0.f, 0.f, 1.f);

  // enable texturing
  //glEnable(GL_TEXTURE_2D);

  // check for error
  GLenum error = glGetError();
  if (error != GL_NO_ERROR) {
    // TODO: use propper debug macro
    printf("Error initializing OpenGL %s\n", gluErrorString(error));
    return false;
  }

  // this will do a lot more when we have dynamic levels
  level = new Level();
  // TODO: constantize
  level->loadFromFile("level1.bmp");
  //level->print();

  character = new Character(level);

  return true;
}




