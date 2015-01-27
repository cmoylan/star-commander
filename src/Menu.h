#pragma once


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

};
