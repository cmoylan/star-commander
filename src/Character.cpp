#include "Character.h"


Character::Character()
{
  // initialize attributes
  height = 1;
  width = 1;

  screenPos.x = 1;
  screenPos.y = 1;

  // --- set up the vao and vbo --- //
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  // call bindVertexArray in render

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  // call glBindBuffer in the render
  // --- END set up the vao and vbo --- //

  // --- set up the shader programs --- //
  GLint status;

  const GLchar* characterVertexSrc =
    "#version 150 core\n"
    "in vec2 position;"
    "void main() {"
    "  gl_Position = vec4(position.x, position.y, 0.0, 1.0);"
    "}";

  const GLchar* characterFragmentSrc =
    "#version 150 core\n"
    "out vec4 outColor;"
    "void main() {"
    "  outColor = vec4(1.0, 0.0, 1.0, 1.0);"
    "}";

  // load and compile the vertex shader code
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &characterVertexSrc, NULL);
  glCompileShader(vertexShader);

  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
  if (status != GL_TRUE) printf("vertex shader did not compile!\n");

  // load and compile the fragment shader code
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &characterFragmentSrc, NULL);
  glCompileShader(fragmentShader);

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
  if (status != GL_TRUE) printf("fragment shader did not compile!\n");

  // combine vertex and fragment shaders into a program
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);

  glLinkProgram(shaderProgram);
  // i think programs are compiled nd then you 'use' one and any
  // vertex data you send goes to whichever program you're 'using'.
  glUseProgram(shaderProgram);

  // describe how vertex buffer object maps to
  // link vertex array to position attribute
  GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
  glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(posAttrib);


  // delete shaders here?
  // --- END setup shader programs --- //

}


Character::~Character()
{
//  glDeleteProgram(shaderProgram);
//  glDeleteShader(fragmentShader);
//  glDeleteShader(vertexShader);
//
//  glDeleteBuffers(1 &vbo);
//  glDeleteVertexArrays(1 &vao);
}


void
Character::move(unsigned char direction)
{

  int newX = screenPos.x;
  int newY = screenPos.y;

  // calculate new coords
  if (direction == 'u') {
    newY = newY - 1;
  }
  else if (direction == 'd') {
    newY = newY + 1;
  }
  else if (direction == 'l') {
    newX = newX - 1;
  }
  else if (direction == 'r') {
    newX = newX + 1;
  }

  // TODO: do some stuff

}


void
Character::render()
{
  GLfloat vertices[] = {
    0.0f, 0.5f,
    0.5f, -0.5f,
    -0.5f, -0.5f
  };

  // TODO: not sure which of these calls i need. Will find out when
  // i start rendering more things

  //glBindVertexArray(vao);
  //glBindBuffer(GL_ARRAY_BUFFER, vbo);
  //glUseProgram(shaderProgram);

  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glDrawArrays(GL_TRIANGLES, 0, 3);
}

