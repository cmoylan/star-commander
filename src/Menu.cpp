#include "Menu.h"

Menu::Menu()
{
    showing = false;

    // --- begin font --- //
    if (FT_Init_FreeType(&ft)) {
	fprintf(stderr, "Could not init freetype library\n");
    }

    if(FT_New_Face(ft, "res/Pixel-UniCode.ttf", 0, &face)) {
	fprintf(stderr, "Could not open font\n");
    }
    // --- end font --- //

    initGL();
}


Menu::~Menu()
{
}



void
Menu::initGL()
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
Menu::render()
{
    glUseProgram(shaderProgram);
    glBindVertexArray(vao);

    // --- new code --- //
    glClearColor(1, 0, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // set font to 48, black
    //FT_Set_Pixel_Sizes(face, 0, 48);
    GLfloat black[4] = {0, 0, 0, 1};
    glUniform4fv(uniformColor, 1, black);

    float sx = 2.0f / WINDOW_WIDTH;
    float sy = 2.0f / WINDOW_HEIGHT;

    FT_Set_Pixel_Sizes(face, 0, 48);
    renderText("The Quick Brown Fox Jumps Over The Lazy Dog",
		-1 + 8 * sx,   1 - 50 * sy,    sx, sy);

    Util::resetGlState();
    //glUseProgram(0);
}


void
Menu::renderText(const char *text, float x, float y, float sx, float sy)
{
    const char *p;
    FT_GlyphSlot g = face->glyph;

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

    for(p = text; *p; p++) {
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
}


void
Menu::toggle()
{
    showing = !showing;
}
