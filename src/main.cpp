#include "Util.h"

void runMainLoop(int val);

int
main(int argc, char *args[])
{
  // intialize FreeGLUT
  glutInit(&argc, args);

  // create OpenGL 2.1 context
  glutInitContextVersion(2, 1);

  // create double-buffered window
  glutInitDisplayMode(GLUT_DOUBLE);
  glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
  glutCreateWindow("OpenGL");

  // do post window/context creation initialization
  if (!initGL()) {
    // TODO: better debugging
    printf("Unable to initialize graphics library!\n");
    return 1;
  }

  // set keyboard handler
  glutKeyboardFunc(handleKeys);

  // set rendering function
  glutDisplayFunc(render);

  // set main loop
  glutTimerFunc(1000 / SCREEN_FPS, runMainLoop, 0);

  // start main loop
  glutMainLoop();

  return 0;
}
