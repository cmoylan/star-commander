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

// DEPRECATED - moving to vectors over points
typedef struct {
  // TODO: change this back to int probably
  float x;
  float y;
} coordinate_t;

typedef struct {
  float x;
  float y;
} Vector2D;

typedef struct {
  Vector2D origin;
  Vector2D size;
} Rectangle;

#endif
