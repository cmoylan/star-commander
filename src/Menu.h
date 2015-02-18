#pragma once

#include "Constants.h"
#include "TextRenderer.h"


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
    void renderText(const char* text, FontAtlas* a, float x, float y, float sx,
                    float sy);

    void toggle();

    // callbacks
    void newGame();
    void quit();

private:
    int leftEdge;
};
