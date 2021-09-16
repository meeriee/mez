#include "mez.h"
#include <stdio.h>
#include "ui/window.h"
#include "ui/render/shader.h"
#include "ui/render/renderer.h"
#include "ui/render/image.h"
#include "ui/render/texture.h"
#include "ui/render/camera.h"
#include "ui/gl.h"
#include "util/log.h"
#include <time.h>
#include <math.h>

#include "event.h"

static int r = 0;

static Shader shader;

static VertexArray VAO = {0};
static VertexBuffer VBO = {0};
static IndexBuffer EBO = {0};
static Texture tex = {0};

static mat4 MVP;
static mat4 Model;

static Camera camera;

void init_renderer();
void render();

f32 delta = 0;

f32 gettime() {
  struct timespec current_time;
  clock_gettime(CLOCK_MONOTONIC, &current_time);
  return ((f32)current_time.tv_nsec + current_time.tv_sec * 1000000000)/1000000000.0;
}

#define MOVE 1

vec3 pos = {0};
bool keys[1024];

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
    keys[key] = false;
    switch (key) {
    case GLFW_KEY_ESCAPE:
      r = 0; break;
    default: break;
    }
    if (key == GLFW_KEY_ESCAPE) r = 0;
  } break;
  case EVENT_KEY_PRESS: {
    const i32 key = e.args[0].i32data, modifiers = e.args[2].i32data;
    keys[key] = true;
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

  Image im; LoadPNG(&im, "res/img/img.png");
  CreateTexture(&tex); ApplyImageToTexture(&tex, &im);

  r = 1;

  camera.position = Vec3(0, 0, 0);
  camera.proj.type = PROJECTION_PERSPECTIVE;
  camera.proj.Persp.aspect = 1;
  camera.proj.Persp.fov = 90;
  camera.proj.near = 0.001;
  camera.proj.far = 1000;
  
  pos = Vec3(0, 0, -1);
  f32 T = gettime();
  for (;r;) {
    Model = Mat4d(1);
    Model = MulMat4(Rotate(fmodf(T, 360.0), Vec3(1,1,0)), Model);
    Model = MulMat4(Translate(pos), Model);

    CalculateCamera(&camera);

    MVP = Mat4d(1);
    MVP = MulMat4(Model, MVP);
    MVP = MulMat4(camera.matrix, MVP);

    render();
    glfwPollEvents();
    glfwSwapBuffers(wnd.wnd);

    if (keys[GLFW_KEY_W])
      camera.position = AddVec3(camera.position, Vec3(0, 0, delta*MOVE));
    if (keys[GLFW_KEY_S])
      camera.position = AddVec3(camera.position, Vec3(0, 0, -delta*MOVE));
    if (keys[GLFW_KEY_A])
      camera.position = AddVec3(camera.position, Vec3(delta*MOVE, 0, 0));
    if (keys[GLFW_KEY_D])
      camera.position = AddVec3(camera.position, Vec3(-delta*MOVE, 0, 0));

    if (keys[GLFW_KEY_UP])
      camera.position = AddVec3(camera.position, Vec3(0, -delta*MOVE, 0));
    if (keys[GLFW_KEY_DOWN])
      camera.position = AddVec3(camera.position, Vec3(0, delta*MOVE, 0));

    //    printf("%.2f %.2f %.2f\n", camera.position.X, camera.position.Y, camera.position.Z);

    const f32 Tb = gettime();
    delta = Tb - T;
    T = Tb;
  }
  CloseWindow(&wnd);
  return 0;
}

void init_renderer() {
  glDepthFunc(GL_LESS); 
  glEnable(GL_DEPTH_TEST);

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
  static const Uniform u_mvp = {.name = "MVP"};
  static const Uniform u_tex = {.name = "tex"};

  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  glActiveTexture(GL_TEXTURE0);
  BindTexture(0, &tex);

  BindShader(&shader);
  ShaderSetInt(&shader, u_tex, 0);
  ShaderSetMat4(&shader, u_mvp, MVP);

  BindVertexBuffer(&VBO);
  BindVertexArray(&VAO);

  glDrawArrays(GL_TRIANGLES, 0, 36);

  UnbindVertexBuffer();
  UnbindShader();
  UnbindVertexArray();
}

