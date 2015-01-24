#include "Entity.h"

void
Entity::initGL(std::string texture)
{
    // --- set up buffers/program
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    glGenTextures(1, &tex);
    loadTexture(tex, texture);

    // set up the shader program
    shaderProgram = createProgramFromShaders("src/shaders/texturedSquare.v.glsl",
                    "src/shaders/texturedSquare.f.glsl");
    glUseProgram(shaderProgram);

    // --- map glsl attributes to pointers
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(posAttrib);

    // texture position
    GLint texAttrib = glGetAttribLocation(shaderProgram, "texcoord");
    glEnableVertexAttribArray(texAttrib);
    // the texcoords are tightly packed after the verticies in the array
    // TODO: you can remove this and go a different route
    glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 0,
                          (void*)(8 * sizeof(float)));

    // translation attr from vector shader
    uniTrans = glGetUniformLocation(shaderProgram, "trans");

    // --- send initial data to the shader
    GLuint elements[] = {
        0, 1, 2,
        2, 3, 0
    };

    GLfloat vertices[] = {
        0.f, (SCALE_Y * (float) size.y), // top left
        (SCALE_X * (float) size.x), (SCALE_Y * (float) size.y), // top right
        (SCALE_X * (float) size.x), 0.f, // bottom right
        0.f, 0.f, // bottom left

        // Texcoords
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f
    };
    //printf("size is: [%d %d] [%f %f] \n", size, size);
    //printf("vertices [%f %f]\n", vertices[2], vertices[5]);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements),
                 elements, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    resetGlState();
}


void
Entity::render()
{
    glUseProgram(shaderProgram);
    glBindVertexArray(vao);
    glBindTexture(GL_TEXTURE_2D, tex);

    // transparency
    // TODO: need to set this every time?
    //glEnable (GL_BLEND);
    //glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // transform coords based on origin of enemy
    glm::mat4 trans;
    trans = glm::translate(trans,
                           glm::vec3((SCALE_X * (float) origin.x),
                                     (SCALE_Y * (float) origin.y),
                                     1.0f));
    glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    resetGlState();
}
