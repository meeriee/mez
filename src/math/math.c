#include "math.h"
#include <math.h>

vec2 Vec2(f32 x, f32 y) {
  vec2 result = {0};
  result.X = x;
  result.Y = y;
  return result;
}

vec2 Vec2i(i32 x, i32 y){
  vec2 result = {0};
  result.X = (f32)x;
  result.Y = (f32)y;
  return result;
}
vec3 Vec3 (f32 x, f32 y, f32 z){
  vec3 result = {0};
  result.X = x;
  result.Y = y;
  result.Z = z;
  return result;
}
vec3 Vec3i(i32 x, i32 y, i32 z){
  vec3 result = {0};
  result.X = (f32)x;
  result.Y = (f32)y;
  result.Z = (f32)z;
  return result;
}
vec4 Vec4 (f32 x, f32 y, f32 z, f32 w){
  vec4 result = {0};
  result.X = x;
  result.Y = y;
  result.Z = z;
  result.W = w;
  return result;
}
vec4 Vec4i(i32 x, i32 y, i32 z, f32 w){
  vec4 result = {0};
  result.X = (f32)x;
  result.Y = (f32)y;
  result.Z = (f32)z;
  result.W = (f32)w;
  return result;
}
vec4 Vec4v(vec3 v, f32 w){
  vec4 result = {0};
  result.XYZ = v;
  result.W = w;
  return result;
}

vec2 AddVec2(vec2 a, vec2 b){
  vec2 result = {0};
  result.X = a.X + b.X;
  result.Y = a.Y + b.Y;
  return result;
}
vec3 AddVec3(vec3 a, vec3 b){
  vec3 result = {0};
  result.X = a.X + b.X;
  result.Y = a.Y + b.Y;
  result.Z = a.Z + b.Z;
  return result;
}
vec4 AddVec4(vec4 a, vec4 b){
  vec4 result = {0};
  result.X = a.X + b.X;
  result.Y = a.Y + b.Y;
  result.Z = a.Z + b.Z;
  result.W = a.W + b.W;
  return result;
}

vec2 SubVec2(vec2 a, vec2 b){
  vec2 result = {0};
  result.X = a.X - b.X;
  result.Y = a.Y - b.Y;
  return result;
}
vec3 SubVec3(vec3 a, vec3 b){
  vec3 result = {0};
  result.X = a.X - b.X;
  result.Y = a.Y - b.Y;
  result.Z = a.Z - b.Z;
  return result;
}
vec4 SubVec4(vec4 a, vec4 b){
  vec4 result = {0};
  result.X = a.X - b.X;
  result.Y = a.Y - b.Y;
  result.Z = a.Z - b.Z;
  result.W = a.W - b.W;
  return result;
}

vec2 MulVec2 (vec2 a, vec2 b){
  vec2 result = {0};
  result.X = a.X * b.X;
  result.Y = a.Y * b.Y;
  return result;
}
vec2 MulVec2f(vec2 a, f32 s){
  vec2 result = {0};
  result.X = a.X * s;
  result.Y = a.Y * s;
  return result;
}
vec3 MulVec3 (vec3 a, vec3 b){
  vec3 result = {0};
  result.X = a.X * b.X;
  result.Y = a.Y * b.Y;
  result.Z = a.Z * b.Z;
  return result;
}
vec3 MulVec3f(vec3 a, f32 s){
  vec3 result = {0};
  result.X = a.X * s;
  result.Y = a.Y * s;
  result.Z = a.Z * s;
  return result;
}
vec4 MulVec4 (vec4 a, vec4 b){
  vec4 result = {0};
  result.X = a.X * b.X;
  result.Y = a.Y * b.Y;
  result.Z = a.Z * b.Z;
  result.W = a.W * b.W;
  return result;
}
vec4 MulVec4f(vec4 a, f32 s){
  vec4 result = {0};
  result.X = a.X * s;
  result.Y = a.Y * s;
  result.Z = a.Z * s;
  result.W = a.W * s;
  return result;
}

