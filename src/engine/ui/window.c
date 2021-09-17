#include "window.h"

void window_resize_callback(GLFWwindow *wnd, i32 w, i32 h) {
  Window *window = glfwGetWindowUserPointer(wnd);
  window->size.W = (f32)w;
  window->size.H = (f32)h;

  const Event e = {.type = EVENT_WINDOW_RESIZE,
                   .args = {
                       {ARG_I32, .i32data=w},
                       {ARG_I32, .i32data=h},
                       {ARG_END},
                   }};
  if (window->event_callback) window->event_callback(e);
}

void window_move_callback(GLFWwindow *wnd, i32 x, i32 y) {
  Window *window = glfwGetWindowUserPointer(wnd);

  const Event e = {.type = EVENT_WINDOW_MOVE,
                   .args = {
                       {ARG_I32, .i32data=x},
                       {ARG_I32, .i32data=y},
                       {ARG_END},
                   }};
  if (window->event_callback) window->event_callback(e);
}

void window_close_callback(GLFWwindow *wnd) {
  Window *window = glfwGetWindowUserPointer(wnd);

  const Event e = {.type = EVENT_WINDOW_CLOSE,
                   .args = {{ARG_END}}};
  if (window->event_callback) window->event_callback(e);
}

void key_callback(GLFWwindow *wnd, i32 key, i32 scancode, i32 action,
                  i32 mods) {
  Window *window = glfwGetWindowUserPointer(wnd);

  EventType type = EVENT_NONE;
  switch (action) {
    case GLFW_PRESS:
      type = EVENT_KEY_PRESS;
      break;
    case GLFW_RELEASE:
      type = EVENT_KEY_RELEASE;
      break;
    case GLFW_REPEAT:
      type = EVENT_KEY_REPEAT;
      break;
  }

  const Event e = {.type = type,
		   .args = {{ARG_I32, .i32data=key},
			    {ARG_I32, .i32data=scancode},
			    {ARG_I32, .i32data=mods},
			    {ARG_END}}};
  if (window->event_callback) window->event_callback(e);
}


i32 CreateWindow(Window *window) {
  if (window == NULL) return 1;
  glfwInit();
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

  window->wnd = glfwCreateWindow((i32)window->size.W, (i32)window->size.H, window->title, NULL, NULL);
  glfwMakeContextCurrent(window->wnd);
  glfwSetWindowUserPointer(window->wnd, window);

  glfwSetFramebufferSizeCallback(window->wnd, window_resize_callback);
  glfwSetWindowPosCallback(window->wnd, window_move_callback);
  glfwSetWindowCloseCallback(window->wnd, window_close_callback);
  glfwSetKeyCallback(window->wnd, key_callback);

  glewExperimental = 1;
  glewInit();

  glEnable(GL_DEBUG_OUTPUT);
  glDebugMessageCallback(MsgCallback, NULL);
  return 0;
}

i32 CloseWindow(Window *window) {
  glfwDestroyWindow(window->wnd);
  glfwTerminate();
  return 0;
}
