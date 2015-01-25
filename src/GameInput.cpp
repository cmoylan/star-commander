#include "Game.h"

void
Game::handleInput(SDL_Event* event)
{
    switch (event->type) {
    case SDL_QUIT:
        running = false;
        break;
    case SDL_KEYDOWN:
        handleKeyDown(event);
        break;
    case SDL_KEYUP:
        handleKeyUp(event);
        break;
    }
}


void
Game::handleKeyDown(SDL_Event* event)
{
    // TODO: allow keys to be remapped
    switch (event->key.keysym.sym) {
    case SDLK_ESCAPE:
        running = false;
        break;
    case SDLK_w:
        playerInputY = INPUT_WEIGHT_Y;
        break;
    case SDLK_a:
        playerInputX = -INPUT_WEIGHT_X;
        break;
    case SDLK_s:
        playerInputY = -INPUT_WEIGHT_Y;
        break;
    case SDLK_d:
        playerInputX = INPUT_WEIGHT_X;
        break;
    case SDLK_SPACE:
        character->fire();
        break;
    case SDLK_p:
        paused = !paused;
        break;
    }
}


void
Game::handleKeyUp(SDL_Event* event)
{
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