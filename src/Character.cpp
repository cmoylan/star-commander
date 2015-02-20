#include "Character.h"


Character::Character(Game* game, std::string texture, Coordinate position)
{
    this->game = game;

    size.x = 20;
    size.y = 20;

    origin.x = position.x - (size.x / 2);
    origin.y = position.y - (size.y / 2);

    //printf("origin is: [%d %d] \n", origin);
    initGL(texture);
}


Character::~Character()
{
    //printf("-- character destructor\n");
    glDeleteProgram(shaderProgram);
    glDeleteVertexArrays(1, &vao);
}


void
Character::center()
{
    origin.x = -(size.x / 2);
    origin.y = -(size.y / 2);
}


void
Character::fire()
{
    Vector2D heading = { 0, 1 };
    Rectangle element = { origin, size };

    BulletRegistry::getInstance().add(element, heading);
    Sound::getInstance()->play("laser");
}


void
Character::hit()
{
    //printf("character was hit at: [%d, %d]\n", origin);
    game->removePoints();
    Sound::getInstance()->play("hit");
}





void
Character::move(int x, int y)
{
    int newX = origin.x;
    int newY = origin.y;
    int movementSize = CHARACTER_MOVE_SIZE;

    newX += (x * movementSize);
    newY += (y * movementSize);

    // TODO: figure out your coordinate system
    if ((newX >= -SCREEN_X) && ((newX + size.x) <= SCREEN_X)) {
        origin.x = newX;
    }
    if ((newY >= -SCREEN_Y) && ((newY + size.y) <= SCREEN_Y)) {
        origin.y = newY;
    }
    //printf("newx and y are: [%dd, %d]\n", newX, newY);
}