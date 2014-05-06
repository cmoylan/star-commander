#ifndef TEXTURE_H
#define TEXTURE_H

#include <stdio.h>
#include <string>

#include "LOpenGL.h"


class Texture {

  // texture name
  GLuint mTextureID;

  // texture dimensions
  GLuint mTextureWidth;
  GLuint mTextureHeight;

public:
  // constructor
  Texture();

  // destructor
  ~Texture();

  bool loadTextureFromFile(std::string path);

  bool loadTextureFromPixels32(GLuint* pixels,
                               GLuint width,
                               GLuint height);

  void  freeTexture();

  void render(GLfloat x,
              GLfloat y,
              LFRect* clip = NULL);

  GLuint getTextureID();

  GLuint textureWidth();

  GLuint textureHeight();

};

#endif
