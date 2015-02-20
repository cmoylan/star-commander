#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

#include "Constants.h"
#include "FontAtlas.h"
#include "OpenGL.h"
#include "Util.h"


static float textScaleX = 2.0f / (float) WINDOW_WIDTH;
static float textScaleY = 2.0f / (float) WINDOW_HEIGHT;

class TextRenderer {

public:
    static TextRenderer* getInstance()
    {
        static TextRenderer instance;
        return &instance;
    }

    FontAtlas* font48;

    // TODO: set up a method that renders text with a default scale factor
    void renderTextDefaultScale(const char *text, float x, float y, 
                                GLfloat color[4], int size);
    // old signature
    void renderText(const char *text, float x, float y, float sx, float sy,
                    GLfloat color[4], int size);
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
