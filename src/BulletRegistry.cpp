#include "BulletRegistry.h"


BulletRegistry::BulletRegistry()
{
    initGL();
}


void
BulletRegistry::add(Rectangle firingElement, Heading heading)
{
    Vector2D bulletOrigin;
    Rectangle element;
    Bullet bullet;
    //Vector2D bulletSize = { BULLET_WIDTH, BULLET_HEIGHT };

    // TODO: this can be refactored
    // -- X axis movement ---
    if (heading.x == 1) {
        // going right
        bulletOrigin.x = firingElement.origin.x + firingElement.size.x;
    }
    else if (heading.x == -1) {
        // going left
        bulletOrigin.x = firingElement.origin.x - firingElement.size.x;
    }
    else {
        // not moving
        bulletOrigin.x =
            firingElement.origin.x +
            ((firingElement.size.x / 2) - (BULLET_WIDTH / 2));
    }

    // --- Y axis movement
    if (heading.y == 1) {
        // going up
        bulletOrigin.y = firingElement.origin.y + firingElement.size.y;
    }
    else if (heading.y == -1) {
        // going down
        bulletOrigin.y = firingElement.origin.y - firingElement.size.y;
    }
    else {
        // not moving - set to half
        bulletOrigin.y =
            firingElement.origin.y +
            ((firingElement.size.y / 2) - (BULLET_HEIGHT / 2));
    }

    //printf("bullet fired from element: origin: [%d, %d] size: [%d, %d]\n",firingElement.origin, firingElement.size);
    //printf("bullet element is: origin: [%d, %d]\n", bulletOrigin);

    // build element
    element.origin = bulletOrigin;
    element.size.x = BULLET_WIDTH;
    element.size.y = BULLET_HEIGHT;

    // assemble bullet
    bullet.element = element;
    bullet.heading = heading;
    bullet.speed = 5;

    bullet.removed = false;

    bullets.push_back(bullet);

    //printf("bullet fired\n");
}


void
BulletRegistry::flush()
{
    std::vector<Bullet>::iterator bullet;

    for (bullet = bullets.begin(); bullet != bullets.end();) {
        if (bullet->removed) {
            remove(bullet);
        }
        else {
            ++bullet;
        }

    }
}


void
BulletRegistry::initGL()
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    shaderProgram = createProgramFromShaders("src/shaders/square.v.glsl",
					     "src/shaders/square.f.glsl");

    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(posAttrib);

    // translation attr from vector shader
    uniTrans = glGetUniformLocation(shaderProgram, "trans");

    // color attr from fragment shader
    uniColor = glGetUniformLocation(shaderProgram, "color");
}


void
BulletRegistry::print()
{
    std::vector<Bullet>::iterator bullet;
    int i;

    for (bullet = bullets.begin(), i = 0; bullet != bullets.end(); ++bullet, i++) {
        printf("bullet #%d (x, y): [%d, %d]\n", i, bullet->element.origin);
    }

}


std::vector<Bullet>::iterator
BulletRegistry::remove(std::vector<Bullet>::iterator position)
{
    //printf("erasing bullet\n");
    return bullets.erase(position);
}


void
BulletRegistry::render()
{
    if (bullets.size() == 0) {
        return;
    }

    std::vector<Bullet>::iterator bullet;

    // iterator
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


    for (bullet = bullets.begin(); bullet != bullets.end(); bullet++) {
        //printf("rendering at: [%d, %d]\n", bullet->element.origin);
        glUseProgram(shaderProgram);

        glUniform3f(uniColor, 1.0f, 0.0f, 0.0f);

        glm::mat4 trans;
        trans = glm::translate(trans,
                               glm::vec3((SCALE_X * (float) bullet->element.origin.x),
                                         (SCALE_Y * (float) bullet->element.origin.y),
                                         0.1f));
        glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // --- this may go back in the main loop and only get called once
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
}


void
BulletRegistry::tick()
{
    std::vector<Bullet>::iterator bullet;

    for (bullet = bullets.begin(); bullet != bullets.end();) {
        // move
        bullet->element.origin.x += bullet->heading.x * bullet->speed;
        bullet->element.origin.y += bullet->heading.y * bullet->speed;

        //printf("bullet x, y: %f, %f\n", bullet->location.x, bullet->location.y);

        // If the bullet is out of bounds, remove it
        if ((bullet->element.origin.x > SCREEN_X)
                || (bullet->element.origin.y > SCREEN_Y)) {
            bullet = remove(bullet);
        }
        else {
            ++bullet;
        }
    }
}
