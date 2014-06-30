#ifndef BULLET_REGISTRY_H
#define BULLET_REGISTRY_H

#include <vector>
#include "Constants.h"

typedef struct {
  int x;
  int y;
} heading_t;

typedef struct {
  coordinate_t location;
  float speed;
  heading_t heading;
} bullet_t;

// --- Singleton example --- //
//class Log {
//  public:
//    static Log* Inst(char* filename);
//    void Logging(string message);
//    void Initialize();
//    ~Log();
//  protected:
//    Log(); // constructor
//  private:
//    static Log* pInstance;
//};



class BulletRegistry
{

 public:
  static BulletRegistry& getInstance()
  {
    static BulletRegistry instance;
    return instance;
  }

  // TODO: if #erase operations become too expensive, consider switching to
  //       forward-lists.
  std::vector<bullet_t> bullets;

  /**
   * Add a new bullet to the screen
   *
   * @param x - location of the bullet on the X axis
   * @param y - location of the bullet on the Y axis
   * @param headingX - heading of the bullet on the X axis (-1, 0, or 1)
   * @param headingY - heading of the bullet on the Y axis (-1, 0, 1)
   *
   * The headings correspond to the OpenGL coordinate system. That is, a bullet heading
   * up the screen will have a heading of (0, 1) as 1 is the top of the screen. A bullet
   * heading left will have the heading (-1, 0). A bullet heading diagonally to the top
   * right corner would have a heading (1, 1). A bullet with a (0, 0) heading would not
   * be moving.
   */
  void add(float x, float y, int headingX, int headingY);

  void print();

  void remove(std::vector<bullet_t>::iterator position);

  void render();

  void tick();

 private:
  BulletRegistry() {}; // Don't implement
  BulletRegistry(BulletRegistry const&); // Don't implement
  void operator=(BulletRegistry const&); // Don't implement

};

#endif
