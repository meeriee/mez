#ifndef INCLUDE_RENDER_CAMERA_H
#define INCLUDE_RENDER_CAMERA_H
#include "mez.h"

typedef enum ProjectionType {
  PROJECTION_PERSPECTIVE,
  PROJECTION_ORTHO,
} ProjectionType;

typedef struct Projection{
  ProjectionType type;
  struct {
    f32 fov, aspect;
  } Persp;
  struct {
    f32 left, right, bottom, top;
  } Ortho;
  f32 near, far;
} Projection;

typedef struct Camera {
  vec3 position;
  vec3 rotation;

  Projection proj;

  mat4 matrix;
} Camera;

void CalculateCamera(Camera *cam);

#endif
