#include "Background.h"

Background::Background()
{

    // this should be coded to 0, no need to use origin and size
    origin.x = -SCREEN_X;
    origin.y = -SCREEN_Y;
    size.x = SCREEN_X * 2;
    size.y = SCREEN_Y * 2;
    //printf(

    initGL("res/background.png");
}


Background::~Background()
{

}


void
Background::render()
{
    glUseProgram(shaderProgram);
    glBindVertexArray(vao);
    glBindTexture(GL_TEXTURE_2D, tex);

    glm::mat4 trans;
    trans = glm::translate(trans, glm::vec3(0, 0, 1.0f));
    glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    resetGlState();
}