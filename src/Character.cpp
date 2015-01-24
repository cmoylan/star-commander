#include "Character.h"


Character::Character(std::string texture, Coordinate position)
{
    size.x = 20;
    size.y = 20;

    origin.x = position.x - (size.x / 2);
    origin.y = position.y - (size.y / 2);

    initGL(texture);
}


Character::~Character()
{
    printf("-- character destructor\n");
    glDeleteProgram(shaderProgram);
    glDeleteVertexArrays(1, &vao);
}


void
Character::center()
{
    origin.x = -(size.x / 2);
    origin.y = -(size.y / 2);
}


void
Character::fire()
{
    Heading heading = { 0, 1 };
    Rectangle element = { origin, size };

    BulletRegistry::getInstance().add(element, heading);
    Sound::getInstance()->play("laser");
}


void
Character::hit()
{
    printf("character was hit at: [%d, %d]\n", origin);
    // TODO: fix
    //Game::getInstance().removePoints();
    Sound::getInstance()->play("hit");
}


void
Character::initGL(std::string texture)
{
    // --- set up buffers/program
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    glGenTextures(1, &tex);
    loadTexture(tex, texture);

    // set up the shader program
    shaderProgram = createProgramFromShaders("src/shaders/texturedSquare.v.glsl",
                    "src/shaders/texturedSquare.f.glsl");
    glUseProgram(shaderProgram);

    // --- map glsl attributes to pointers
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(posAttrib);

    // texture position
    GLint texAttrib = glGetAttribLocation(shaderProgram, "texcoord");
    glEnableVertexAttribArray(texAttrib);
    // the texcoords are tightly packed after the verticies in the array
    // TODO: you can remove this and go a different route
    glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 0, (void*)(8 * sizeof(float)));

    // translation attr from vector shader
    uniTrans = glGetUniformLocation(shaderProgram, "trans");

    // --- send initial data to the shader
    GLuint elements[] = {
        0, 1, 2,
        2, 3, 0
    };

    GLfloat vertices[] = {
        // Position
        0.0f, 0.0f, // top left
        (SCALE_X * (float) size.x), 0.0f, // top right
        (SCALE_X * (float) size.x), -(SCALE_Y * (float) size.y),  //bottom right
        0.0f, -(SCALE_Y * (float) size.y), // bottom left

        // Texcoords
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f
    };

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements),
                 elements, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    resetGlState();
}


void
Character::move(int x, int y)
{
    int newX = origin.x;
    int newY = origin.y;
    int movementSize = CHARACTER_MOVE_SIZE;

    newX += (x * movementSize);
    newY += (y * movementSize);

    if ((newX >= -SCREEN_X) && ((newX + size.x) <= SCREEN_X)) {
        origin.x = newX;
    }
    if ((newY >= -SCREEN_Y) && ((newY + size.y) <= SCREEN_Y)) {
        origin.y = newY;
    }
}


void
Character::render()
{
    glUseProgram(shaderProgram);
    glBindVertexArray(vao);
    glBindTexture(GL_TEXTURE_2D, tex);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // transform coords based on screenPos of character
    // TODO: precalculate?
    glm::mat4 trans;
    trans = glm::translate(trans,
                           glm::vec3((SCALE_X * (float) origin.x),
                                     (SCALE_Y * (float) origin.y),
                                     1.0f));
    glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));

    // draw a rectangle from 2 triangles
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    resetGlState();
}

