#include "Level.h"


/*
 * When we create the level we should instantiate wall classes for each
 * section of the wall. We should keep a list to instances of the
 * wall classes and any time the wall is identical, we should reuse
 * a pointer.
 */

Level::Level()
{
    // initialize camera to the middle of the level:
    cameraX = LEVEL_WIDTH / 2;
    cameraY = LEVEL_HEIGHT / 2;

    printf("initializing level camera to: %d, %d\n", cameraX, cameraY);

    initTexture();
    printf("texture initialized\n");
}


Level::~Level()
{
}


void
Level::centerOn(int x, int y)
{
    centerOnX(x);
    centerOnY(y);
}


void
Level::centerOnX(int x)
{
    int levelBufferX = LEVEL_WIDTH / 2;
    // TODO: macroize?
    if ((x - levelBufferX >= 0) &&
            (x < (width() - levelBufferX))) {
        cameraX = x;
    }
}


void
Level::centerOnY(int y)
{
    int levelBufferY = LEVEL_HEIGHT / 2;

    // Only move the camera if we're past the level buffer. This way the edge of the
    // level sticks to the edge of the screen.
    if ((y - levelBufferY >= 0) &&
            (y < (height() - levelBufferY))) {
        cameraY = y;
    }
}


int
Level::height()
{
    return levelMatrix.size();
}


bool
Level::isCentered(int x, int y)
{
    return isCenteredX(x) && isCenteredY(y);
}


bool
Level::isCenteredX(int x)
{
    // TODO: store these on the class, update on level load
    int minCenterX = LEVEL_WIDTH / 2;
    int maxCenterX = width() - minCenterX;

    if (x > minCenterX && x < maxCenterX) {
        return true;
    }
    else {
        return false;
    }
}


bool
Level::isCenteredY(int y)
{
    int minCenterY = LEVEL_HEIGHT / 2;
    //int maxCenterY = (LEVEL_ARRAY_SIZE_Y - minCenterY) - 1; // account for 0-indexed array
    int maxCenterY = height() - minCenterY;

    if (y > minCenterY && y < maxCenterY) {
        return true;
    }
    else {
        return false;
    }
}


bool
Level::isClear(int x, int y)
{
    if (levelMatrix[y][x] == 0) {
        return true;
    }
    else {
        return false;
    }
}


bool
Level::loadFromFile(std::string path)
{
    int x, y, width, height;

    cimg_library::CImg<int> image(path.c_str());
    width = image.width();
    height = image.height();

    // resize levelMatrix
    levelMatrix.resize(height);

    for (y = 0; y < height; y++) {
        levelMatrix[y].resize(width);

        for (x = 0; x < width; x++) {
            // if there is a wall
            // TODO: replace with constant
            if (image(x, y) == 255) {
                levelMatrix[y][x] = 1;
            }
            // empty space
            else {
                levelMatrix[y][x] = 0;
            }
            //printf("[%d, %d]: %d\n", x, y, image(y, x));
        }
    }

//  for (y = 0; y < levelMatrix.size(); y++) {
//    for (x = 0; x < levelMatrix[y].size(); x++) {
//      printf("[%d, %d]: %d\n", x, y, levelMatrix[y][x]);
//    }
//  }

    // TODO: more error handling
    return true;
}


void
Level::print()
{
    // TODO: macro-ize
    int x, y;

    printf("Current structure of level is:\n");

    for (y = 0; y < height(); y++) {
        printf("[");
        for (x = 0; x < width(); x++) {
            if (levelMatrix[y][x] == 1) {
                printf("*");
            }
            else {
                printf(" ");
            }
        }
        printf("]\n");
    }

}


inline void
printRenderingPoints(int x, int y)
{
    printf("  ---rendering points: \n");
    printf("     [%f, %f]\n", x * BOX_WIDTH, y * BOX_HEIGHT);
    printf("     [%f, %f]\n", (x + 1)*BOX_WIDTH, y * BOX_HEIGHT);
    printf("     [%f, %f]\n", (x + 1)*BOX_WIDTH, (y + 1)*BOX_HEIGHT);
    printf("     [%f, %f]\n", x * BOX_WIDTH, (y + 1)*BOX_HEIGHT);
}


void
Level::render()
{
    int levelX, levelY, boxX, boxY;
    boxX = 0;
    boxY = 0;

    //printf("--- render cycle ---\n");
    //printf("camera x and y are: %d, %d\n", cameraX, cameraY);

    // LEVEL_WIDTH/HEIGHT in this case will need to be level[].length and level[][].length
    levelY = cameraY - (LEVEL_HEIGHT / 2);

    //printf("levelx is: %d\n", levelX);
    for (; levelY <= cameraY + (LEVEL_HEIGHT / 2); levelY++) {
        //printf("inside Y loop, levelY is %d\n", levelY);

        // reset looping vars for next iteration
        levelX = cameraX - (LEVEL_WIDTH / 2);
        boxX = 0;

        for (; levelX <= cameraX + (LEVEL_WIDTH / 2); levelX++) {
            //printf("inside X loop, x is %d\n", x);
            // This rendering will happen inside wall classes, instances of which will be
            // pointed to by each position in the level matrix.
            // if there is a wall

            if (levelMatrix[levelY][levelX] == 1) {

                glEnable(GL_TEXTURE_2D);
                //glColor3f(1.0f, 1.0f, 1.0f);
                glColor3f(1.0f, 1.0f, 1.0f); // reset gl color
                // this is supposed to use the texture's color regardless of glColor
                //glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

                // bind the wall texture
                glBindTexture(GL_TEXTURE_2D, 13);

                // draw a square
                glBegin(GL_QUADS);

                //printf("boxX and boxY are: %d, %d\n", boxX, boxY);
                glTexCoord2f(0.0, 0.0);
                glVertex2f(boxX * BOX_WIDTH, boxY * BOX_HEIGHT); // upper left

                glTexCoord2f(1.0, 0.0);
                glVertex2f((boxX + 1) * BOX_WIDTH, boxY * BOX_HEIGHT); //upper right

                glTexCoord2f(1.0, 1.0);
                glVertex2f((boxX + 1) * BOX_WIDTH, (boxY + 1) * BOX_HEIGHT); // lower right

                glTexCoord2f(0.0, 1.0);
                glVertex2f(boxX * BOX_WIDTH, (boxY + 1) * BOX_HEIGHT); // lower left

                glEnd();

                // remove the texture from the opengl state machine
                glBindTexture(GL_TEXTURE_2D, NULL);

                glDisable(GL_TEXTURE_2D);
            }

            boxX++;
        }
        boxY++;
    }
}


int
Level::width()
{
    // Assuming level is  square. This could change.
    // TODO: Loop over all rows of the level and find the largest one.
    return levelMatrix[0].size();
}


void
Level::initTexture()
{
    glBindTexture(GL_TEXTURE_2D, 13);

    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    //glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    //glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
    //		   GL_LINEAR_MIPMAP_NEAREST );


    //cimg_library::CImg<int> image("bricks.jpg");
    cimg_library::CImg<int> image("texture.png");

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                 image.width(), image.height(),
                 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data());

    glGenerateMipmap(GL_TEXTURE_2D);
    // the texture wraps over at the edges (repeat)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // when texture area is small, bilinear filter the closest mipmap
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // when texture area is large, bilinear filter the original
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // check for error
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        printf("Error initializing texture: %s\n", gluErrorString(error));
    }

    glBindTexture(GL_TEXTURE_2D, NULL);
}
