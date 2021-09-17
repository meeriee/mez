#include "shader.h"
#include "renderer.h"
#include <string.h>
#include <stdio.h>

void CompileShader(struct Shader *shader) {
  i32 success = 0; i32 info_length = 0;
  u32 vertex_shader = 0; u32 fragment_shader = 0;
  char *info_log = NULL;

  /* VERTEX */
  vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, (const char**)&shader->vertex_src, NULL);
  glCompileShader(vertex_shader);

  glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
  glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &info_length);
  if (!success) {
    info_log = malloc(info_length);
    glGetShaderInfoLog(vertex_shader, info_length, NULL, info_log);
    ERROR(Renderer, "failed to compile vertex shader\n%s\n", info_log);
    free(info_log);
  } else {
    INFO(Renderer, "successfully compiled vertex shader");
  }

  /* FRAGMENT */
  fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, (const char**)&shader->fragment_src, NULL);
  glCompileShader(fragment_shader);

  glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
  glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &info_length);
  if (!success) {
    info_log = malloc(info_length);
    glGetShaderInfoLog(fragment_shader, info_length, NULL, info_log);
    ERROR(Renderer, "failed to compile fragment shader\n%s\n", info_log);
    free(info_log);
  } else {
    INFO(Renderer, "successfully compiled fragment shader");
  }

  shader->shader_id = glCreateProgram();
  glAttachShader(shader->shader_id, vertex_shader);
  glAttachShader(shader->shader_id, fragment_shader);
  glLinkProgram(shader->shader_id);

  glGetShaderiv(shader->shader_id, GL_COMPILE_STATUS, &success);
  glGetShaderiv(shader->shader_id, GL_INFO_LOG_LENGTH, &info_length);
  if (!success) {
    info_log = malloc(info_length);
    glGetShaderInfoLog(shader->shader_id, info_length, NULL, info_log);
    ERROR(Renderer, "failed to link shader\n%s\n", info_log);
    free(info_log);
  } else {
    INFO(Renderer, "succesfully linked shader");
  }

  glDeleteShader(fragment_shader);
  glDeleteShader(vertex_shader);
}


enum ShaderSourceType {
  SHADER_NONE,
  SHADER_VERTEX,
  SHADER_FRAGMENT
};
#define SOURCE_SIZE_MAX 16384
void ShaderChangeCallback(void *user) {
  struct Shader *shader = user;
  LoadShaderFile(shader, NULL);
  CompileShader(shader);
}
void LoadShaderFile(struct Shader *shader, const char *path) {
  if (path != NULL) shader->file.path = path;

  FileCreate(&shader->file);
  FileOpen(&shader->file, "r");
  char *line = NULL;
  size_t read = 0; size_t len = 0;
  enum ShaderSourceType current = 0;

  char *buffers[3];
  for (enum ShaderSourceType shader_type = SHADER_VERTEX; shader_type <= SHADER_FRAGMENT; shader_type++) {
    buffers[shader_type] = malloc(sizeof(char) * SOURCE_SIZE_MAX);
    memset(buffers[shader_type], 0, sizeof(char) * SOURCE_SIZE_MAX);
  }

  while ((read = getline(&line, &len, shader->file.fp)) != -1) {
    if (line[0] == '@') {
      if (strncmp(line, "@shader", 7) == 0) {
        if (strncmp(line, "@shader vertex", 9) == 0)
	  { current = SHADER_VERTEX; }
        else if (strncmp(line, "@shader fragment", 9) == 0)
	  { current = SHADER_FRAGMENT; }
	else
	  { current = SHADER_NONE; }

	continue;
      }
    }
    strcat(buffers[current], line);
  }
  FileClose(&shader->file);

  free(shader->vertex_src); 	shader->vertex_src = buffers[SHADER_VERTEX];
  free(shader->fragment_src); 	shader->fragment_src = buffers[SHADER_FRAGMENT];
}

void BindShader(struct Shader *shader) {
  glUseProgram(shader->shader_id);
}

void UnbindShader() {
  glUseProgram(0);
}

void ShaderSetInt(struct Shader *shader, struct Uniform uniform, i32 value) {
  if (uniform.loc == 0) { uniform.loc = glGetUniformLocation(shader->shader_id, uniform.name); }
  glUniform1i(uniform.loc, value);
}

void ShaderSetUInt(struct Shader *shader, struct Uniform uniform, u32 value) {
  if (uniform.loc == 0) { uniform.loc = glGetUniformLocation(shader->shader_id, uniform.name); }
  glUniform1ui(uniform.loc, value);
}

void ShaderSetFloat(struct Shader *shader, struct Uniform uniform, f32 value) {
  if (uniform.loc == 0) { uniform.loc = glGetUniformLocation(shader->shader_id, uniform.name); }
  glUniform1f(uniform.loc, value);
}

void ShaderSetVec2	(struct Shader *shader, struct Uniform uniform, vec2 value) {
  if (uniform.loc == 0) { uniform.loc = glGetUniformLocation(shader->shader_id, uniform.name); }
  glUniform2f(uniform.loc, value.X, value.Y);
}
void ShaderSetVec3	(struct Shader *shader, struct Uniform uniform, vec3 value) {
  if (uniform.loc == 0) { uniform.loc = glGetUniformLocation(shader->shader_id, uniform.name); }
  glUniform3f(uniform.loc, value.X, value.Y, value.Y);
}
void ShaderSetVec4	(struct Shader *shader, struct Uniform uniform, vec4 value) {
  if (uniform.loc == 0) { uniform.loc = glGetUniformLocation(shader->shader_id, uniform.name); }
  glUniform4f(uniform.loc, value.X, value.Y, value.Z, value.W);
}

void ShaderSetMat4      (struct Shader *shader, struct Uniform uniform, mat4 value) {
  if (uniform.loc == 0) { uniform.loc = glGetUniformLocation(shader->shader_id, uniform.name); }
  float buffer[16]; mat4buffer(value, buffer);
  glUniformMatrix4fv(uniform.loc, 1, GL_FALSE, buffer);
}


