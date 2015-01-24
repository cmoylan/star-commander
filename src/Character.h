#pragma once

#include <string>
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>

#include "OpenGL.h"
#include "Util.h"
#include "Constants.h"
#include "Entity.h"
#include "BulletRegistry.h"
#include "Sound.h"
#include "Game.h"


class Game;


class Character : public Entity {

    Game* game;

public:

    // constructor
    Character(Game* game, std::string texture, Coordinate potision);

    // destructor
    ~Character();

    void center();

    void fire();

    void move(int x, int y);

    virtual void hit();

};