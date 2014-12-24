#ifndef ENEMYAI_H
#define ENEMYAI_H

#include <vector>
#include "Character.h"
#include "Enemy.h"


typedef struct {
  char direction;
  Enemy *enemy;
} enemy_state_machine_t;


class EnemyAI {
  Character* player;

  std::vector<enemy_state_machine_t> enemies;

 public:
  EnemyAI();

  ~EnemyAI();

  void registerEnemy(Enemy*);

  void registerPlayer(Character*);

  void tick(int);
};

#endif
