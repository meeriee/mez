#ifndef INCLUDE_UI_IMAGE_H
#define INCLUDE_UI_IMAGE_H
#include "mez.h"
#include "util/file.h"

typedef struct Image {
  const char *path;
  f32 *data;
  vec2 size;

  File file;
} Image;

void LoadPNG (Image *im, const char *path);

#endif
