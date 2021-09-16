#include "camera.h"

void CalculateCamera(Camera *cam) {
  mat4 result = Mat4d(1);

  mat4 proj = Mat4d(1);
  mat4 view = Mat4d(1);

  switch (cam->proj.type) {
  case PROJECTION_PERSPECTIVE:
    proj = Persp(cam->proj.Persp.fov, cam->proj.Persp.aspect, cam->proj.near, cam->proj.far);
    break;
  case PROJECTION_ORTHO:
    proj = Ortho(cam->proj.Ortho.left, cam->proj.Ortho.right, cam->proj.Ortho.bottom, cam->proj.Ortho.top, cam->proj.near, cam->proj.far);
    break;
  }

  view = Translate(cam->position); 
  view = MulMat4(QuaternionToMat4(cam->rotation), view);

  result = MulMat4(view, result);
  result = MulMat4(proj, result);

  cam->matrix = result;
}
