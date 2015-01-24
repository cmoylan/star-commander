#include "Game.h"

void
Game::cleanup()
{
    Sound::getInstance()->freeAll();
    Mix_CloseAudio();

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


void
Game::init()
{
    initSDL();
    initAudio();
    initEntities();
    initAI();
}


void
Game::initAI()
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
Game::initAudio()
{
    Sound *sound = Sound::getInstance();

    sound->load("laser", "res/laser.wav");
    sound->load("enemy-laser", "res/enemy-laser.wav");
    sound->load("hit", "res/hit.wav");
}


void
Game::initEntities()
{
    Coordinate position = { 30, 80 };
    this->enemy = new Enemy("res/enemy.png", position);

    position.y = -70;
    this->character = new Character("res/spaceship.png", position);
}


void
Game::initSDL()
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
