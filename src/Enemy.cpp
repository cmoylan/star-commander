#include "Enemy.h"


Enemy::Enemy(std::string texture, Coordinate position)
{
    // TODO: default to center if no position specified
    size.x = 20;
    size.y = 20;

    origin.x = position.x - (size.x / 2);
    origin.y = position.y - (size.y / 2);

    initGL(texture);
}


Enemy::~Enemy()
{
    glDeleteProgram(shaderProgram);
    glDeleteVertexArrays(1, &vao);
}


int
Enemy::edgeBottom()
{
    return origin.y;
}


int
Enemy::edgeLeft()
{
    return origin.x;
}


int
Enemy::edgeRight()
{
    return origin.x + size.x;
}


int
Enemy::edgeTop()
{
    return origin.y + size.y;
}


void
Enemy::fire()
{
    // Add a bullet moving down
    //BulletRegistry::getInstance().add(screenPos.x, screenPos.y, 0, -1);
    Heading heading = { 0, -1 };
    Rectangle element = { origin, size };

    BulletRegistry::getInstance().add(element, heading);
    Sound::getInstance()->play("enemy-laser");
}


void
Enemy::hit()
{
    printf("enemy was hit at: [%d, %d]\n", origin.x, origin.y);
    // add 1 to score
    Game::getInstance().addPoints();
    Sound::getInstance()->play("hit");
}


void
Enemy::initGL(std::string texture)
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    // texture
    glGenTextures(1, &tex);
    loadTexture(tex, texture);

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
    uniTrans = glGetUniformLocation(shaderProgram, "trans");


    GLuint elements[] = {
        0, 1, 2,
        2, 3, 0
    };

    GLfloat vertices[] = {
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

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    resetGlState();
}


void
Enemy::move(int x, int y)
{
    int newX = origin.x;
    int newY = origin.y;
    int movementSize = 5; // TODO: move?

    newX += (x * movementSize);
    newY += (y * movementSize);

    if ((newX >= -SCREEN_X) && ((newX + size.x) <= SCREEN_X)) {
        origin.x = newX;
    }
    if ((newY >= -SCREEN_Y) && ((newY + size.y) <= SCREEN_Y)) {
        origin.y = newY;
    }
    //printf("moved to %f, %f\n", newX, newY);
}


void
Enemy::render()
{
    glUseProgram(shaderProgram);
    glBindVertexArray(vao);
    glBindTexture(GL_TEXTURE_2D, tex);

    // transform coords based on origin of enemy
    glm::mat4 trans;
    trans = glm::translate(trans,
                           glm::vec3((SCALE_X * (float) origin.x),
                                     (SCALE_Y * (float) origin.y),
                                     1.0f));
    glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    resetGlState();
}

