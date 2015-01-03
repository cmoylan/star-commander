#include "Enemy.h"


Enemy::Enemy(Coordinate position)
{
    // TODO: default to center if no position specified

    size.x = 10;
    size.y = 10;

    origin.x = position.x - (size.x / 2);
    origin.y = position.y - (size.y / 2);

    initGL();
}


Enemy::~Enemy()
{
    glDeleteProgram(shaderProgram);

    glDeleteBuffers(1, &ebo);
    glDeleteBuffers(1, &vbo);
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
    printf("enemy was hit at: [%d, %d]\n", origin);
    // add 1 to score
    Game::getInstance().addPoints();
    Sound::getInstance()->play("hit");
}


void
Enemy::initGL()
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    std::vector<GLuint> shaderList;
    shaderList.push_back(createShader(GL_VERTEX_SHADER, "src/bulletVertexShader.glsl"));
    shaderList.push_back(createShader(GL_FRAGMENT_SHADER, "src/bulletFragmentShader.glsl"));

    shaderProgram = createProgram(shaderList);
    std::for_each(shaderList.begin(), shaderList.end(), glDeleteShader);

    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(posAttrib);

    // translation attr from vector shader
    uniTrans = glGetUniformLocation(shaderProgram, "trans");

    // color attr from fragment shader
    uniColor = glGetUniformLocation(shaderProgram, "color");
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
    GLuint elements[] = {
        0, 1, 2,
        2, 3, 0
    };

    GLfloat vertices[] = {
        0.0f, 0.0f, // top left
        (SCALE_X * (float) size.x), 0.0f, // top right
        (SCALE_X * (float) size.x), -(SCALE_Y * (float) size.y),  //bottom right
        0.0f, -(SCALE_Y * (float) size.y) // bottom left
    };

    glUseProgram(shaderProgram);

    glUniform3f(uniColor, 1.0f, 1.0f, 0.0f);
    //printf("vertex array: ");
    //for (GLfloat vertex : vertices) {
    //  printf("[%f]->", vertex);
    //}
    //printf("\n");

    // transform coords based on origin of enemy
    glm::mat4 trans;
    trans = glm::translate(trans,
                           glm::vec3((SCALE_X * (float) origin.x),
                                     (SCALE_Y * (float) origin.y),
                                     1.0f));
    //printf("transform x: [%f]\n", (0.01f * (float) origin.x));
    //printf("transform y: [%f]\n", (0.01f * (float) origin.y));
    glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

