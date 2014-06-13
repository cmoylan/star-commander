#include "OpenGL.h"
#include "Character.h"
#include "BulletRegistry.h"

bool quit = false;

// main character
Character *character;

void update();

void handleKeys();

void render();


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

  character = new Character();

  BulletRegistry::add(1, 1, 1, 1);
  BulletRegistry::add(2, 2, 2, 2);
  BulletRegistry::add(3, 3, 3, 3);
  BulletRegistry::print();
  std::vector<bullet_t>::iterator bullet = BulletRegistry::bullets.begin();
  //printf("pointer in main is: %p\n", &bullet);
  BulletRegistry::remove(bullet);
  BulletRegistry::print();

  quit = true; // don't run
  // main loop
  // TODO: how to change the framerate?
  while (!quit) {
    handleKeys();
    update();
  GLuint ebo;
  glGenBuffers(1, &ebo);

  GLuint elements[] = {
    0, 1, 2,
    2, 3, 0
  };

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
	       sizeof(elements),
	       elements,
	       GL_STATIC_DRAW);

    -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,  // top left
    0.5f, 0.5f, 0.0f, 1.0f, 0.0f, // top right
    0.5f, -0.5f, 0.0f, 0.0f, 1.0f,  // bottom right
    -0.5f, -0.5f, 1.0f, 1.0f, 1.0f // bottom left

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
}


void
update()
{
  BulletRegistry::tick();
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
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    //glDrawArrays(GL_TRIANGLES, 0, 3);

}


void
render()
{
  // Clear the screen to black
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Render each component on the screen
  character->render();
}
