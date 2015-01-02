#include "EnemyAI.h"

EnemyAI::EnemyAI()
{
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

  for (sm = enemies.begin(); sm != enemies.end(); ++sm) {
    enemy = sm->enemy;
    direction = sm->direction;

    // randomly change directions

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

    // occasionally fire
    if (enemy->origin.x == 0) {
      enemy->fire();
    }
  }
}
