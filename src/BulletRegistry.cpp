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


std::vector<bullet_t>::iterator
BulletRegistry::remove(std::vector<bullet_t>::iterator position)
{
  printf("erasing bullet\n");
  return bullets.erase(position);
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

  for (bullet = bullets.begin(); bullet != bullets.end(); ) {
    // move
    bullet->location.x += bullet->heading.x * bullet->speed;
    bullet->location.y += bullet->heading.y * bullet->speed;

    printf("bullet x, y: %f, %f\n", bullet->location.x, bullet->location.y);

    // If the bullet is out of bounds, remove it
    if ((bullet->location.x > 1.0f) || (bullet->location.y > 1.0f)){
      bullet = remove(bullet);
    }
    // If the bullet has collided with something, handle it
    // else if (collision(bullet)) {
    //   handle_collision(bullet);
    // }
    // Otherwise, go to the next bullet
    else {
      ++bullet;
    }
  }
}
