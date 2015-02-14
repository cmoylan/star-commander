#include "Menu.h"

Menu::Menu()
{
    // menu will resize if necessary
    itemWidth = MENU_ITEM_WIDTH;
    itemHeight = MENU_ITEM_HEIGHT;
    leftEdge = (SCREEN_X - itemWidth) / 2;
    showing = false;

    initGL();

    // --- font stuff
      // Create a pixmap font from a TrueType file.
    font = new FTPixmapFont("/home/chris/Downloads/freesans/sfd/FreeMonoBold.ttf");
    //FTGLTextureFont("/home/chris/Downloads/freesans/sfd/FreeMonoBold.ttf");

    // If something went wrong, bail out.
    if(font->Error())
      printf("error with the font\n");

    // Set the font size and render a small text.
    if (!font->FaceSize(72))
      printf("error with face size!\n");
    // --- end font stuff

    // test texture for now
    glGenTextures(1, &tex);
    //Util::loadTexture(tex, "res/test-bg.png");
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex);
    
    //FTPoint* texture = font->Render("fuck yea");
    //texture->
    
    glBindTexture(GL_TEXTURE_2D, 0);
}


Menu::~Menu()
{
}



void
Menu::initGL()
{
    Util::createAndBindContext(&vao);

    // TODO: create a shader manager to compile these
    shaderProgram =
        Util::createProgramFromShaders("src/shaders/texturedSquare.v.glsl",
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

    GLint elements[] = {
        0, 1, 2,
        2, 3, 0
    };

    GLfloat vertices[] = {
        0.f, (SCALE_Y * (float) itemHeight), // top left
        (SCALE_X * (float) itemWidth), (SCALE_Y * (float) itemHeight), // top right
        (SCALE_X * (float) itemWidth), 0.f, //bottom right
        0.f, 0.f, // bottom left

        // Texcoords
        0.f, 0.f,
        1.f, 0.f,
        1.f, 1.f,
        0.f, 1.f
    };

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements,
                 GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    Util::resetGlState();
}


void
Menu::render()
{
    // add a black, translucent overlay to screen
    // display buttons - centered

    // go through each button
    // if it is selected change the background or color
    // if it is not selected just draw it

    // probably make textures for the text
    // calculate width of menu, and center it
    // may need a texture loader

    //glUseProgram(shaderProgram);
    // glBindVertexArray(vao);
    // glBindTexture(GL_TEXTURE_2D, tex);
    //
    // glm::mat4 trans;
    // trans = glm::translate(trans,
    //                        glm::vec3(-(SCALE_X * (float) leftEdge),
    //                                  (SCALE_Y * (float) 1),
    //                                  1.0f));
    // glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));
    glOrtho();
    glUseProgram(0);
    glColor4f(1.0, 1.0, 1.0, 0.9);
    //font->Render("Hello World!", 0, 0);
    glColor3f(1.0, 1.0, 1.0); /* White inside */
    font->Render("Hello", -1, FTPoint(), FTPoint());
//     glEnable(GL_BLEND);
//     //font->Render("Hello World!");
//     glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
     Util::resetGlState();
    
    //glLoadIdentity();
    //glColor3f( 1.0, 0.0, 0.0);
//    glPushAttrib(GL_ALL_ATTRIB_BITS);
//    glEnable(GL_BLEND);
//    glDisable(GL_LIGHTING);
//    glDisable(GL_DEPTH_TEST);
//    glColor3f(0.0, 0.0, 1.0);
//    font->Render("Hello World!");
//    //glDrawElements(GL_STATIC_DRAW, 1, GL_UNSIGNED_INT, 0);
//    glPopAttrib();
     //glUseProgram(0);

    //float sc = 0.035;

    //glPushMatrix();
    //glPushAttrib(GL_ALL_ATTRIB_BITS);
    //glTranslatef(0.0, 0.0, 10.0);
    //glRotatef(0.0, 1.0, 0.0, 0.0);
    //glScalef(1.0, 0.75, 1.0);
     //    font->Render("Hello World");
    //glPopMatrix();
    //glPopAttrib();

    
}


void
Menu::toggle()
{
    showing = !showing;
}
