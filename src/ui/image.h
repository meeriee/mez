#ifndef INCLUDE_UI_IMAGE_H
#define INCLUDE_UI_IMAGE_H
#include "mez.h"

typedef struct Image {
  const char *path;
  u8 *data;
} Image;

void LoadPNG (Image *im, const char *path);
void LoadTIFF(Image *im, const char *path);
void LoadJPG (Image *im, const char *path);

#endif
