#include "OpenGL.h"
#include "Character.h"
#include "Enemy.h"
#include "BulletRegistry.h"

bool quit = false;

// main character
Character *character;
Enemy *enemy;

void update();

void handleKeys();

void render();


int
main(int argc, char *args[])
{
  Uint32 startTime;
  // TODO: move
  const int FPS = 30;

  // setup
  SDL_Init(SDL_INIT_VIDEO);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

  SDL_Window *window = SDL_CreateWindow("OpenGL", 100, 100, 800, 600, SDL_WINDOW_OPENGL);
  SDL_GLContext context = SDL_GL_CreateContext(window);

  // Initialize GLEW
  glewExperimental = GL_TRUE;
  glewInit();

  coordinate_t position = { 0, -0.8 };
  character = new Character("res/spaceship.png", position);

  position.y = 0.8;
  enemy = new Enemy(position);

  // main loop
  // TODO: how to change the framerate?
  while (!quit) {
    startTime = SDL_GetTicks();

    handleKeys();
    update();
    render();

    SDL_GL_SwapWindow(window);
    
    if (1000/FPS > SDL_GetTicks() - startTime) {
      SDL_Delay(1000/FPS - (SDL_GetTicks() - startTime));
    }
  }

  SDL_GL_DeleteContext(context);
  SDL_Quit();

  return 0;
}


void
update()
{
  BulletRegistry::getInstance().tick();
  //if (enemy->screenPos.x >= -0.9) {
  //  enemy->move('l');
  //}
  //else {
  //  enemy->move('r');
  //}
}


void
handleKeys()
{
  SDL_Event windowEvent;

  if (SDL_PollEvent(&windowEvent)) {
    if (windowEvent.type == SDL_QUIT) {
      quit = true;
    }

    if (windowEvent.type == SDL_KEYUP) {
      // TODO: this won't really work if the user holds the key down
      // TODO: allow keys to be remapped
      switch (windowEvent.key.keysym.sym) {

      case SDLK_ESCAPE:
        quit = true;
        break;

      case SDLK_w:
        character->move('u');
        break;

      case SDLK_a:
        character->move('l');
        break;

      case SDLK_s:
        character->move('d');
        break;

      case SDLK_d:
        character->move('r');
        break;

      case SDLK_SPACE:
        character->fire();
        break;
      }
    }
  }
}


void
render()
{
  // Clear the screen to black
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Render each component on the screen
  character->render();
  enemy->render();
  BulletRegistry::getInstance().render();

}
