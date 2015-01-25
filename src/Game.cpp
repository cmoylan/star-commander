#include "Game.h"


Game::Game()
{
}


void
Game::addPoints(int points)
{
    printf("adding [%d] point for player\n", points);
    score += points;
    printf("players score is: [%d]\n", score);
}


void
Game::removePoints(int points)
{
    printf("removing [%d] points for player\n", points);
    score -= points;
    printf("players score is: [%d]\n", score);
}


void
Game::reset()
{
    running = true;
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

        update(ticks);
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