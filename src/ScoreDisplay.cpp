#include "ScoreDisplay.h"

ScoreDisplay::ScoreDisplay()
{
    // load font
    font = TTF_OpenFont("res/FreeMonoBold.ttf", 16);

    initGL();
    setScore(0);
}


ScoreDisplay::~ScoreDisplay()
{
    TTF_CloseFont(font);
}


void
ScoreDisplay::initGL()
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    // generated here, set elsewhere
    glGenTextures(1, &tex);

    shaderProgram = createProgramFromShaders("src/shaders/texturedSquare.v.glsl",
                                             "src/shaders/texturedSquare.f.glsl");
    glUseProgram(shaderProgram);

    GLint texAttrib = glGetAttribLocation(shaderProgram, "texcoord");
    glEnableVertexAttribArray(texAttrib);
    glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 0, (void*)(8 * sizeof(float)));

    // position offset
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(posAttrib);

    // translation attr from vector shader
    GLint uniTrans = glGetUniformLocation(shaderProgram, "trans");
    //// transform coords based on origin of enemy
    glm::mat4 trans;
    trans = glm::translate(trans, glm::vec3(-1.f, 1.f, 1.f));
    glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));

    GLuint elements[] = {
        0, 1, 2,
        2, 3, 0
    };

    //GLfloat vertices[] = {
    //    //-1.0f, 1.0f, // top left
    //    //1.0f, 1.0f, // top right
    //    //-1.0f, (SCALE_Y * (float) (SCREEN_Y - SCORE_HEIGHT)),  //bottom right
    //    //1.0f, (SCALE_Y * (float) (SCREEN_Y - SCORE_HEIGHT)), // bottom left
    //
    //	-1.f, 1.f,
    //	-0.5f, 1.f,
    //	-1.0f, (SCALE_Y * (float) (SCREEN_Y - SCORE_HEIGHT)),  //bottom right
    //	0.5f, (SCALE_Y * (float) (SCREEN_Y - SCORE_HEIGHT)), // bottom left
    //
    //    // Texcoords
    //    0.0f, 0.0f,
    //    1.f, 0.0f,
    //    1.f, 1.0f,
    //    0.0f, 1.0f
    //};

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

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


void
ScoreDisplay::setScore(int score)
{
    SDL_Surface* surface;
    SDL_Color color = {0,0,0};

    //surface = TTF_RenderUTF8_Blended(font, "Hello World!", color);
    surface = TTF_RenderText_Solid(font, "Hello World!", color);

    glUseProgram(shaderProgram);
    glBindVertexArray(vao);

    GLfloat vertices[] = {
        0.0f, 0.0f, // top left
        (SCALE_X * (float) surface->w), 0.0f, // top right
        (SCALE_X * (float) surface->w), -(SCALE_Y * (float) surface->h),  //bottom right
        0.0f, -(SCALE_Y * (float) surface->h), // bottom left

        // Texcoords
        0.0f, 0.0f,
        1.f, 0.0f,
        1.f, 1.0f,
        0.0f, 1.0f
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    printf("surface w/h: [%d, %d]\n", surface->w, surface->h);
    printf("vertex data: [%f, %f] [%f, %f] [%f, %f] [%f, %f]\n", vertices);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, surface->w, surface->h, 0,
    		 GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);

    //glBindTexture(GL_TEXTURE_2D, 0);
    resetGlState();
    SDL_FreeSurface(surface);
}
