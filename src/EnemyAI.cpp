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
  enemy_state_machine_t enemySm = {
    'l',
    enemy
  };

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

  std::vector<enemy_state_machine_t>::iterator sm;
  Enemy *enemy;
  char direction;

  for (sm = enemies.begin(); sm != enemies.end(); ++sm) {
    enemy = sm->enemy;
    direction = sm->direction;
    // if we are moving right, and we are under 0.9, continue moving right
    // if we are moving right and we are at 1, move left
    // if we are moving left and we are over -0.9, continue moving left
    // if we are moving left and we are at 1, move right

    // move somewhere
    if (direction == 'r' && enemy->screenPos.x < 0.9) {
      //sm->enemy->screenPos.x += 0.1;
      sm->enemy->move(1, 0);
    }
    else if (direction == 'r' && enemy->screenPos.x < 1) {
      sm->direction = 'l';
    }
    else if (direction == 'l' && enemy->screenPos.x > -0.9) {
      //sm->enemy->screenPos.x -= 0.1;
      sm->enemy->move(-1, 0);
    }
    else if (direction == 'l' && enemy->screenPos.x > -1) {
      sm->direction = 'r';
    }
    //printf("screenpos->%f\n", sm->enemy->screenPos.x);
  }
}
