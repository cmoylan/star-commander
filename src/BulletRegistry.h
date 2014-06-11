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

namespace BulletRegistry
{

static std::vector<bullet_t> bullets;

void add(float x, float y, int headingX, int headingY);

//void remove();

void render();

void tick();

};

#endif
