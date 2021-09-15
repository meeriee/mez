#ifndef INCLUDE_MATH_MATH_H
#define INCLUDE_MATH_MATH_H
#include "mez.h"

typedef struct vec2 {
   struct {
    f32 X, Y;
  };
  struct {
    f32 U, V;
  };
  struct {
    f32 W, H;
  };
  f32 elems[2];
} vec2;

typedef struct vec3 {
  struct {
    f32 X, Y, Z;
  };
  struct {
    f32 U, V, W;
  };
  struct {
    f32 R, G, B;
  };
  f32 elems[3];
} vec3;

typedef union vec4 {
  struct {
    union {
      vec3 XYZ;
      struct {
	f32 X, Y, Z;
      };
    };
    f32 W;
  };
  struct {
    union {
      vec3 RGB;
      struct {
	f32 R, G, B;
      };
    };
    f32 A;
  };
  f32 elems[4];
} vec4;

typedef union Quaternion {
  struct {
    union {
      vec3 XYZ;
      struct {
        f32 X, Y, Z;
      };
    };
    f32 W;
  };
  f32 elems[4];
} Quaternion;

typedef union mat4 {
  f32 elems[4][4];
} mat4;

vec2 Vec2 (f32 x, f32 y);
vec2 Vec2i(i32 x, i32 y);
vec3 Vec3 (f32 x, f32 y, f32 z);
vec3 Vec3i(i32 x, i32 y, i32 z);
vec4 Vec4 (f32 x, f32 y, f32 z, f32 w);
vec4 Vec4i(i32 x, i32 y, i32 z, f32 w);
vec4 Vec4v(vec3 v, f32 w);

vec2 AddVec2(vec2 a, vec2 b);
vec3 AddVec3(vec3 a, vec3 b);
vec4 AddVec4(vec4 a, vec4 b);

vec2 SubVec2(vec2 a, vec2 b);
vec3 SubVec3(vec3 a, vec3 b);
vec4 SubVec4(vec4 a, vec4 b);

vec2 MulVec2 (vec2 a, vec2 b);
vec2 MulVec2f(vec2 a, f32 s);
vec3 MulVec3 (vec3 a, vec3 b);
vec3 MulVec3f(vec3 a, f32 s);
vec4 MulVec4 (vec4 a, vec4 b);
vec4 MulVec4f(vec4 a, f32 s);

vec2 DivVec2 (vec2 a, vec2 b);
vec2 DivVec2f(vec2 a, f32 s);
vec3 DivVec3 (vec3 a, vec3 b);
vec3 DivVec3f(vec3 a, f32 s);
vec4 DivVec4 (vec4 a, vec4 b);
vec4 DivVec4f(vec4 a, f32 s);

u8 EqVec2(vec2 a, vec2 b);
u8 EqVec3(vec3 a, vec3 b);
u8 EqVec4(vec4 a, vec4 b);

vec3 CrossVec3(vec3 a, vec3 b);

f32 DotVec2(vec2 a, vec2 b);
f32 DotVec3(vec3 a, vec3 b);
f32 DotVec4(vec4 a, vec4 b);

vec2 NormalizeVec2(vec2 a);
vec3 NormalizeVec3(vec3 a);
vec4 NormalizeVec4(vec4 a);

f32 LenVec2(vec2 a);
f32 LenVec3(vec3 a);
f32 LenVec4(vec4 a);

f32 LenSquaredVec2(vec2 a);
f32 LenSquaredVec3(vec3 a);
f32 LenSquaredVec4(vec4 a);

mat4 Mat4();
mat4 Mat4d(f32 s);
mat4 Transpose(mat4 m);
mat4 AddMat4(mat4 a, mat4 b);
mat4 SubMat4(mat4 a, mat4 b);
mat4 MulMat4(mat4 a, mat4 b);
mat4 MulMat4f(mat4 a, f32 s);
mat4 DivMat4f(mat4 a, f32 s);

mat4 Translate(vec3 v);
mat4 Rotate(f32 a, vec3 v);
mat4 Scale(vec3 v);

mat4 Ortho(f32 left, f32 right, f32 bottom, f32 top, f32 near, f32 far);
mat4 Persp(f32 fov, f32 aspect, f32 near, f32 far);
mat4 LookAt(vec3 eye, vec3 center, vec3 up);

void mat4buffer(mat4 m, f32 *buffer);




#endif
