#include "Character.h"


Character::Character(std::string texture, Coordinate position)
{
    size.x = 10;
    size.y = 10;

    origin.x = position.x - (size.x / 2);
    origin.y = position.y - (size.y / 2);

    initGL(texture);
}


Character::~Character()
{
    printf("-- character destructor\n");
    glDeleteProgram(shaderProgram);

    glDeleteBuffers(1, &ebo);
    glDeleteBuffers(1, &vbo);
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
    Game::getInstance().removePoints();
    Sound::getInstance()->play("hit");
}


void
Character::initGL(std::string texture)
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    // set up the shader program
    shaderProgram = createProgramFromShaders("src/shaders/texturedSquare.v.glsl",
					     "src/shaders/texturedSquare.f.glsl");

    glUseProgram(shaderProgram);

    glGenTextures(1, &tex);
    loadTexture(tex, texture);

    // describe how vertex buffer object maps to
    // link vertex array to position attribute
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(posAttrib);

    // texture position
    GLint texAttrib = glGetAttribLocation(shaderProgram, "texcoord");
    glEnableVertexAttribArray(texAttrib);
    // the texcoords are tightly packed after the verticies in the array
    glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 0, (void*)(8 * sizeof(float)));

    // translation attr from vector shader
    uniTrans = glGetUniformLocation(shaderProgram, "trans");
    glm::mat4 trans;
    trans = glm::translate(trans, glm::vec3(0.0f, 0.0f, 1.0f));
    glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));
    // --- END setup shader programs --- //

    // --- temporarily added
    // color attr from fragment shader
    uniColor = glGetUniformLocation(shaderProgram, "color");

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


    glBindVertexArray(0);
    glUseProgram(0);
}


void
Character::move(unsigned char direction)
{
    int newX = origin.x;
    int newY = origin.y;
    int movementSize = CHARACTER_MOVE_SIZE;

    // calculate new coords
    if (direction == 'u') {
        newY += movementSize;
    }
    else if (direction == 'd') {
        newY -= movementSize;
    }
    else if (direction == 'l') {
        newX -= movementSize;
    }
    else if (direction == 'r') {
        newX += movementSize;
    }

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

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glUniform3f(uniColor, 0.0f, 1.0f, 0.0f);

    // transform coords based on screenPos of character
    glm::mat4 trans;
    trans = glm::translate(trans,
                           glm::vec3((SCALE_X * (float) origin.x),
                                     (SCALE_Y * (float) origin.y),
                                     1.0f));
    glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));

    // --- this may go back in the main loop and only get called once
    // draw a rectangle from 2 triangles
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
    glUseProgram(0);
}

