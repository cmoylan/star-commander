#pragma once

#include <cstdlib>
#include <time.h>
//#include <random>
#include <vector>

#include "Constants.h"
#include "Character.h"
#include "Enemy.h"


class Character;
class Enemy;

typedef struct {
    Vector2D direction;
    Enemy *enemy;
    bool evading;
} EnemyStateMachine;


class EnemyAI {

    Character* player;

    // --- <random> stuff
    time_t secondSeed;
    //std::default_random_engine generator;
    //std::uniform_int_distribution<int> distribution;

    std::vector<EnemyStateMachine> enemies;

public:

    EnemyAI();

    ~EnemyAI();

    // management
    void registerEnemy(Enemy*);
    void registerPlayer(Character*);
    void tick(int);

    // logic
    void avoidBullets(std::vector<EnemyStateMachine>::iterator enemySm);

};