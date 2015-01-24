#include "Enemy.h"


Enemy::Enemy(Game* game, std::string texture, Coordinate position)
{
    this->game = game;

    // TODO: default to center if no position specified
    size.x = 20;
    size.y = 20;

    origin.x = position.x - (size.x / 2);
    origin.y = position.y - (size.y / 2);

    initGL(texture);
}


Enemy::~Enemy()
{
    glDeleteProgram(shaderProgram);
    glDeleteVertexArrays(1, &vao);
}


int
Enemy::edgeBottom()
{
    return origin.y;
}


int
Enemy::edgeLeft()
{
    return origin.x;
}


int
Enemy::edgeRight()
{
    return origin.x + size.x;
}


int
Enemy::edgeTop()
{
    return origin.y + size.y;
}


void
Enemy::fire()
{
    // Add a bullet moving down
    //BulletRegistry::getInstance().add(screenPos.x, screenPos.y, 0, -1);
    Heading heading = { 0, -1 };
    Rectangle element = { origin, size };

    BulletRegistry::getInstance().add(element, heading);
    Sound::getInstance()->play("enemy-laser");
}


void
Enemy::hit()
{
    printf("enemy was hit at: [%d, %d]\n", origin);
    // add 1 to score
    game->addPoints();
    Sound::getInstance()->play("hit");
}


void
Enemy::move(int x, int y)
{
    int newX = origin.x;
    int newY = origin.y;
    int movementSize = ENEMY_MOVE_SIZE;

    newX += (x * movementSize);
    newY += (y * movementSize);

    if ((newX >= -SCREEN_X) && ((newX + size.x) <= SCREEN_X)) {
        origin.x = newX;
    }
    if ((newY >= -SCREEN_Y) && ((newY + size.y) <= SCREEN_Y)) {
        origin.y = newY;
    }
    //printf("moved to %f, %f\n", newX, newY);
}
