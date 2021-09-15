#ifndef INCLUDE_UI_SHADER_H
#define INCLUDE_UI_SHADER_H
#include "mez.h"
#include "math/math.h"
#include "util/file.h"
#include "renderer.h"

typedef struct Shader {
  char *vertex_src, *fragment_src;
  struct File file;
  u32 shader_id;
} Shader;

typedef struct Uniform {
  const char *name;
  i32 loc;
} Uniform;

void CompileShader(struct Shader *shader);
void LoadShaderFile(struct Shader *shader, const char *path);
void BindShader(struct Shader *shader);
void UnbindShader();

void ShaderSetInt   (struct Shader *shader, struct Uniform uniform, i32 value);
void ShaderSetUInt  (struct Shader *shader, struct Uniform uniform, u32 value);
void ShaderSetFloat (struct Shader *shader, struct Uniform uniform, f32 value);

void ShaderSetVec2  (struct Shader *shader, struct Uniform uniform, vec2 value);
void ShaderSetVec3  (struct Shader *shader, struct Uniform uniform, vec3 value);
void ShaderSetVec4  (struct Shader *shader, struct Uniform uniform, vec4 value);
void ShaderSetMat4  (struct Shader *shader, struct Uniform uniform, mat4 value);

#endif
