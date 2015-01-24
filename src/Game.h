#pragma once

#include <stdio.h>

#include "OpenGL.h"
#include <SDL2/SDL_mixer.h>

#include "BulletRegistry.h"
#include "Character.h"
#include "CollisionManager.h"
#include "Config.h"
#include "EnemyAI.h"
#include "Enemy.h"
//#include "InputHandler.h"
#include "Sound.h"


class Character;
class Enemy;
class EnemyAI;
class CollisionManager;

class Game {

    int score;
    bool running;

    // global openGL objects
    SDL_Window *window;
    SDL_GLContext context;

    Character *character;
    Enemy *enemy;
    CollisionManager *collisionManager;
    EnemyAI *enemyAI; // enemy AI manager

    int playerInputX;
    int playerInputY;

public:
    Game();

    ~Game();

    void addPoints(int points = 1);
    void removePoints(int points = 1);

    // Util methods
    void init();
    void render();
    void reset();
    void run();
    void update(int ticks);

    // Input methods
    void handleInput(SDL_Event* event);
    void handleKeyDown(SDL_Event* event);
    void handleKeyUp(SDL_Event* event);

private:
    // Utility methods
    void initAI();
    void initEntities();
    void initSDL();
    void initAudio();
    void cleanup();

};
