void compileShader(GLchar *source, GLuint *reference)
{
  GLint status;

  reference = glCreateShader(GL_VERTEX_SHADER);

  glShaderSource(reference, 1, source, NULL);
  glCompileShader(reference);

  glGetShaderiv(reference, GL_COMPILE_STATUS, &status);
  if (status != GL_TRUE) {
    // TODO: better erorr handling
    prinft("shader did not compile!\n");
  }
}
