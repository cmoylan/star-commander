#pragma once


#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

// screen constants
#define SCREEN_X 100
#define SCREEN_Y 100

#define SCALE_X 0.01f
#define SCALE_Y 0.01f

#define FPS 30

#define SCORE_HEIGHT 10

// character attributes
#define CHARACTER_MOVE_SIZE 5


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
