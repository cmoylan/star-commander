#ifndef CONSTANTS_H
#define CONSTANTS_H

// screen constants
const int SCREEN_WIDTH = 700;
const int SCREEN_HEIGHT = 700;
const int SCREEN_FPS = 60;

// color modes
const int COLOR_MODE_CYAN = 0;
const int COLOR_MODE_MULTI = 1;

// level constants
// -- how much of the level to display on screen
// -- TODO: this should be renamed
// screen_level_width
// screen_level_height
// - how much of the level fits on the screen
const int LEVEL_WIDTH = 11;
const int LEVEL_HEIGHT = 11;

// -- how big each box is
const float BOX_WIDTH = SCREEN_WIDTH / LEVEL_WIDTH;
const float BOX_HEIGHT = SCREEN_HEIGHT / LEVEL_HEIGHT;

struct coordinate_t {
  // TODO: change this back to int probably
  float x;
  float y;
};

#endif
