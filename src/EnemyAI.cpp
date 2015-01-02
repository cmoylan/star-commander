#include "EnemyAI.h"

EnemyAI::EnemyAI()
{
  time(&seconds);
  srand((unsigned int) seconds);
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
  if (ticks != 0) { return; }

  std::vector<EnemyStateMachine>::iterator sm;
  Enemy *enemy;
  char direction;
  // rand() % (HIGH - LOW + 1) + LOW;
  int random = rand() % (100 - 0 + 1);

  //printf("rand is %d\n", random);

  for (sm = enemies.begin(); sm != enemies.end(); ++sm) {
    enemy = sm->enemy;
    direction = sm->direction;

    // --- randomly change directions
    if (random + 20 > 100) {
      if (sm->direction == 'r') {
	sm->direction = 'l';
      }
      else {
	sm->direction = 'r';
      }
    }

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
    if (random > 30 && random < 40) {
      enemy->fire();
    }
  }
}
