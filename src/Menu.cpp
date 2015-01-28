#include "Menu.h"

Menu::Menu()
{
}


Menu::~Menu()
{
}



void
Menu::initGL()
{
    Util::createAndBindContext(&vao);

    shaderProgram = Util::createProgramFromShaders("src/shaders/square.v.glsl",
                    "src/shaders/square.f.glsl");

    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(posAttrib);

    // color attr from fragment shader
    uniColor = glGetUniformLocation(shaderProgram, "color");

    // from render
    GLint elements[] = {
        0, 1, 2,
        2, 3, 0
    };

    GLfloat vertices[] = {
        0.0f, 0.0f, // top left
        (SCALE_X * (float) BULLET_WIDTH), 0.0f, // top right
        (SCALE_X * (float) BULLET_WIDTH), -(SCALE_Y * (float) BULLET_HEIGHT),  //bottom right
        0.0f, -(SCALE_Y * (float) BULLET_HEIGHT) // bottom left
    };

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements,
                 GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(0);
    glUseProgram(0);
}


void
Menu::render()
{
    // add a black, translucent overlay to screen
    // display buttons - centered

    // go through each button
    // if it is selected change the background or color
    // if it is not selected just draw it

    // probably make textures for the text
    // calculate width of menu, and center it
    // may need a texture loader
}
