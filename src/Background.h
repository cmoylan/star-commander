#pragma once

#include "Constants.h"
#include "Entity.h"


class Background : public Entity {

public:
    Background();

    ~Background();

    void render();

    virtual void hit() {};
};