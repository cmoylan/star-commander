#ifndef ENEMYAI_H
#define ENEMYAI_H

#include <vector>
#include "Character.h"


typedef struct {
  char direction;
  Character *enemy;
} enemy_state_machine_t;


class EnemyAI {
  Character* player;
  std::vector<enemy_state_machine_t> enemies;

 public:
  EnemyAI();

  ~EnemyAI();

  void registerEnemy(Character*);

  void registerPlayer(Character*);

  void tick(int);
};

#endif
