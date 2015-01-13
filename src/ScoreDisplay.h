#pragma once

#include <SDL2/SDL_ttf.h>

#include "OpenGL.h"
#include "Constants.h"
#include "Util.h"


class ScoreDisplay {

    TTF_Font* font;

    GLuint vao, tex, shaderProgram;

    void initGL();

 public:

    ScoreDisplay();

    ~ScoreDisplay();

    void render();
};
