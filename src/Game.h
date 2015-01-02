#ifndef GAME_H
#define GAME_H

#include <stdio.h>


class Game {

  int score;

 public:
  static Game& getInstance()
  {
    static Game instance;
    return instance;
  }

  void addPoints(int points = 1);

  void removePoints(int points = 1);

  void resetScore();

 private:
  // --- Singleton things
  Game(); // Don't implement
  Game(Game const&); // Don't implement
  void operator=(Game const&); // Don't implement

};

#endif
