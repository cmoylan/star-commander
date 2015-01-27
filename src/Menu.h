#pragma once

#include "Constants.h"
#include "OpenGL.h"
#include "Util.h"


class Menu {

public:
    enum MenuItem {
	NewGame, Quit
    };
    bool showing;
    MenuItem currentSelection;

    Menu();
    ~Menu();

    void render();

    // callbacks
    void newGame();
    void quit();
    
private:
    // --- OpenGL
    GLuint vao, vbo, ebo, uniTrans, uniColor;
    GLuint shaderProgram;

    void initGL();

};
