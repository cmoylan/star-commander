#pragma once

#include "Constants.h"
#include "Entity.h"


class Background : public Entity {

    Vector2D offset;

public:
    Background();

    ~Background();

    void render();

    void tick(int ticks);

    virtual void hit() {};
};