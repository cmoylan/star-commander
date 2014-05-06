#include "Character.h"


Character::Character(Level *level)
{
  currentLevel = level;

  // initialize attributes
  height = 1;
  width = 1;

  levelPosX = 1;
  levelPosY = 1;

  screenPosX = 1;
  screenPosY = 1;
}


Character::~Character()
{
}


void
Character::move(unsigned char direction)
{
  // get direction from util.cpp
  // have current position in x,y
  // depending on string, add or subtract from x or y
  // ask level if we can move to that position
  //
  // rather than keep x,y on character...since character is mostly going to be
  // in the middle of the screen, have level remember x and y. After all,
  // level is going to have to render itself. Character is pretty much
  // always the same.

  // no keep the x,y on the character
  // the character will ask level if it can update it's position
  // level will respond yes or no

  int newX = levelPosX; // second arg
  int newY = levelPosY; // first arg

  // calculate new coords
  if (direction == 'u') {
    newY = newY - 1;
  }
  else if (direction == 'd') {
    newY = newY + 1;
  }
  else if (direction == 'l') {
    newX = newX - 1;
  }
  else if (direction == 'r') {
    newX = newX + 1;
  }

  // GRAVITY
  // check if character is falling
  // if character is falling move down at the speed of gravity
  // allow slowed side-to-side motion while falling
  // if character is not falling move the regular amount

  // if jumping, accellerate upward logarithmically?
  // then begin falling logarithmically to make it look natural
  // allow slowed side-to-side movement while jumping, just like falling
  // maybe slice the jump into N sections and each for each section calculate
  // how much to move. character will move more at beginning and end of jump,
  // and will slow near the middle where they will breifly hover, just like
  // a real jump.


  // first see if there is a collision and do not move
  if (currentLevel->isClear(newX, newY)) {
    //printf("character: moving to: %d, %d\n", newX, newY);

    if (currentLevel->isCenteredY(newY)) {
      screenPosY = (LEVEL_HEIGHT / 2);
    }
    // level character is not centered, update screen position
    else {
      //printf("is not centered Y (inside the IF)\n");

      if (newY <= LEVEL_HEIGHT / 2) {
        //printf("newY <= LEVEL+_HEIGHT/2\n");
        screenPosY = newY;
        //printf("setting screnPoxY to new Y (in the IF -> if)\n");
      }
      else {
        screenPosY = LEVEL_HEIGHT - (currentLevel->height() % newY);
      }
    }
    //printf("screenPosY is: %d\n", screenPosY);
    currentLevel->centerOnY(newY);


    if (currentLevel->isCenteredX(newX)) {
      screenPosX = (LEVEL_WIDTH / 2);
    }
    // if the character is not centered, update screen position
    else {
      // borrowing same logic from Y
      if (newX <= LEVEL_WIDTH / 2) {
        screenPosX = newX;
      }
      else {
        screenPosX = LEVEL_WIDTH - (currentLevel->width() % newX);
        //screenPosX = currentLevel->width() - newX;
      }
    }
    currentLevel->centerOnX(newX);

    // update this as we go
    levelPosY = newY;
    levelPosX = newX;
  }
}


void
Character::render()
{
  glLoadIdentity();

  glBegin(GL_QUADS);
  glColor3f(0.f, 1.f, 0.f);

  //printf("rendering character at: %d, %d\n", screenPosX, screenPosY);

  glVertex2f(screenPosX * BOX_WIDTH, screenPosY * BOX_HEIGHT); // upper left
  glVertex2f((screenPosX + 1) * BOX_WIDTH, screenPosY * BOX_HEIGHT); // upper left
  glVertex2f((screenPosX + 1) * BOX_WIDTH, (screenPosY + 1) * BOX_HEIGHT); // upper left
  glVertex2f(screenPosX * BOX_WIDTH, (screenPosY + 1) * BOX_HEIGHT); // upper left

  glEnd();
}

