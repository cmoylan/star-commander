#ifndef BULLET_REGISTRY_H
#define BULLET_REGISTRY_H

#include <stdio.h>
#include <vector>
// TODO: move to opengl.h ???
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "OpenGL.h"
#include "Util.h"
#include "Constants.h"

#define BULLET_WIDTH 2
#define BULLET_HEIGHT 5

// TODO: just use a vector?
typedef struct {
  int x;
  int y;
} Heading;

typedef struct {
  Rectangle element;
  int speed;
  Heading heading;
  bool removed;
} Bullet;

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

class BulletRegistry {

public:
  static BulletRegistry& getInstance()
  {
    static BulletRegistry instance;
    return instance;
  }

  std::vector<Bullet> bullets;

  /**
   * Add a new bullet to the screen
   *
   * @param element - a Rectangle representing the element that is firing
   * @param heading - heading of the bullet
   *
   * The headings correspond to the OpenGL coordinate system. That is, a bullet heading
   * up the screen will have a heading of (0, 1) as 1 is the top of the screen. A bullet
   * heading left will have the heading (-1, 0). A bullet heading diagonally to the top
   * right corner would have a heading (1, 1). A bullet with a (0, 0) heading would not
   * be moving.
   */
  void add(Rectangle firingElement, Heading heading);

  /**
   * Flush bullets flagged for removal
   */
  void flush();

  void print();

  std::vector<Bullet>::iterator remove(std::vector<Bullet>::iterator position);

  void render();

  void tick();

private:
  // --- Singleton things
  BulletRegistry();//BulletRegistry() {}; // Don't implement
  BulletRegistry(BulletRegistry const&); // Don't implement
  void operator=(BulletRegistry const&); // Don't implement

  // --- OpenGL
  GLuint vao, vbo, ebo, uniTrans, uniColor;
  GLuint shaderProgram;

  void initGL();

};

#endif
