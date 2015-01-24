#include "Game.h"

void
Game::handleInput(SDL_Event* event)
{
    //if (SDL_PollEvent(&windowEvent)) {
    if (event->type == SDL_QUIT) {
        running = false;
    }

    if (event->type == SDL_KEYDOWN) {
        // TODO: allow keys to be remapped
        switch (event->key.keysym.sym) {
        case SDLK_ESCAPE:
            running = false;
            break;
        case SDLK_w:
            playerInputY = 1;
            break;
        case SDLK_a:
            playerInputX = -1;
            break;
        case SDLK_s:
            playerInputY = -1;
            break;
        case SDLK_d:
            playerInputX = 1;
            break;
        case SDLK_SPACE:
            character->fire();
            break;
        }
    }

    if (event->type == SDL_KEYUP) {
        switch (event->key.keysym.sym) {
        case SDLK_w:
        case SDLK_s:
            playerInputY = 0;
            break;
        case SDLK_a:
        case SDLK_d:
            playerInputX = 0;
            break;
        }
    }

    character->move(playerInputX, playerInputY);
    // }
}
