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
      ((firingElement.size.x / 2.0f) - (BULLET_WIDTH / 2.0f));
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
      ((firingElement.size.y / 2.0f) - (BULLET_HEIGHT / 2.0f));
  }

  // build element
  element.origin = bulletOrigin;

  // assemble bullet
  bullet.element = element;
  bullet.heading = heading;
  bullet.speed = 0.1f;

  bullets.push_back(bullet);

  //printf("bullet fired\n");
}


void
BulletRegistry::initGL()
{
  glGenVertexArrays(1, &vao);
  //glBindVertexArray(vao);
  glGenBuffers(1, &vbo);
  //glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glGenBuffers(1, &ebo);
  //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

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
BulletRegistry::print()
{
  std::vector<Bullet>::iterator bullet;
  int i;

  for (bullet = bullets.begin(), i = 0; bullet != bullets.end(); ++bullet, i++) {
    printf("bullet #%d (x, y): %f, %f\n", i, bullet->element.origin.x, bullet->element.origin.y);
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
  if (bullets.size() == 0) { return; }

  std::vector<Bullet>::iterator bullet;

  // iterator
  GLint elements[] = {
    0, 1, 2,
    2, 3, 0
  };

  GLfloat vertices[] = {
    // Position
    0, BULLET_WIDTH,
    BULLET_HEIGHT, BULLET_WIDTH,
    BULLET_HEIGHT, 0,
    0, 0
  };

  for (bullet = bullets.begin(); bullet != bullets.end(); bullet++) {
    glUseProgram(shaderProgram);

    glUniform3f(uniColor, 1.0f, 0.0f, 0.0f);

    glm::mat4 trans;
    trans = glm::translate(trans,
                           glm::vec3(bullet->element.origin.x,
                                     bullet->element.origin.y, 0.1f));
    glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // --- this may go back in the main loop and only get called once
    // draw a rectangle from 2 triangles
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
    if ((bullet->element.origin.x > 1.0f)
	|| (bullet->element.origin.y > 1.0f)) {
      bullet = remove(bullet);
    }
    // If the bullet has collided with something, handle it
    // else if (collision(bullet)) {
    //   handle_collision(bullet);
    // }
    // Otherwise, go to the next bullet
    else {
      ++bullet;
    }
  }
}
