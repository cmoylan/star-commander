#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

#include "Constants.h"
#include "FontAtlas.h"
#include "OpenGL.h"
#include "Util.h"


class TextRenderer {

public:
    static TextRenderer* getInstance()
    {
        static TextRenderer instance;
        return &instance;
    }

    FontAtlas* font48;

    // old signature
    void renderText(const char *text, float x, float y, float sx, float sy, GLfloat color[4], int size);
    // new with font atlas
    //void renderText(const char* text, FontAtlas* a, float x, float y, float sx,
    //                float sy);


private:
    GLuint vao;
    GLuint vbo;
    GLuint shaderProgram;
    GLint attributeCoord;
    GLint uniformTex;
    GLint uniformColor;

    void initGL();

    FT_Library ft;
    FT_Face face;
    //FT_GlyphSlot g;
    
    // --- Singleton things
    TextRenderer(); // Don't implement
    ~TextRenderer();
    TextRenderer(TextRenderer const&); // Don't implement
    void operator=(TextRenderer const&); // Don't implement
};
