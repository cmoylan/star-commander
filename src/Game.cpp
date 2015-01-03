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
Game::resetScore()
{
    score = 0;
}
