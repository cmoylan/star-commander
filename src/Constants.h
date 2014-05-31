#ifndef CONSTANTS_H
#define CONSTANTS_H

// screen constants
const int SCREEN_WIDTH = 700;
const int SCREEN_HEIGHT = 700;
const int SCREEN_FPS = 60;

// The screen goes from -1.0f to 1.0f for a total of 2.0f width
// chop it into smaller units
const int SCALE = 100;
// TODO: probably use a different scale for y

struct coordinate_t {
  // TODO: change this back to int probably
  float x;
  float y;
};

#endif
