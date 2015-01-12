#ifndef CHARACTER_H
#define CHARACTER_H

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


class Character : public Entity {

    // opengl stuff
    // TODO: rename most of these, they are awful
    GLuint vao, tex, uniTrans;
    GLuint shaderProgram;

    void initGL(std::string texture);

public:

    // constructor
    Character(std::string texture, Coordinate potision);

    // destructor
    ~Character();

    void center();

    void fire();

    // TODO: probably should take a heading or something...
    void move(unsigned char direction);

    void render();

    virtual void hit();

};

#endif
