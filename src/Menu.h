#pragma once


class Menu {

public:
    bool showing;

    static Menu* getInstance()
    {
        static Menu instance;
        return &instance;
    }

    void render();

private:
    // --- Singleton things
    Menu() {}; // Don't implement
    Menu(Menu const&); // Don't implement
    void operator=(Menu const&); // Don't implement

};