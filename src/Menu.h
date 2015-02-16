#pragma once

#include <algorithm>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "Constants.h"
#include "FontAtlas.h"
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
    FontAtlas* font48;

    Menu();
    ~Menu();

    void render();
    // old signature
    void renderText(const char *text, float x, float y, float sx, float sy);
    void renderText(const char* text, FontAtlas* a, float x, float y, float sx, float sy);

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
