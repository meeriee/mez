#include "mez.h"
#include <stdio.h>
#include "ui/window.h"
#include "ui/render/shader.h"
#include "ui/render/renderer.h"
#include "ui/gl.h"
#include "util/log.h"
#include <time.h>

#include "event.h"

static int r = 0;

static Shader shader;

static VertexArray VAO = {0};
static VertexBuffer VBO = {0};
static IndexBuffer EBO = {0};
static mat4 MVP;

void init_renderer();
void render();

f32 delta = 0;

f32 gettime() {
  struct timespec current_time;
  clock_gettime(CLOCK_MONOTONIC, &current_time);
  return ((f32)current_time.tv_nsec + current_time.tv_sec * 1000000000)/1000000000.0;
}

#define MOVE_X 0.05
#define MOVE_Y 0.05

vec3 pos = {0};

void window_callback(Event e) {
  switch (e.type) {
  case EVENT_WINDOW_CLOSE:
    r = 0;
    break;
  case EVENT_WINDOW_MOVE:
    break;
  case EVENT_WINDOW_RESIZE: {
    const i32 w = e.args[0].i32data, h = e.args[1].i32data;
    (void)w;
    (void)h;
  } break;
  case EVENT_KEY_RELEASE: {
    const i32 key = e.args[0].i32data, modifiers = e.args[2].i32data;
    switch (key) {
    case GLFW_KEY_ESCAPE:
      r = 0; break;
    default: break;
    }
    if (key == GLFW_KEY_ESCAPE) r = 0;
  } break;
  case EVENT_KEY_PRESS: {
    const i32 key = e.args[0].i32data, modifiers = e.args[2].i32data;
    switch (key) {
    case GLFW_KEY_RIGHT:
      pos = AddVec3(pos, Vec3(MOVE_X, 0, 0)); break;
    case GLFW_KEY_LEFT:
      pos = AddVec3(pos, Vec3(-MOVE_X, 0, 0)); break;
    case GLFW_KEY_UP:
      pos = AddVec3(pos, Vec3(0, MOVE_Y, 0)); break;
    case GLFW_KEY_DOWN:
      pos = AddVec3(pos, Vec3(0, -MOVE_Y, 0)); break;
    default: break;
    }
  }
  default: break;
  }
}

Channel general;

int main(int argc, char **argv) {
  Window wnd = {.size.W=400, .size.H=400, .title = "mez"};
  CreateWindow(&wnd);
  wnd.event_callback = window_callback;

  InitRenderer();
  init_renderer();

  general = CreateChannel("general");

  LoadShaderFile(&shader, "res/shader/shader.glsl");
  CompileShader(&shader);

  r = 1;
  pos.Z = -2;
  
  f32 T = gettime();
  for (;r;) {
    MVP = MulMat4(Persp(120, 1, 0.001, 1000), Translate(pos));
    render();
    glfwPollEvents();
    glfwSwapBuffers(wnd.wnd);

    const f32 Tb = gettime();
    delta = Tb - T;
    T = Tb;
  }
  CloseWindow(&wnd);
  return 0;
}

void init_renderer() {
  glEnable(GL_DEPTH);

  static const float verticies[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
    
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
      
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
  };
  CreateVertexArray(&VAO);

  CreateVertexBuffer(&VBO, 36*5, verticies);

  VertexArrayAdd(&VAO, (struct VertexArrayElement){GL_FLOAT, 3, 0});
  VertexArrayAdd(&VAO, (struct VertexArrayElement){GL_FLOAT, 2, 0});
  MakeVertexArray(&VAO);

  UnbindVertexArray();
}


void render() {
  static const Uniform mvp = {.name = "MVP"};

  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  ShaderSetMat4(&shader, mvp, MVP);
  BindShader(&shader);

  BindVertexBuffer(&VBO);
  BindVertexArray(&VAO);

  glDrawArrays(GL_TRIANGLES, 0, 36);

  //  UnbindVertexBuffer();
  //  UnbindShader();
  UnbindVertexArray();
}

