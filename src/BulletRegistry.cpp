#include "BulletRegistry.h"


BulletRegistry::BulletRegistry()
{
  initGL();
}


void
BulletRegistry::add(float x, float y, int headingX, int headingY)
{
  coordinate_t location;
  heading_t heading;
  bullet_t bullet;

  location.x = x;
  location.y = y;

  heading.x = headingX;
  heading.y = headingY;

  bullet.location = location;
  bullet.heading = heading;
  bullet.speed = 0.1;

  bullets.push_back(bullet);

  printf("bullet fired\n");
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
  std::vector<bullet_t>::iterator bullet;
  int i;

  for (bullet = bullets.begin(), i=0; bullet != bullets.end(); ++bullet, i++) {
    printf("bullet #%d (x, y): %f, %f\n", i, bullet->location.x, bullet->location.y);
  }

}


std::vector<bullet_t>::iterator
BulletRegistry::remove(std::vector<bullet_t>::iterator position)
{
  printf("erasing bullet\n");
  return bullets.erase(position);
}


void
BulletRegistry::render()
{
  if (bullets.size() == 0) {
    return;
  }
  
  std::vector<bullet_t>::iterator bullet;

  // iterator
  GLint elements[] = {
    0, 1, 2,
    2, 3, 0
  };

  GLfloat vertices[] = {
    // Position
    -0.1f, 0.1f,
    0.1f, 0.1f,
    0.1f, -0.1f,
    -0.1f, -0.1f
  };

  for (bullet = bullets.begin(); bullet != bullets.end(); bullet++) {
    glUseProgram(shaderProgram);

    glUniform3f(uniColor, 1.0f, 0.0f, 0.0f);

    glm::mat4 trans;
    trans = glm::translate(trans,
			  glm::vec3(bullet->location.x,
				    bullet->location.y, 0.1f));
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
  std::vector<bullet_t>::iterator bullet;

  for (bullet = bullets.begin(); bullet != bullets.end(); ) {
    // move
    bullet->location.x += bullet->heading.x * bullet->speed;
    bullet->location.y += bullet->heading.y * bullet->speed;

    printf("bullet x, y: %f, %f\n", bullet->location.x, bullet->location.y);

    // If the bullet is out of bounds, remove it
    if ((bullet->location.x > 1.0f) || (bullet->location.y > 1.0f)){
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
