#ifndef INCLUDE_UI_GL_H
#define INCLUDE_UI_GL_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

void GLAPIENTRY MsgCallback(GLenum source, GLenum type, GLuint id,
                            GLenum severity, GLsizei len, const GLchar *msg,
                            const void *user);

#endif
