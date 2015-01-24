#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "OpenGL.h"
#include "Constants.h"
#include "Util.h"


class Entity {

public:

    // allow direct access to these...why not
    Vector2D origin;
    Vector2D size;

    virtual void hit() = 0;

    GLuint vao, tex, uniTrans;
    GLuint shaderProgram;

    void initGL(std::string texture);
    void render();

};
