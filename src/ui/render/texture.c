#include "texture.h"

void BindTexture(u32 slot, Texture *tex) {
  glBindTextureUnit(slot, tex->id);
}
void UnbindTexture(u32 slot) {
  glBindTextureUnit(slot, 0);
}
void CreateTexture(Texture *tex) {
  glCreateTextures(GL_TEXTURE_2D, 1, &tex->id);
}
void ApplyImageToTexture(Texture *tex, Image *im) {
  tex->size = im->size;
  tex->data = im->data;
  glTextureStorage2D(tex->id, 1, GL_RGBA32F, tex->size.W, tex->size.H);
  glTextureParameteri(tex->id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTextureParameteri(tex->id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTextureParameteri(tex->id, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTextureParameteri(tex->id, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTextureSubImage2D(tex->id, 0, 0, 0, tex->size.W, tex->size.H, GL_RGBA, GL_FLOAT, tex->data);
}
