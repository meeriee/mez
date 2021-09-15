#ifndef INCLUDE_UI_RENDER_FRAMEBUFFER_H
#define INCLUDE_UI_RENDER_FRAMEBUFFER_H
#include "mez.h"
#include "ui/gl.h"

typedef struct FramebufferSpec {
  vec2 size;
  u64 samples;
  u8 swapchain_target;
} FramebufferSpec;

typedef struct Framebuffer {
  u32 ID;
  u32 colorID, depthID;
  FramebufferSpec spec;
} Framebuffer;

void CreateFramebuffer(Framebuffer *fb);
void ResizeFramebuffer(Framebuffer *fb, vec2 size);
void BindFramebuffer(Framebuffer *fb);
void UnbindFramebuffer();
void DeleteFramebuffer(Framebuffer *fb);

void FramebufferGetPixel(Framebuffer *fb, vec2 pos);


#endif
