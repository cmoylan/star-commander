#define GLEW_STATIC
#include <GL/glew.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>


//void runMainLoop(int val);

int
main(int argc, char *args[])
{
  // setup
  SDL_Init(SDL_INIT_VIDEO);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

  SDL_Window *window = SDL_CreateWindow("DO IT OpenGL", 100, 100, 800, 600, SDL_WINDOW_OPENGL);

  SDL_GLContext context = SDL_GL_CreateContext(window);

  glewExperimental = GL_TRUE;
  glewInit();

  GLuint vertexBuffer;
  glGenBuffers(1, &vertexBuffer);
  printf("%u\n", vertexBuffer);

  // main loop
  SDL_Event windowEvent;
  while(true) {
    if (SDL_PollEvent(&windowEvent)) {
      if (windowEvent.type == SDL_QUIT) break;

      if (windowEvent.type = SDL_KEYUP &&
	  windowEvent.key.keysym.sym == SDLK_ESCAPE) break;
    }

    SDL_GL_SwapWindow(window);
  }

  // teardown
  SDL_GL_DeleteContext(context);
  SDL_Quit();

  return 0;

  // --------------------------------------------------------------
  // intialize FreeGLUT
  //glutInit(&argc, args);
  //
  //// create OpenGL 2.1 context
  //glutInitContextVersion(2, 1);
  //
  //// create double-buffered window
  //glutInitDisplayMode(GLUT_DOUBLE);
  //glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
  //glutCreateWindow("OpenGL");
  //
  //// do post window/context creation initialization
  //if (!initGL()) {
  //  // TODO: better debugging
  //  printf("Unable to initialize graphics library!\n");
  //  return 1;
  //}
  //
  //// set keyboard handler
  //glutKeyboardFunc(handleKeys);
  //
  //// set rendering function
  //glutDisplayFunc(render);
  //
  //// set main loop
  //glutTimerFunc(1000 / SCREEN_FPS, runMainLoop, 0);
  //
  //// start main loop
  //glutMainLoop();
  //
  //return 0;
}