vec2 DivVec2 (vec2 a, vec2 b){
  vec2 result = {0};
  result.X = a.X / b.X;
  result.Y = a.Y / b.Y;
  return result;
}
vec2 DivVec2f(vec2 a, f32 s){
  vec2 result = {0};
  result.X = a.X / s;
  result.Y = a.Y / s;
  return result;

}
vec3 DivVec3 (vec3 a, vec3 b){
  vec3 result = {0};
  result.X = a.X / b.X;
  result.Y = a.Y / b.Y;
  result.Z = a.Z / b.Z;
  return result;
}
vec3 DivVec3f(vec3 a, f32 s){
  vec3 result = {0};
  result.X = a.X / s;
  result.Y = a.Y / s;
  result.Z = a.Z / s;
  return result;
}
vec4 DivVec4 (vec4 a, vec4 b){
  vec4 result = {0};
  result.X = a.X / b.X;
  result.Y = a.Y / b.Y;
  result.Z = a.Z / b.Z;
  result.W = a.W / b.W;
  return result;
}
vec4 DivVec4f(vec4 a, f32 s){
  vec4 result = {0};
  result.X = a.X / s;
  result.Y = a.Y / s;
  result.Z = a.Z / s;
  result.W = a.W / s;
  return result;
}

u8 EqVec2(vec2 a, vec2 b){
  u8 result = 0;
  result = a.X == b.X && a.Y == b.Y;
  return result;
}
u8 EqVec3(vec3 a, vec3 b){
  u8 result = 0;
  result = a.X == b.X && a.Y == b.Y && a.Z == b.Z;
  return result;
}
u8 EqVec4(vec4 a, vec4 b){
  u8 result = 0;
  result = a.X == b.X && a.Y == b.Y && a.Z == b.Z && a.W == b.W;
  return result;
}

vec3 CrossVec3(vec3 a, vec3 b){
  vec3 result = {0};
  result.X = (a.Y * b.Z) - (a.Z * b.Y);
  result.Y = (a.Z * b.X) - (a.X * b.Z);
  result.Z = (a.X * b.Y) - (a.Y * b.X);
  return result;
}

f32 DotVec2(vec2 a,vec2 b){
  f32 result = 0;
  result = (a.X * b.X) + (a.Y * b.Y);
  return result;
}
f32 DotVec3(vec3 a, vec3 b){
  f32 result = 0;
  result = (a.X * b.X) + (a.Y * b.Y) + (a.Z * b.Z);
  return result;
}
f32 DotVec4(vec4 a, vec4 b){
  f32 result = 0;
  result = (a.X * b.X) + (a.Y * b.Y) + (a.Z * b.Z) + (a.W * b.W);
  return result;
}

vec2 NormalizeVec2(vec2 a){
  vec2 result = {0};
  f32 len = LenVec2(a);
  if (len != 0) {
    result = MulVec2f(a, 1/len);
  }
  return result;
}
vec3 NormalizeVec3(vec3 a){
  vec3 result = {0};
  f32 len = LenVec3(a);
  if (len != 0) {
    result = MulVec3f(a, 1/len);
  }
  return result;
}
vec4 NormalizeVec4(vec4 a){
  vec4 result = {0};
  f32 len = LenVec4(a);
  if (len != 0) {
    result = MulVec4f(a, 1/len);
  }
  return result;
}

f32 LenVec2(vec2 a){
  f32 result = sqrtf(LenSquaredVec2(a));
  return result;
}
f32 LenVec3(vec3 a){
  f32 result = sqrtf(LenSquaredVec3(a));
  return result;
}
f32 LenVec4(vec4 a){
  f32 result = sqrtf(LenSquaredVec4(a));
  return result;
}

f32 LenSquaredVec2(vec2 a){
  f32 result = DotVec2(a, a);
  return result;
}
f32 LenSquaredVec3(vec3 a){
  f32 result = DotVec3(a, a);
  return result;
}
f32 LenSquaredVec4(vec4 a){
  f32 result = DotVec4(a, a);
  return result;
}

mat4 Mat4(){
  mat4 result = {0};
  return result;
}
mat4 Mat4d(f32 s){
  mat4 result = {0};
  result.elems[0][0] = s;
  result.elems[1][1] = s;
  result.elems[2][2] = s;
  result.elems[3][3] = s;
  return result;
}
mat4 Transpose(mat4 m){
  mat4 result = {0};
  for (u8 column = 0; column < 4; column++) {
    for (u8 row = 0; row < 4; row++) {
      result.elems[row][column] = m.elems[column][row];
    }
  }
  return result;
}
mat4 AddMat4(mat4 a, mat4 b){
  mat4 result = {0};
  for (u8 column = 0; column < 4; column++) {
    for (u8 row = 0; row < 4; row++) {
      result.elems[column][row] = a.elems[column][row] + b.elems[column][row];
    }
  }
  return result;
}
mat4 SubMat4(mat4 a, mat4 b){
  mat4 result = {0};
  for (u8 column = 0; column < 4; column++) {
    for (u8 row = 0; row < 4; row++) {
      result.elems[column][row] = a.elems[column][row] - b.elems[column][row];
    }
  }
  return result;
}
mat4 MulMat4(mat4 a, mat4 b){
  mat4 result = {0};
  for (u8 column = 0; column < 4; column++) {
    for (u8 row = 0; row < 4; row++) {
      f32 sum = 0;
      for (u8 matrix = 0; matrix < 4; matrix++) {
	sum += a.elems[matrix][row] * b.elems[column][matrix];
      }
      result.elems[column][row] = sum;
    }
  }


  return result;
}
mat4 MulMat4f(mat4 a, f32 s){
  mat4 result = {0};
  TODO("implement MulMat4f");
  (void)a;
  (void)s;

  return result;
}
mat4 DivMat4f(mat4 a, f32 s){
  mat4 result = {0};
  TODO("implement DivMat4f");
  (void)a;
  (void)s;

  return result;
}

