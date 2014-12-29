#include "Character.h"


Character::Character(std::string texture, Coordinate startingPos)
{
  // initialize attributes
  height = 10;
  width = 10;

  size = { 0.2, 0.2 };

  // convert starting pos to vector
  origin = {
    startingPos.x - size.x,
    startingPos.y - size.y
  };

  //printf("origin is: %f, %f\n", origin.x, origin.y);
  initGL(texture);
}


Character::~Character()
{
  glDeleteProgram(shaderProgram);

  glDeleteBuffers(1, &ebo);
  glDeleteBuffers(1, &vbo);
  glDeleteVertexArrays(1, &vao);
}


void
Character::center()
{
  origin.x = -(size.x / 2.0f);
  origin.y = -(size.y / 2.0f);
}


void
Character::fire()
{
  Heading heading = { 0, 1 };
  Rectangle element = { origin, size };

  BulletRegistry::getInstance().add(element, heading);
}


void
Character::initGL(std::string texture)
{
  // apparently the bind calls are needed here
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

  // --- set up the shader programs --- //
  std::vector<GLuint> shaderList;
  shaderList.push_back(createShader(GL_VERTEX_SHADER, "src/characterVertexShader.glsl"));
  shaderList.push_back(createShader(GL_FRAGMENT_SHADER, "src/characterFragmentShader.glsl"));

  // combine vertex and fragment shaders into a program
  shaderProgram = createProgram(shaderList);
  std::for_each(shaderList.begin(), shaderList.end(), glDeleteShader);

  // --- BEGIN Link buffer objects --- //

  // i think programs are compiled nd then you 'use' one and any
  // vertex data you send goes to whichever program you're 'using'.
  // need to do this for the lines below
  glUseProgram(shaderProgram);

  // --- BEGIN texture stuff --- //
  glGenTextures(1, &tex);
  loadTexture(tex, texture);
  // --- END texture stuff --- //

  // describe how vertex buffer object maps to
  // link vertex array to position attribute
  GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
  glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(posAttrib);

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

}


void
Character::move(unsigned char direction)
{
  float newX = origin.x;
  float newY = origin.y;
  float movementSize = 0.1f;

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

  //printf("tring to move to: [%f, %f]\n", newX, newY);
  // TODO: wat?
  if ((newX > -1.1f) && (newX <= (1.1f - size.x))) {
    origin.x = newX;
  }
  if ((newY >= -1.1f) && (newY <= (1.1f - size.y))) {
    origin.y = newY;
  }
  //printf("moved to: [%f, %f]\n", newX, newY);
}


void
Character::render()
{
  //printf("origin is: [%f, %f]\n", origin.x, origin.y);

  GLuint elements[] = {
    0, 1, 2,
    2, 3, 0
  };

  // y, x
  GLfloat vertices[] = {
    // Position
    0, size.y,      // upper left
    size.x, size.y, // upper right
    size.x, 0,      // lower right
    0, 0,           // lower left

    // Texcoords
    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 1.0f
  };

  glUseProgram(shaderProgram);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // transform coords based on screenPos of character
  glm::mat4 trans;
  trans = glm::translate(trans,
                         glm::vec3(origin.x, origin.y, 1.0f));
  glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));

  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // --- this may go back in the main loop and only get called once
  // draw a rectangle from 2 triangles
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

