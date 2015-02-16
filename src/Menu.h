#pragma once

// TODO: move into opengl.h?
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Constants.h"
#include "OpenGL.h"
#include "Util.h"

// --- begin font --- //
#include <ft2build.h>
#include FT_FREETYPE_H
// --- end font --- //


class Menu {

public:
    enum menuItems {
        NewGame, Quit
    };
    bool showing;
    menuItems currentSelection;
    int itemWidth;
    int itemHeight;


    Menu();
    ~Menu();

    void render();
    void renderText(const char *text, float x, float y, float sx, float sy);

    void toggle();

    // callbacks
    void newGame();
    void quit();

private:
    int leftEdge;

    GLuint vao;
    GLuint vbo;
    GLuint shaderProgram;
    GLint attributeCoord;
    GLint uniformTex;
    GLint uniformColor;

    void initGL();

    FT_Library ft;
    FT_Face face;
    //FT_GlyphSlot g;
};