mat4 Translate(vec3 v){
  mat4 result = Mat4d(1);
  result.elems[3][0] = v.X;
  result.elems[3][1] = v.Y;
  result.elems[3][2] = v.Z;
  return result;
}
mat4 Rotate(f32 a, vec3 v){
  mat4 result = Mat4d(1);
  v = NormalizeVec3(v);

  f32 sin_theta = sinf(a);
  f32 cos_theta = cosf(a);
  f32 cos_value = 1.0f - cos_theta;

  result.elems[0][0] = (v.X * v.X * cos_value) + cos_theta;
  result.elems[0][1] = (v.X * v.Y * cos_value) + (v.Z * sin_theta);
  result.elems[0][2] = (v.X * v.Z * cos_value) - (v.Y * sin_theta);

  result.elems[1][0] = (v.Y * v.X * cos_value) - (v.Z * sin_theta);
  result.elems[1][1] = (v.Y * v.Y * cos_value) + cos_theta;
  result.elems[1][2] = (v.Y * v.Z * cos_value) + (v.X * sin_theta);

  result.elems[2][0] = (v.Z * v.X * cos_value) + (v.Y * sin_theta);
  result.elems[2][1] = (v.Z * v.Y * cos_value) - (v.X * sin_theta);
  result.elems[2][2] = (v.Z * v.Z * cos_value) + cos_theta;

  return result;
}
mat4 Scale(vec3 v){
  mat4 result = Mat4d(1);
  result.elems[0][0] = v.X;
  result.elems[1][1] = v.Y;
  result.elems[2][2] = v.Z;
  return result;
}

mat4 Ortho(f32 left, f32 right, f32 bottom, f32 top, f32 near, f32 far){
  mat4 result = {0};
  TODO("implement ortho");
  (void)left;
  (void)right;
  (void)bottom;
  (void)top;
  (void)far;
  (void)near;

  return result;
}
mat4 Persp(f32 fov, f32 aspect, f32 near, f32 far){
  mat4 result = Mat4d(1.0);
  f32 ctg = 1 / tanf(fov * M_PI / 360);

  result.elems[0][0] = ctg / aspect;
  result.elems[1][1] = ctg;
  result.elems[2][3] = -1;
  result.elems[2][2] = (near+far)/(near-far);
  result.elems[3][2] = (2*near*far)/(near-far);
  result.elems[3][3] = 0;

  return result;

}
mat4 LookAt(vec3 eye, vec3 center, vec3 up){
  mat4 result = {0};

  vec3 F = NormalizeVec3(SubVec3(center, eye));
  vec3 S = NormalizeVec3(CrossVec3(F, up));
  vec3 U = CrossVec3(S, F);

  result.elems[0][0] = S.X;
  result.elems[0][1] = U.X;
  result.elems[0][2] = -F.X;
  result.elems[0][3] = 0;

  result.elems[1][0] = S.Y;
  result.elems[1][1] = U.Y;
  result.elems[1][2] = -F.Y;
  result.elems[1][3] = 0;

  result.elems[2][0] = S.Z;
  result.elems[2][1] = U.Z;
  result.elems[2][2] = -F.Z;
  result.elems[2][3] = 0;

  result.elems[3][0] = -DotVec3(S, eye);
  result.elems[3][1] = -DotVec3(U, eye);
  result.elems[3][2] = DotVec3(F, eye);
  result.elems[3][3] = 1;

  return result;
}

void mat4buffer(mat4 m, float *buffer) {
  m = Transpose(m);
  for (u8 column = 0; column < 4; column++) {
    for (u8 row = 0; row < 4; row++) {
      buffer[row * 4 + column] = m.elems[column][row];
    }
  }
}
