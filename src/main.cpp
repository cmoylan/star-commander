#include "OpenGL.h"
#include "Character.h"


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

  // Initialize GLEW
  glewExperimental = GL_TRUE;
  glewInit();

  Character *character = new Character();

  // main loop
  SDL_Event windowEvent;

  // TODO: how to change the framerate?
  while (true) {
    // TODO: move to key handler function
    if (SDL_PollEvent(&windowEvent)) {
      if (windowEvent.type == SDL_QUIT) {
        break;
      }

      if (windowEvent.type == SDL_KEYUP &&
          windowEvent.key.keysym.sym == SDLK_ESCAPE) {
        break;
      }
    }

    // TODO: move to render function
    // Clear the screen to black
    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Render each component on the screen
    character->render();

    SDL_GL_SwapWindow(window);
  }

  // teardown
//  glDeleteProgram(shaderProgram);
//  glDeleteShader(fragmentShader);
//  glDeleteShader(vertexShader);
//
//  glDeleteBuffers(1, &vbo);
//
//  glDeleteVertexArrays(1, &vao);

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
