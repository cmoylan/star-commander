#include "Enemy.h"


Enemy::Enemy(coordinate_t startingPos)
{
  height = 20;
  width = 20;

  screenPos = startingPos;

  initGL();
}


Enemy::~Enemy()
{
  glDeleteProgram(shaderProgram);

  glDeleteBuffers(1, &ebo);
  glDeleteBuffers(1, &vbo);
  glDeleteVertexArrays(1, &vao);
}


void
Enemy::fire()
{
  // Add a bullet moving down
  BulletRegistry::getInstance().add(screenPos.x, screenPos.y, 0, -1);
}


void
Enemy::initGL()
{
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);

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
  float newX = screenPos.x;
  float newY = screenPos.y;
  float movementSize = 0.1f;

  newX += (x * movementSize);
  newY += (y * movementSize);

  if ((newX > -1.0f) && (newX < 1.0)) {
    screenPos.x = newX;
  }
  if ((newY > -1.0f) && (newY < 1.0)) {
    screenPos.y = newY;
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

  // take starting x,y
  // get half height and half width
  int renderHeight = height / 2;
  int renderWidth = width / 2;

  // y, x
  GLfloat vertices[] = {
    0.0f, 0.0f, // top left
    0.0f, (0.1f * (float) renderWidth),  // top right
    (0.1f * (float)renderHeight), (0.1f * (float)renderWidth), //bottom right
    (0.1f * (float)renderHeight), -0.0f // bottom left
  };

  glUseProgram(shaderProgram);

  glUniform3f(uniColor, 1.0f, 1.0f, 0.0f);

  // transform coords based on screenPos of enemy
  glm::mat4 trans;
  trans = glm::translate(trans,
                         glm::vec3(screenPos.x,
                                   screenPos.y,
                                   1.0f));
  glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));

  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

