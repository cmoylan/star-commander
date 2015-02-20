#include "TextRenderer.h"

TextRenderer::TextRenderer()
{
    if (FT_Init_FreeType(&ft)) {
        fprintf(stderr, "Could not init freetype library\n");
    }

    if (FT_New_Face(ft, "res/Pixel-UniCode.ttf", 0, &face)) {
        fprintf(stderr, "Could not open font\n");
    }

    initGL();

    font48 = new FontAtlas(face, 48, uniformTex);
}


TextRenderer::~TextRenderer() { }


void
TextRenderer::initGL()
{
    Util::createAndBindContext(&vao);

    shaderProgram =
        Util::createProgramFromShaders("src/shaders/glyph.v.glsl",
                                       "src/shaders/glyph.f.glsl");

    attributeCoord = glGetAttribLocation(shaderProgram, "coord");
    uniformTex = glGetUniformLocation(shaderProgram, "tex");
    uniformColor = glGetUniformLocation(shaderProgram, "color");

    glGenBuffers(1, &vbo);

    //Util::resetGlState();
}


void
TextRenderer::renderText(const char *text, float rawX, float rawY, float sx, float sy,
                         GLfloat color[4], int size)
{

    // convert x and y to scale
    float x = (float) rawX * sx;
    float y = (float) rawY * sy;

    const char *p;
    FT_GlyphSlot g = face->glyph;

    glUseProgram(shaderProgram);
    glBindVertexArray(vao);

    // set the color and size
    glUniform4fv(uniformColor, 1, color);
    FT_Set_Pixel_Sizes(face, 0, 32);

    /* Create a texture that will be used to hold one "glyph" */
    GLuint tex;

    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glUniform1i(uniformTex, 0);

    /* We require 1 byte alignment when uploading texture data */
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    /* Clamping to edges is important to prevent artifacts when scaling */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    /* Linear filtering usually looks best for text */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    /* Set up the VBO for our vertex data */
    glEnableVertexAttribArray(attributeCoord);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(attributeCoord, 4, GL_FLOAT, GL_FALSE, 0, 0);

    for (p = text; *p; p++) {
        if (FT_Load_Char(face, *p, FT_LOAD_RENDER)) {
            continue;
        }

        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            g->bitmap.width,
            g->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            g->bitmap.buffer
        );

        float x2 = x + g->bitmap_left * sx;
        float y2 = -y - g->bitmap_top * sy;
        float w = g->bitmap.width * sx;
        float h = g->bitmap.rows * sy;

        GLfloat box[4][4] = {
            {x2,     -y2    , 0, 0},
            {x2 + w, -y2    , 1, 0},
            {x2,     -y2 - h, 0, 1},
            {x2 + w, -y2 - h, 1, 1},
        };

        glBufferData(GL_ARRAY_BUFFER, sizeof box, box, GL_DYNAMIC_DRAW);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        x += (g->advance.x >> 6) * sx;
        y += (g->advance.y >> 6) * sy;

    }

    glDisableVertexAttribArray(attributeCoord);
    glDeleteTextures(1, &tex);
    Util::resetGlState();
}


void
TextRenderer::renderTextDefaultScale(
    const char *text, 
    float x, float y,
    GLfloat color[4], int size
) {
  float scaledX = x * textScaleX;
  float scaledY = y * textScaleY;

  renderText(text, scaledX, scaledY, textScaleX, textScaleY, color, size);
}


// not used
// void
// TextRenderer::renderText(const char *text,
//                  FontAtlas* a,
//                  float x,
//                  float y,
//                  float sx,
//                  float sy)
// {
//     const uint8_t *p;
//
//     /* Use the texture containing the atlas */
//     glBindTexture(GL_TEXTURE_2D, a->tex);
//     glUniform1i(uniformTex, 0);
//
//     /* Set up the VBO for our vertex data */
//     glEnableVertexAttribArray(attributeCoord);
//     glBindBuffer(GL_ARRAY_BUFFER, vbo);
//     glVertexAttribPointer(attributeCoord, 4, GL_FLOAT, GL_FALSE, 0, 0);
//
//     point coords[6 * strlen(text)];
//     int c = 0;
//
//     /* Loop through all characters */
//     for (p = (const uint8_t *)text; *p; p++) {
//         /* Calculate the vertex and texture coordinates */
//         float x2 = x + a->c[*p].bl * sx;
//         float y2 = -y - a->c[*p].bt * sy;
//         float w = a->c[*p].bw * sx;
//         float h = a->c[*p].bh * sy;
//
//         /* Advance the cursor to the start of the next character */
//         x += a->c[*p].ax * sx;
//         y += a->c[*p].ay * sy;
//
//         /* Skip glyphs that have no pixels */
//         if (!w || !h) {
//             continue;
//         }
//
//         coords[c++] = (point) {
//             x2, -y2, a->c[*p].tx, a->c[*p].ty
//         };
//         coords[c++] = (point) {
//             x2 + w, -y2, a->c[*p].tx + a->c[*p].bw / a->w, a->c[*p].ty
//         };
//         coords[c++] = (point) {
//             x2, -y2 - h, a->c[*p].tx, a->c[*p].ty + a->c[*p].bh / a->h
//         };
//         coords[c++] = (point) {
//             x2 + w, -y2, a->c[*p].tx + a->c[*p].bw / a->w, a->c[*p].ty
//         };
//         coords[c++] = (point) {
//             x2, -y2 - h, a->c[*p].tx, a->c[*p].ty + a->c[*p].bh / a->h
//         };
//         coords[c++] = (point) {
//             x2 + w, -y2 - h, a->c[*p].tx + a->c[*p].bw / a->w,
//             a->c[*p].ty + a->c[*p].bh / a->h
//         };
//     }
//
//     /* Draw all the character on the screen in one go */
//     glBufferData(GL_ARRAY_BUFFER, sizeof coords, coords, GL_DYNAMIC_DRAW);
//     glDrawArrays(GL_TRIANGLES, 0, c);
//
//     glDisableVertexAttribArray(attributeCoord);
// }
