#include "Menu.h"

Menu::Menu()
{
    showing = false;
}


Menu::~Menu()
{
}


void
Menu::render()
{
    // color of the font
    GLfloat green[4] = {0, 1, 0, 1};
    GLfloat red[4] = { 1, 0, 0, 1 };

    float sx = 2.0f / WINDOW_WIDTH;
    float sy = 2.0f / WINDOW_HEIGHT;

    //FT_Set_Pixel_Sizes(face, 0, 32);
    TextRenderer::getInstance()->renderText("Press Q to quit, Esc to resume.",
               -1 + 250 * sx,   1 - 400 * sy,    
	       sx, sy, 
	       green, 32);
    //renderText("The Quick Brown Fox Jumps Over The Lazy Dog", font48, -1 + 8 * sx, 1 - 50 * sy, sx, sy);

}


void
Menu::toggle()
{
    showing = !showing;
}
