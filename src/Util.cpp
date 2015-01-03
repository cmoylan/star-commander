#include "Util.h"


GLuint
createProgram(const std::vector<GLuint> &shaderList)
{
    size_t i;
    GLuint program;
    GLint status;

    program = glCreateProgram();

    // TODO: rewrite to use vector iterator?
    for (i = 0; i < shaderList.size(); i++) {
        glAttachShader(program, shaderList.at(i));
    }

    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        printf("ERROR: error linking shader program\n");
    }

    for (i = 0; i < shaderList.size(); i++) {
        glDetachShader(program, shaderList.at(i));
    }

    return program;
}


GLuint
createShader(GLenum shaderType, const std::string &shaderFile)
{
    GLint status;
    std::string shaderSource;

    shaderSource = loadStringFromFile(shaderFile.c_str());

    GLuint shader = glCreateShader(shaderType);

    const char *strFileData = shaderSource.c_str();

    glShaderSource(shader, 1, &strFileData, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    if (status != GL_TRUE) {
        GLint infoLogLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

        printf("ERROR: unable to compile shader: %s\n", shaderSource.c_str());

        //GLchar *strInfoLog = newGLchar[infoLogLength + 1];
        //glGetShaderInfoLog(shader, strInfoLog,  infoLogLength);
        //
        //// TODO: log to stderror
        //printf("shader did not compile: %s - %s\n", shaderType, strInfoLog);
        //
        //delete[] strInfoLog;
    }

    return shader;
}


std::string
loadStringFromFile(const std::string &filename)
{
    std::stringstream sstr;
    std::ifstream file;

    file.open(filename.c_str(), std::ifstream::in);

    if (file.is_open()) {
        sstr << file.rdbuf();
        return sstr.str();
    }
    else {
        printf("ERROR: unable to open file %s\n", filename.c_str());
        return "";
    }
}


void
//#args: buffer, filename
loadTexture(GLuint buffer, const std::string &filename)
{
    int width, height;
    unsigned char* image;

    glBindTexture(GL_TEXTURE_2D, buffer);

    image = SOIL_load_image(filename.c_str(),
                            &width,
                            &height,
                            0,
                            SOIL_LOAD_RGBA);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, image);

    SOIL_free_image_data(image);

    glGenerateMipmap(GL_TEXTURE_2D);

    // TODO: change to gl_nearest_mipmap_nearest
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                    GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_NEAREST_MIPMAP_NEAREST);
}
