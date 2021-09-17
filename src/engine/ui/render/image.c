#include "image.h"
#include <png.h>
#include "util/log.h"

void LoadPNG(Image *image, const char *path) {
  static Channel Loading;
  if (Loading.name == NULL) Loading = CreateChannel("resource");

  image->file.path = path;
  FileCreate(&image->file);
  FileOpen(&image->file, "rb");

  if (image->file.fp == NULL) {
    ERROR(Loading, "Failed to open file pointer (path: %s)", path);
    return;
  }

  uint8_t header[8];
  if (fread(header, 1, 8, image->file.fp) != 8) {
    ERROR(Loading, "Failed to read PNG header (path: %s)", path);
    fclose(image->file.fp);
    image->file.fp = NULL;
    return;
}

  if (png_sig_cmp(header, 0, 8) != 0) {
    ERROR(Loading, "%s is not a PNG file", path);
    fclose(image->file.fp);
    return;
  }

  png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (png_ptr == NULL) {
    ERROR(Loading, "failed to create png read struct (path %s)", path);
    png_destroy_read_struct(&png_ptr, NULL, NULL);
    fclose(image->file.fp); return;
  }

  png_infop info_ptr = png_create_info_struct(png_ptr);
  if (info_ptr == NULL) {
    ERROR(Loading, "failed to create png info struct (path %s)", path);
    png_destroy_read_struct(&png_ptr, NULL, NULL); 
    fclose(image->file.fp); return;
  }

  png_init_io(png_ptr, image->file.fp);
  png_set_sig_bytes(png_ptr, 8);
  png_read_info(png_ptr, info_ptr);

  const u32 width = png_get_image_width(png_ptr, info_ptr);
  const u32 height = png_get_image_height(png_ptr, info_ptr);
  image->size.W  = width;
  image->size.H = height;

  const float max = (float)(1.0 / (1 << png_get_bit_depth(png_ptr, info_ptr)));

  const int color_type = png_get_color_type(png_ptr, info_ptr);
  const int channels = png_get_channels(png_ptr, info_ptr);
  const size_t rowbytes = png_get_rowbytes(png_ptr, info_ptr);

  if (!(channels == 3 || channels == 4)) {
    ERROR(Loading, "Failed to load %s! Wrong amount of channels (%d)", path, channels); return;
  }
  if (!(color_type == PNG_COLOR_TYPE_RGB || color_type == PNG_COLOR_TYPE_RGBA)) {
    ERROR(Loading, "Failed to load %s! Wrong color type (%d)!", path, color_type); return;
  }

  png_bytepp row_ptr = (png_bytepp)malloc(sizeof(png_bytep) * height);
  for (uint32_t y = 0; y < height; ++y) row_ptr[y] = (png_bytep)malloc(sizeof(png_byte) * rowbytes);
  png_read_image(png_ptr, row_ptr);

  image->data = malloc(4 * width * height * sizeof(float));

  for (uint32_t y = 0; y < height; y++) {
    png_bytep row = row_ptr[y];
    for (uint32_t x = 0; x < width; x++) {
      const u32 offset = x * (u32)(channels);
      image->data[(width * y * 4) + x * 4 + 0] = row[offset + 0] * max;
      image->data[(width * y * 4) + x * 4 + 1] = row[offset + 1] * max;
      image->data[(width * y * 4) + x * 4 + 2] = row[offset + 2] * max;
      image->data[(width * y * 4) + x * 4 + 3] = channels == 4 ? row[offset + 3] * max : 1.0f;
    }
    free(row);
  }
  free(row_ptr);

  png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
  FileClose(&image->file);

  INFO(Loading, "Succesfully loaded %s", path);

}
