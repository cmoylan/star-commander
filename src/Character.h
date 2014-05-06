#ifndef CHARACTER_H
#define CHARACTER_H


#include "OpenGL.h"
#include "Constants.h"
#include "Level.h"


// NOTE: should this be a singleton? Can there ever be > 1?
class Character {

public:
  // the location of the character in the level
  int levelPosX;
  int levelPosY;

  // the location of the character on the screen
  int screenPosX;
  int screenPosY;

  // size of the actual character
  int width;
  int height;

  // reference to the current level
  Level *currentLevel;

  // constructor
  Character(Level *level);

  // destructor
  ~Character();

  void move(unsigned char direction);

  void render();

};

#endif
