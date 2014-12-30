#ifndef ENEMYAI_H
#define ENEMYAI_H

#include <vector>
#include "Character.h"
#include "Enemy.h"


typedef struct {
  char direction;
  Enemy *enemy;
} EnemyStateMachine;


class EnemyAI {

  Character* player;

  std::vector<EnemyStateMachine> enemies;

public:

  EnemyAI();

  ~EnemyAI();

  void registerEnemy(Enemy*);

  void registerPlayer(Character*);

  void tick(int);
};

#endif
