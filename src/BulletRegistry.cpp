#include "BulletRegistry.h"

void
BulletRegistry::add(float x, float y, int headingX, int headingY)
{
  coordinate_t location;
  heading_t heading;
  bullet_t bullet;

  location.x = x;
  location.y = y;

  heading.x = headingX;
  heading.y = headingY;

  bullet.location = location;
  bullet.heading = heading;
  bullet.speed = 1.0f;

  bullets.push_back(bullet);
}


void
BulletRegistry::render()
{
  // iterator
}


void
BulletRegistry::tick()
{
  std::vector<bullet_t>::iterator bullet;

  for (bullet = bullets.begin(); bullet != bullets.end(); ++bullet) {
    // move
    printf("bullet\n");
  }
}
