#ifndef CONSTANTS_H
#define CONSTANTS_H


#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

// screen constants
#define SCREEN_X 100
#define SCREEN_Y 100
// TODO: caculate from screen_x and screen_y
#define SCALE_X 0.01f
#define SCALE_Y 0.01f

#define FPS 30

// character attributes
#define CHARACTER_MOVE_SIZE 2


typedef struct {
    int x;
    int y;
} Coordinate;

typedef struct {
    int x;
    int y;
} Vector2D;

typedef struct {
    Vector2D origin;
    Vector2D size;
} Rectangle;

#endif
