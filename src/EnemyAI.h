#ifndef ENEMYAI_H
#define ENEMYAI_H

#include <cstdlib>
#include <time.h>
#include <vector>

#include "Character.h"
#include "Enemy.h"


typedef struct {
  // TODO: direction is an enumeration
  char direction;
  Enemy *enemy;
} EnemyStateMachine;


class EnemyAI {

  Character* player;

  time_t seconds;

  std::vector<EnemyStateMachine> enemies;

public:

  EnemyAI();

  ~EnemyAI();

  void registerEnemy(Enemy*);

  void registerPlayer(Character*);

  void tick(int);
};

#endif
