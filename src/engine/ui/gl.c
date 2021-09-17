#include "gl.h"
#include "util/log.h"

void GLAPIENTRY MsgCallback(GLenum source, GLenum type, GLuint id,
                            GLenum severity, GLsizei len, const GLchar *msg,
                            const void *user) {
  static Channel GL = {0};
  if (GL.name == NULL) GL = CreateChannel("OpenGL");
  (void)source;
  (void)id;
  (void)user;
  (void)len;

  WARN(GL, "%s (type = 0x%x, severity = 0x%x)", msg, type, severity);
}
