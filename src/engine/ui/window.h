#ifndef INCLUDE_UI_WINDOW_H
#define INCLUDE_UI_WINDOW_H
#include "mez.h"
#include "event.h"
#include "ui/gl.h"

typedef struct Window {
  vec2 size;
  const char *title;

  GLFWwindow *wnd;

  EventCallbackFun event_callback;
} Window;

i32 CreateWindow(Window *window);
i32 CloseWindow(Window *window);


#endif
