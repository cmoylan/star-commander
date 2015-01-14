#pragma once

#include <SDL2/SDL_ttf.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "OpenGL.h"
#include "Constants.h"
#include "Util.h"


class ScoreDisplay {

    TTF_Font* font;

    GLuint vao, tex, shaderProgram;

    //SDL_Surface* surface;

    void initGL();

 public:

    ScoreDisplay();

    ~ScoreDisplay();

    void render();

    void setScore(int score);
};
