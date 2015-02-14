#pragma once

// TODO: move into opengl.h?
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <FTGL/ftgl.h>

#include "Constants.h"
#include "OpenGL.h"
#include "Util.h"


class Menu {

public:
    enum menuItems {
        NewGame, Quit
    };
    bool showing;
    menuItems currentSelection;
    int itemWidth;
    int itemHeight;
    FTPixmapFont* font;
  
    Menu();
    ~Menu();

    void render();

    void toggle();

    // callbacks
    void newGame();
    void quit();

private:
    int leftEdge;

    // --- OpenGL
    GLuint vao, uniTrans, uniColor;
    GLuint shaderProgram;

    // TODO: there will be more of these
    GLuint tex, tex2;

    void initGL();

};
