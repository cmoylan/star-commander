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


void
update()
{
  // no real logic to update
}


void
render()
{
  // clear color buffer
  glClear(GL_COLOR_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  level->render();
  //glTranslatef(gCameraX, gCameraY, 0.f);
  character->render();

  // update screen
  glutSwapBuffers();
}


void
runMainLoop(int val)
{
  // frame logic
  update();
  render();

  // run frame one more time
  glutTimerFunc(1000 / SCREEN_FPS, runMainLoop, val);
}


void
handleKeys(unsigned char key, int x, int y)
{
  // if the user pressed w/a/s/d, move the character
  // a/s/d/f will be translated to /l/d/r/u (left/right/down/up).
  // this is done so that the keys are not hardwired and can be changed.

  // move up
  if (key == 'w') {
    character->move('u');
  }
  // move left
  else if (key == 'a') {
    character->move('l');
  }
  // move down
  else if (key == 's') {
    character->move('d');
  }
  // move right
  else if (key == 'd') {
    character->move('r');
  }

  // TODO: other things
}
