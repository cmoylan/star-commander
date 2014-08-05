#include "Character.h"


Character::Character(std::string texture, coordinate_t startingPos)
{
  // initialize attributes
  height = 10;
  width = 10;

  //screenPos.x = 0;
  //screenPos.y = 0;
  screenPos = startingPos;

  // --- set up the vao and vbo --- //
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  // call bindVertexArray in render

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  // call glBindBuffer in the render

  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

  // --- END set up the vao and vbo --- //


  // --- BEGIN texture stuff --- //
  glGenTextures(1, &tex);
  loadTexture(tex, texture);
  // --- END texture stuff --- //


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
  // --- BEGIN Link buffer objects --- //

  // --- END setup shader programs --- //
}


Character::~Character()
{
  glDeleteProgram(shaderProgram);

  glDeleteBuffers(1, &ebo);
  glDeleteBuffers(1, &vbo);
  glDeleteVertexArrays(1, &vao);
}


void
Character::fire()
{
  BulletRegistry::getInstance().add(screenPos.x, screenPos.y, 0, 1);
}


void
Character::move(unsigned char direction)
{
  float newX = screenPos.x;
  float newY = screenPos.y;
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

  //printf("newX and newY are: %f, %f\n", newX, newY);

  if ((newX > -1.0f) && (newX < 1.0)) {
    screenPos.x = newX;
  }
  if ((newY > -1.0f) && (newY < 1.0)) {
    screenPos.y = newY;
  }
  //printf("moved to %f, %f\n", newX, newY);
}


void
computeInitialVertices(GLfloat &vertices)
{

}


void
Character::render()
{
  GLuint elements[] = {
    0, 1, 2,
    2, 3, 0
  };

  // take starting x,y
  // get half height and half width
  int renderHeight = height / 2;
  int renderWidth = width / 2;
  // do this with matrix math??
  // upper right (x, y)
  // (screePos.x - renderWidth), (screenPos.y - renderHeight)
  // lower right
  // (screenPos.x + renderWidth), (screenPos.y + renderHeight)
  // lower left
  // (screenPos.x - renderWidth), (screenPos.y + renderHeight)
  // upper left
  // (screenPos.x + renderWidth), (screenPos.y - renderHeight)

  // y, x
  GLfloat vertices[] = {
    // Position
    -0.1f, 0.1f,
    0.1f, 0.1f,
    0.1f, -0.1f,
    -0.1f, -0.1f,

    // Texcoords
    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 1.0f
  };

  glUseProgram(shaderProgram);

  // transform coords based on screenPos of character
  glm::mat4 trans;
  trans = glm::translate(trans,
			 glm::vec3(screenPos.x, screenPos.y, 1.0f));
  glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));

  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // --- this may go back in the main loop and only get called once
  // draw a rectangle from 2 triangles
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

