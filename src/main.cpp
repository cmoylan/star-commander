#include "OpenGL.h"
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "Character.h"
#include "Enemy.h"
#include "BulletRegistry.h"
#include "CollisionManager.h"
#include "EnemyAI.h"
#include "Sound.h"
#include "Game.h"
#include "ScoreDisplay.h"


// window/display
SDL_Window *window;
SDL_GLContext context;
ScoreDisplay *score;

Character *character;
Enemy *enemy;
CollisionManager *collisionManager;
EnemyAI *enemyAI; // enemy AI manager

bool quit = false;
int playerInputX = 0;
int playerInputY = 0;


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

    score = new ScoreDisplay();
    Game::getInstance().resetScore();

    // main loop
    while (!quit) {
        // count every 10 frames
        if (ticks > 9) {
            ticks = 0;
        }

        startTime = SDL_GetTicks();

        update(ticks);
        handleKeys();
        render();

	SDL_GL_SwapWindow(window);

	// TODO: fix the framerate
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
    enemy = new Enemy("res/enemy.png", position);

    position.y = -65;
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

    // Font initialization
    if (TTF_Init() == -1) {
        printf("Unable to initialize SDL_ttf: %s\n", TTF_GetError());
    }
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
    BulletRegistry::getInstance().tick();
    enemyAI->tick(ticks);
    collisionManager->tick();
}


void
handleKeys()
{
    // TODO: still a little weird, fix framerate
    SDL_Event windowEvent;

    if (SDL_PollEvent(&windowEvent)) {
        if (windowEvent.type == SDL_QUIT) {
            quit = true;
        }

        if (windowEvent.type == SDL_KEYDOWN) {
            // TODO: allow keys to be remapped
            switch (windowEvent.key.keysym.sym) {
            case SDLK_ESCAPE:
                quit = true;
                break;
            case SDLK_w:
                playerInputY = 1;
                break;
            case SDLK_a:
                playerInputX = -1;
                break;
            case SDLK_s:
                playerInputY = -1;
                break;
            case SDLK_d:
                playerInputX = 1;
                break;
            case SDLK_SPACE:
                character->fire();
                break;
            }
        }

        if (windowEvent.type == SDL_KEYUP) {
            switch (windowEvent.key.keysym.sym) {
            case SDLK_w:
            case SDLK_s:
                playerInputY = 0;
                break;
            case SDLK_a:
            case SDLK_d:
                playerInputX = 0;
                break;
            }
        }

        character->move(playerInputX, playerInputY);
    }
}


void
render()
{
    // Clear the screen to black
    //glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Render each component on the screen
    BulletRegistry::getInstance().render();
    character->render();
    enemy->render();

    score->render();
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
