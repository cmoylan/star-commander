#define GLEW_STATIC
#include <GL/glew.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>


//void runMainLoop(int val);

// shader programs...probably do these in their own files
const GLchar* vertexSource =
  "#version 150 core\n"
  "in vec2 position;"
  "in vec3 color;"
  "out vec3 Color;"
  "void main() {"
  "  Color = color;"
  "  gl_Position = vec4(position.x, position.y, 0.0, 1.0);"
  "}";

const GLchar* fragmentSource =
  "#version 150 core\n"
  "in vec3 Color;"
  "out vec4 outColor;"
  "void main() {"
  "  outColor = vec4(Color, 1.0);"
  "}";


int
main(int argc, char *args[])
{
  // setup
  SDL_Init(SDL_INIT_VIDEO);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

  SDL_Window *window = SDL_CreateWindow("DO IT OpenGL", 100, 100, 800, 600, SDL_WINDOW_OPENGL);
  SDL_GLContext context = SDL_GL_CreateContext(window);

  // Initialize GLEW
  glewExperimental = GL_TRUE;
  glewInit();

  // vertex array object...???
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  GLuint vbo; // vertex buffer object
  glGenBuffers(1, &vbo); // generate 1 buffer

  // vertex: pos.x, pos.y, r, g, b
  GLfloat vertices[] = {
    0.0f, 0.5f, 1.0f, 0.0f, 0.0f,  // vertex 1 red
    0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // vertex 2 green
    -0.5f, -0.5f, 0.0f, 0.0f, 1.0f  // vertex 3 blue
  };

  // make vbo the active buffer and send the vertices to it
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // load and compile the vertex shader code
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexSource, NULL);
  glCompileShader(vertexShader);
  // TODO: make sure shader compiled successfully

  // load and compile the fragment shader code
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
  glCompileShader(fragmentShader);
  //GLint status;
  //glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);

  // TODO: make sure shader compiled successfully

  // combine the vertex and fragment shaders into a program
  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  // this line is not neccessary with only one buffer
  glBindFragDataLocation(shaderProgram, 0, "outColor");

  // link all shaders into the program
  glLinkProgram(shaderProgram);
  glUseProgram(shaderProgram);

  // retrive reference to `position` in the vertexShader
  GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
  glEnableVertexAttribArray(posAttrib);
  // tell the program how the vertexArray `vertices` is laid out
  glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE,
			(5 * sizeof(float)), 0);

  GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
  glEnableVertexAttribArray(colAttrib);
  glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE,
			(5 * sizeof(float)), (void*)(2 * sizeof(float)));

  // set the color for the frgment shader
  //GLint uniColor = glGetUniformLocation(shaderProgram, "triangleColor");
  //glUniform3f(uniColor, 1.0f, 0.0f, 0.0f);


  //printf("error: %x\n", glGetError());

  // main loop
  SDL_Event windowEvent;
  while(true) {
    if (SDL_PollEvent(&windowEvent)) {
      if (windowEvent.type == SDL_QUIT) break;

      if (windowEvent.type = SDL_KEYUP &&
	  windowEvent.key.keysym.sym == SDLK_ESCAPE) break;
    }

    glDrawArrays(GL_TRIANGLES, 0, 3);
    SDL_GL_SwapWindow(window);
  }

  // teardown
  glDeleteProgram(shaderProgram);
  glDeleteShader(fragmentShader);
  glDeleteShader(vertexShader);

  glDeleteBuffers(1, &vbo);

  glDeleteVertexArrays(1, &vao);

  SDL_GL_DeleteContext(context);
  SDL_Quit();

  return 0;

  // --------------------------------------------------------------
  // intialize FreeGLUT
  //glutInit(&argc, args);
  //
  //// create OpenGL 2.1 context
  //glutInitContextVersion(2, 1);
  //
  //// create double-buffered window
  //glutInitDisplayMode(GLUT_DOUBLE);
  //glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
  //glutCreateWindow("OpenGL");
  //
  //// do post window/context creation initialization
  //if (!initGL()) {
  //  // TODO: better debugging
  //  printf("Unable to initialize graphics library!\n");
  //  return 1;
  //}
  //
  //// set keyboard handler
  //glutKeyboardFunc(handleKeys);
  //
  //// set rendering function
  //glutDisplayFunc(render);
  //
  //// set main loop
  //glutTimerFunc(1000 / SCREEN_FPS, runMainLoop, 0);
  //
  //// start main loop
  //glutMainLoop();
  //
  //return 0;
}
