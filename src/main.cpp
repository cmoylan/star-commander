#include "OpenGL.h"
#include <SDL2/SDL_mixer.h>

#include "Character.h"
#include "Enemy.h"
#include "BulletRegistry.h"
#include "CollisionManager.h"
#include "EnemyAI.h"
#include "Sound.h"
#include "Game.h"


bool quit = false;

// global openGL objects
SDL_Window *window;
SDL_GLContext context;

Character *character;
Enemy *enemy;
CollisionManager *collisionManager;
EnemyAI *enemyAI; // enemy AI manager

void initAI();
void initEntities();
void initSDL();
void initAudio();
void cleanup();
void update(int ticks);
void handleKeys();
void render();
void debug();


int
//main(int argc, char *args[])
main()
{
    Uint32 startTime;
    int ticks = 0;

    initSDL();
    initAudio();
    initEntities();
    initAI();

    Game::getInstance().resetScore();

    // main loop
    // TODO: how to change the framerate?
    while (!quit) {
        // count every 10 frames
        if (ticks > 9) {
            ticks = 0;
        }

        startTime = SDL_GetTicks();

        //printf("ticks:: %d\n", ticks);
        update(ticks);
        handleKeys();
        render();

        SDL_GL_SwapWindow(window);

        if (1000 / FPS > SDL_GetTicks() - startTime) {
            SDL_Delay(1000 / FPS - (SDL_GetTicks() - startTime));
        }

        ticks += 1;
    }

    cleanup();

    return 0;
}


void
initAI()
{
    // setup enemy AI
    enemyAI = new EnemyAI();
    enemyAI->registerPlayer(character);
    enemyAI->registerEnemy(enemy);

    collisionManager = new CollisionManager();
    collisionManager->registerEntity(character);
    collisionManager->registerEntity(enemy);
}


void
initEntities()
{
    Coordinate position = { 30, 80 };
    enemy = new Enemy(position);

    position.y = -70;
    character = new Character("res/spaceship.png", position);
}


void
initSDL()
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    // --- Audio initialization
    // TODO: remove magic numbers
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
    //Mix_Volume(0 - 128);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    // TODO: remove magic numbers
    window = SDL_CreateWindow("OpenGL", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    context = SDL_GL_CreateContext(window);

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    glewInit();
}


void
initAudio()
{
    Sound *sound = Sound::getInstance();

    sound->load("laser", "res/laser.wav");
    sound->load("enemy-laser", "res/enemy-laser.wav");
    sound->load("hit", "res/hit.wav");
}


void
cleanup()
{
    Sound::getInstance()->freeAll();
    Mix_CloseAudio();

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


void
update(int ticks)
{
    //printf("ticking: %d\n", ticks);
    BulletRegistry::getInstance().tick();

    // enemy logic here
    enemyAI->tick(ticks);
    collisionManager->tick();
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
    //enemy2->render();
    BulletRegistry::getInstance().render();

}


void debug()
{
    SDL_version compile_version;
    const SDL_version *link_version = Mix_Linked_Version();
    SDL_MIXER_VERSION(&compile_version);
    printf("compiled with SDL_mixer version: %d.%d.%d\n",
           compile_version.major,
           compile_version.minor,
           compile_version.patch);
    printf("running with SDL_mixer version: %d.%d.%d\n",
           link_version->major,
           link_version->minor,
           link_version->patch);
}
