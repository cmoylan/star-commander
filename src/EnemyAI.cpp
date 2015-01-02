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
EnemyAI::registerEnemy(Enemy* enemy)
{
  EnemyStateMachine enemySm = { 'l', enemy };
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
  char direction;
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
      sm->direction = (sm->direction == 'l') ? 'r' : 'l';
    }

    // if we get to the edge of the screen, go the other way
    if (direction == 'r' && enemy->edgeRight() < SCREEN_X) {
      sm->enemy->move(1, 0);
    }
    else if (direction == 'r' && enemy->edgeRight() >= SCREEN_X) {
      sm->direction = 'l';
    }
    else if (direction == 'l' && enemy->edgeLeft() > -SCREEN_X) {
      sm->enemy->move(-1, 0);
    }
    else if (direction == 'l' && enemy->edgeLeft() <= -SCREEN_X) {
      sm->direction = 'r';
    }

    // --- occasionally fire
    // Seems to fire often enough
    if (random > 30 && random < 35) {
      enemy->fire();
    }
  }
}
