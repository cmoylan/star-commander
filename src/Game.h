#pragma once

#include <stdio.h>
#include <string>

#include "OpenGL.h"
#include <SDL2/SDL_mixer.h>

#include "Background.h"
#include "BulletRegistry.h"
#include "Character.h"
#include "CollisionManager.h"
#include "EnemyAI.h"
#include "Enemy.h"
#include "Menu.h"
#include "Sound.h"
#include "TextRenderer.h"


class Character;
class Enemy;
class EnemyAI;
class CollisionManager;
class Background;
class Menu;

class Game {

    int score;
    bool running;
    bool paused;
    char scoreString[10];
    GLfloat scoreColor[4];

    // global openGL objects
    SDL_Window *window;
    SDL_GLContext context;

    // renderables
    Background* background;
    Character *character;
    Enemy *enemy;

    // logic
    CollisionManager *collisionManager;
    EnemyAI *enemyAI; // enemy AI manager

    Menu* menu;

    int playerInputX;
    int playerInputY;

public:
    Game();

    ~Game();

    void addPoints(int points = 1);
    void removePoints(int points = 1);
    void scoreDisplay();

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
