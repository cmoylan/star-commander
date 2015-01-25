#include "EnemyAI.h"

EnemyAI::EnemyAI()
{
    time(&secondSeed);
    srand((unsigned int) secondSeed);
    //distribution(1, 100);
}


EnemyAI::~EnemyAI()
{
}


void
EnemyAI::avoidBullets(EnemyStateMachine* enemy)
{
    // TODO: left off here
    // need to ask the bullet registry it there are any bullets nearby
    // probably need to make up some new data structure to make it easy to look that up
}


void
EnemyAI::registerEnemy(Enemy* enemy)
{
    Vector2D direction = {1, 0};
    EnemyStateMachine enemySm = { direction, enemy };
    enemies.push_back(enemySm);
}


void
EnemyAI::registerPlayer(Character* character)
{
    player = character;
}


void
EnemyAI::tick(int ticks)
{
    // slow down the enemy
    //if (ticks != 0) { return; }

    std::vector<EnemyStateMachine>::iterator sm;
    Enemy *enemy;
    Vector2D direction;
    int random;

    //printf("rand is %d\n", random);

    for (sm = enemies.begin(); sm != enemies.end(); ++sm) {
        enemy = sm->enemy;
        direction = sm->direction;
        // rand() % (HIGH - LOW + 1) + LOW;
        random = rand() % (100 - 0 + 1);
        //random = distribution(generator);

        // --- randomly change directions
        // restricting chance of direction change makes the enemy less chaotic
        if (random > 5 && random < 8) {
            sm->direction.x = (sm->direction.x == 1) ? 0 : 1;
        }

        /* TODO: change logic to:
        *       if within SCREEN_x/y, pass direction to enemy->move
         *       otherwise switch directions (multiply dir.x by -1)
         */
        // --- going right
        // keep going
        if (direction.x == 1 && enemy->edgeRight() < SCREEN_X) {
            sm->enemy->move(1, 0);
        }
        // switch direction
        else if (direction.x == 1 && enemy->edgeRight() >= SCREEN_X) {
            sm->direction.x = -1;
        }

        // --- going left
        // keep going
        else if (direction.x == -1 && enemy->edgeLeft() > -SCREEN_X) {
            sm->enemy->move(-1, 0);
        }
        // switch direction
        else if (direction.x == -1 && enemy->edgeLeft() <= -SCREEN_X) {
            sm->direction.x = 1;
        }

        // --- occasionally fire
        // Seems to fire often enough
        if (random > 30 && random < 35) {
            enemy->fire();
        }
    }
}
