#include "BulletRegistry.h"


BulletRegistry::BulletRegistry()
{
}


BulletRegistry::~BulletRegistry()
{
}


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
  bullet.speed = 0.1;

  bullets.push_back(bullet);

  printf("bullet fired\n");
}


void
BulletRegistry::print()
{
  std::vector<bullet_t>::iterator bullet;
  int i;

  for (bullet = bullets.begin(), i=0; bullet != bullets.end(); ++bullet, i++) {
    printf("bullet #%d (x, y): %f, %f\n", i, bullet->location.x, bullet->location.y);
  }

}


void
BulletRegistry::remove(std::vector<bullet_t>::iterator position)
{
  printf("erasing bullet\n");
  //printf("pointer in remove is: %p\n", &position);
  //bullets.erase(bullets.begin());
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
    bullet->location.x += bullet->heading.x * bullet->speed;
    bullet->location.y += bullet->heading.y * bullet->speed;

    // If the bullet is out of bounds, remove it
//    if (bullet->location.x > 1.0f) {
//      remove(bullet);
//    }
//    if (bullet->location.y > 1.0f) {
//      printf("trying to remove \n");
//      remove(bullet);
//    }
    // check for collision
    // destroy if collision
    //printf("bullet\n");
    printf("bullet x, y: %f, %f\n", bullet->location.x, bullet->location.y);
  }

  if (bullets.size() > 3) {
    printf("removing bullet\n");
    remove(bullets.begin());
  }
}
