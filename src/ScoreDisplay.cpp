#include "ScoreDisplay.h"

ScoreDisplay::ScoreDisplay()
{
    // load font
    font = TTF_OpenFont("res/FreeMonoBold.ttf", 16);

    printf("1\n");
    initGL();
    printf("2\n");

    glGenTextures(1, &tex);
    loadTexture(tex, "res/enemy.png");
}


ScoreDisplay::~ScoreDisplay()
{
    TTF_CloseFont(font);
}


void
ScoreDisplay::initGL()
{
    printf("workee?");
    // passed in
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    shaderProgram = createProgramFromShaders("src/shaders/texturedSquare.v.glsl",
                                             "src/shaders/texturedSquare.v.glsl");
    glUseProgram(shaderProgram);

    GLint texAttrib = glGetAttribLocation(shaderProgram, "texcoord");
    glEnableVertexAttribArray(texAttrib);
    glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 0, (void*)(8 * sizeof(float)));

    GLuint elements[] = {
        0, 1, 2,
        2, 3, 0
    };

    GLfloat vertices[] = {
        -1.0f, -1.0f, // top left
        1.0f, -1.0f, // top right
        -1.0f, (SCALE_Y * (float) (SCREEN_Y - SCORE_HEIGHT)),  //bottom right
        1.0f, (SCALE_Y * (float) (SCREEN_Y - SCORE_HEIGHT)), // bottom left

        // Texcoords
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f
    };

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    resetGlState();
}


void
ScoreDisplay::render()
{
    glUseProgram(shaderProgram);
    glBindVertexArray(vao);
    glBindTexture(GL_TEXTURE_2D, tex);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    resetGlState();
}
