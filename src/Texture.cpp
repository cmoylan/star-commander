#include "Texture.h"
#include "CImg.h"


Texture::Texture()
{
  // initialize texture ID
  mTextureID = 0;

  // initialize texture dimensions
  mTextureWidth = 0;
  mTextureHeight = 0;
}


Texture::~Texture()
{
  // free texture data if needed
  freeTexture();
}


bool
Texture::loadTextureFromFile(std::string path)
{
  // texture loading success
  bool textureLoaded = false;

  // generate and set current image ID
  //ILuint imgID = 0;
  //ilGenImages(1, &imgID);
  //ilBindImage(imgID);

  // load image
  //ILboolean success = ilLoadImage(path.c_str());

  // image loaded successfully
  //if (success == IL_TRUE) {
  //  // convert image to RGBA
  //  success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
  //
  //  if (success == IL_TRUE) {
  //    // create texture from file pixels
  //    textureLoaded = loadTextureFromPixels32(\
  //                                            (GLuint*) ilGetData(),
  //                                            (GLuint) ilGetInteger(IL_IMAGE_WIDTH),
  //                                            (GLuint) ilGetInteger(IL_IMAGE_HEIGHT));
  //  }
  //
  //  // delete file from memory
  //  ilDeleteImages(1, &imgID);
  //}

  cimg_library::CImg<int> textureFile(path.c_str());

  textureLoaded = loadTextureFromPixels32(textureFile.data(),
                                          textureFile.width()
                                          textureFile.height());

  // report error
  if (!textureLoaded) {
    // TODO: debug
    printf("Unable to load %s\n", path.c_str());
  }

  return textureLoaded;
}


bool
Texture::loadTextureFromPixels32(GLuint* pixels,
                                 GLuint width,
                                 GLuint height)
{
  // free texture if it exists
  freeTexture();

  // get texture dimensions
  mTextureWidth = width;
  mTextureHeight = height;

  // generate texture ID
  glGenTextures(1, &mTextureID);

  // bind texture ID
  glBindTexture(GL_TEXTURE_2D, mTextureID);

  // generate texture
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,
               0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

  // set texture parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  // unbind texture
  glBindTexture(GL_TEXTURE_2D, NULL);

  // check for error
  GLenum error = glGetError();
  if (error != GL_NO_ERROR) {
    printf("Error loading texture from %p pixels! %s\n",
           pixels,
           gluErrorString(error));
    return false;
  }

  return true;
}


void
Texture::freeTexture()
{
  // delete texture
  if (mTextureID != 0) {
    glDeleteTextures(1, &mTextureID);
    mTextureID = 0;
  }

  mTextureWidth = 0;
  mTextureHeight = 0;
}


void
Texture::render(GLfloat x, GLfloat y, LFRect* clip)
{
  // if the texture exists
  if (mTextureID != 0) {
    // remove any previous transformations
    glLoadIdentity();

    // texture coordinates
    GLfloat texTop = 0.f;
    GLfloat texBottom = 1.f;
    GLfloat texLeft = 0.f;
    GLfloat texRight = 1.f;

    // vertex coordinates
    GLfloat quadWidth = mTextureWidth;
    GLfloat quadHeight = mTextureHeight;

    // handle clipping
    if (clip != NULL) {
      // texture coordinates
      texLeft = clip->x / mTextureWidth;
      texRight = (clip->x + clip->w) / mTextureWidth;
      texTop = clip->y / mTextureHeight;
      texBottom = (clip->y + clip->h) / mTextureHeight;

      // vertex coordinates
      quadWidth = clip->w;
      quadHeight = clip->h;
    }

    // move to rendering point
    glTranslatef(x, y, 0.f);

    // set texture id
    glBindTexture(GL_TEXTURE_2D, mTextureID);

    // render textured quad
    glBegin(GL_QUADS);
    glTexCoord2f(0.f, 0.f);
    glVertex2f(0.f, 0.f);
    glTexCoord2f(1.f, 0.f);
    glVertex2f(mTextureWidth, 0.f);
    glTexCoord2f(1.f, 1.f);
    glVertex2f(mTextureWidth, mTextureHeight);
    glTexCoord2f(0.f, 1.f);
    glVertex2f(0.f, mTextureHeight);
    glEnd();
  }
}


GLuint
Texture::getTextureID()
{
  return mTextureID;
}


GLuint
Texture::textureWidth()
{
  return mTextureWidth;
}


GLuint
Texture::textureHeight()
{
  return mTextureHeight;
}
