#ifndef ENEMY_H
#define ENEMY_H

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "OpenGL.h"
#include "Util.h"
#include "Constants.h"
#include "Entity.h"
#include "BulletRegistry.h"
#include "Sound.h"
#include "Game.h"


class Game;


class Enemy : public Entity {

    Game* game;

public:
    // constructor
    Enemy(Game* game, std::string texture, Coordinate position);

    // destructor
    ~Enemy();

    int edgeBottom();
    int edgeLeft();
    int edgeRight();
    int edgeTop();

    void fire();

    void move(int x, int y);

    virtual void hit();
};

#endif
