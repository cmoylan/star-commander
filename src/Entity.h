#ifndef ENTITY_H
#define ENTITY_H

#include "Constants.h"

class Entity {

public:

    // allow direct access to these...why not
    Vector2D origin;
    Vector2D size;

    virtual void hit() = 0;

};

#endif
