#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include <vector>

#include "Entity.h"
#include "BulletRegistry.h"


class CollisionManager {

  std::vector<Entity*> entities;
  std::vector<BulletRegistry*> bulletRegistries;
  //BulletRegistry *bulletRegistry;

public:

  void registerEntity(Entity *entity);

  void registerBulletRegistry(BulletRegistry *registry);

  void tick();

};

#endif
