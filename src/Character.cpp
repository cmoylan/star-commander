#include "Character.h"


Character::Character()
{
  // initialize attributes
  height = 10;
  width = 10;

  screenPos.x = 0;
  screenPos.y = 0;

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
  glBindTexture(GL_TEXTURE_2D, tex);


  int width, height;
  unsigned char* image =
    SOIL_load_image("res/spaceship2.png", &width, &height, 0, SOIL_LOAD_RGBA);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
	       GL_UNSIGNED_BYTE, image);

  SOIL_free_image_data(image);

  glGenerateMipmap(GL_TEXTURE_2D);

  // TODO: change to gl_nearest_mipmap_nearest
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                  GL_NEAREST_MIPMAP_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_NEAREST_MIPMAP_NEAREST);

  // --- END texture stuff --- //

  // --- set up the shader programs --- //
  GLint status;

  const GLchar* characterVertexSrc =
    "#version 150 core\n"
    "in vec2 position;"
    "in vec2 texcoord;"
    "out vec2 Texcoord;"
    "uniform mat4 trans;"
    "void main() {"
    "  gl_Position = trans * vec4(position.x, position.y, 0.0, 1.0);"
    "  Texcoord = texcoord;"
    "}";

  const GLchar* characterFragmentSrc =
    "#version 150 core\n"
    "in vec2 Texcoord;"
    "out vec4 outColor;"
    "uniform sampler2D tex;"
    "void main() {"
    "  outColor = texture(tex, Texcoord);"
    "}";

  // load and compile the vertex shader code
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &characterVertexSrc, NULL);
  glCompileShader(vertexShader);

  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
  if (status != GL_TRUE) {
    printf("vertex shader did not compile!\n");
  }

  // load and compile the fragment shader code
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &characterFragmentSrc, NULL);
  glCompileShader(fragmentShader);

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
  if (status != GL_TRUE) {
    printf("fragment shader did not compile!\n");
  }

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

  GLint texAttrib = glGetAttribLocation(shaderProgram, "texcoord");
  glEnableVertexAttribArray(texAttrib);
  // the texcoords are tightly packed after the verticies in the array
  glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 0, (void*)(8 * sizeof(float)));

  // translation attr from vector shader
  uniTrans = glGetUniformLocation(shaderProgram, "trans");
  glm::mat4 trans;
  trans = glm::translate(trans, glm::vec3(0.0f, 0.0f, 1.0f));
  glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));


  // delete shaders here?
  //glDeleteShader(fragmentShader);
  //glDeleteShader(vertexShader);

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
Character::move(unsigned char direction)
{
  // TODO: go back to integers?
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

  // transform
  // TODO: move into render call
  glm::mat4 trans;
  trans = glm::translate(trans, glm::vec3(newX, newY, 1.0f));
  glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));

  screenPos.x = newX;
  screenPos.y = newY;
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

  // TODO: not sure which of these calls i need. Will find out when
  // i start rendering more things

  //glBindVertexArray(vao);
  //glBindBuffer(GL_ARRAY_BUFFER, vbo);
  //glUseProgram(shaderProgram);

  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // --- this may go back in the main loop and only get called once
  // draw a rectangle from 2 triangles
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

