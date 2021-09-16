#ifndef INCLUDE_UI_TEXTURE_H
#define INCLUDE_UI_TEXTURE_H
#include "mez.h"
#include "image.h"
#include "ui/gl.h"

typedef struct Texture {
  vec2 size;
  float *data;

  u32 id;
} Texture;

void BindTexture(u32 slot, Texture *tex);
void UnbindTexture(u32 slot);
void CreateTexture(Texture *tex);
void ApplyImageToTexture(Texture *tex, Image *im);

#endif
