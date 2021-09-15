#include "framebuffer.h"

void CreateFramebuffer(Framebuffer *fb) {
  if (fb->ID) {
    glDeleteFramebuffers(1, &fb->ID);
    glDeleteTextures(1, &fb->colorID);
    glDeleteTextures(1, &fb->depthID);
  }

  glCreateFramebuffers(1, &fb->ID);
  glBindFramebuffer(GL_FRAMEBUFFER, fb->ID);
  
  glCreateTextures(GL_TEXTURE_2D, 1, &fb->colorID);
  glBindTexture(GL_TEXTURE_2D, fb->colorID);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, fb->spec.size.W, fb->spec.size.H, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fb->colorID, 0);
  glCreateTextures(GL_TEXTURE_2D, 1, &fb->depthID);
  glBindTexture(GL_TEXTURE_2D, fb->depthID);
  glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, fb->spec.size.W, fb->spec.size.H);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, fb->depthID, 0);
  
  ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");
  
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void BindFramebuffer(Framebuffer *fb) {
  glBindFramebuffer(GL_FRAMEBUFFER, fb->ID);
  glViewport(0, 0, fb->spec.size.W, fb->spec.size.H);
}
void UnbindFramebuffer() {
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void DeleteFramebuffer(Framebuffer *fb) {
  glDeleteFramebuffers(1, &fb->ID);
}
