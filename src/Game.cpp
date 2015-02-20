#include "Game.h"


Game::Game()
{
    sprintf(scoreString, "%s%d", BASE_SCORE_STRING, score);
}


void
Game::addPoints(int points)
{
    score += points;
    sprintf(scoreString, "%s%d", BASE_SCORE_STRING, score);
}


void
Game::removePoints(int points)
{
    score -= points;
    sprintf(scoreString, "%s%d", BASE_SCORE_STRING, score);
}


void
Game::reset()
{
    running = true;
    paused = false;
    score = 0;
}


void
Game::run()
{
    Uint32 startTime;
    int ticks = 0;

    reset();

    // main loop
    while (running) {
        // count every 10 frames
        if (ticks > 9) {
            ticks = 0;
        }

        startTime = SDL_GetTicks();

        if (!paused) {
            update(ticks);
        }

        render();

        SDL_GL_SwapWindow(window);

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            // TODO: return boolean indicating if input was handled
            handleInput(&event);
        }
        character->move(playerInputX, playerInputY);

        if (1000 / FPS > SDL_GetTicks() - startTime) {
            SDL_Delay(1000 / FPS - (SDL_GetTicks() - startTime));
        }

        ticks += 1;
    }

    cleanup();
}


void
Game::render()
{
    // Clear the screen to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Render each component on the screen
    background->render();
    character->render();
    enemy->render();
    BulletRegistry::getInstance().render();

    scoreDisplay();

    if (menu->showing) {
        menu->render();
    }
}


void
Game::scoreDisplay()
{
    // color of the font
    GLfloat green[4] = {0, 1, 0, 1};
    GLfloat red[4] = { 1, 0, 0, 1 };

    //TextRenderer::getInstance()->renderTextDefaultScale(scoreString,
    //                                        -1 + 375,   1 - 25,
    //                                        green, 32);
    float textScaleX = 2.0f / WINDOW_WIDTH;
    float textScaleY = 2.0f / WINDOW_HEIGHT;
    //printf("text scale %f\n", textScaleX);
    TextRenderer::getInstance()->renderText(scoreString,
                                            -1 + 375,   1 - 25,
    					    textScaleX, textScaleY,
                                            green, 32);

}


void
Game::update(int ticks)
{
    background->tick(ticks);
    BulletRegistry::getInstance().tick();

    // enemy logic here
    enemyAI->tick(ticks);
    collisionManager->tick();
}
