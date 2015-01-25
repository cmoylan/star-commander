#include "Background.h"

Background::Background()
{
    origin.x = -SCREEN_X;
    origin.y = -SCREEN_Y;

    size.x = SCREEN_X * 2;
    size.y = SCREEN_Y * 2;

    offset.x = -SCREEN_X;
    offset.y = -SCREEN_Y;

    initGL("res/background.png");
}


Background::~Background()
{

}


void
Background::render()
{
    glm::mat4 trans1, trans2;

    glUseProgram(shaderProgram);
    glBindVertexArray(vao);
    glBindTexture(GL_TEXTURE_2D, tex);

    // Draw the first background tile
    trans1 = glm::translate(trans1,
                            glm::vec3((SCALE_X * (float) offset.x),
                                      (SCALE_Y * (float) offset.y),
                                      1.f));
    glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans1));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // Draw the second background tile
    // TODO: figure out x offset
    trans2 = glm::translate(trans2,
                            glm::vec3((SCALE_X * (float) offset.x),
                                      (SCALE_Y * (float)(offset.y + size.y)),
                                      1.f));
    glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans2));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    resetGlState();
}


void
Background::tick(int ticks)
{
    if (offset.y > -(SCREEN_Y + size.y)) {
        offset.y -= 1;
    }
    else {
        offset.y = -SCREEN_Y;
    }
}