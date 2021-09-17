#include "renderer.h"
#include "ui/gl.h"

void CreateVertexBuffer(VertexBuffer *vbo, u32 size, const f32 *data) {
  glGenBuffers(1, &vbo->ID);
  BindVertexBuffer(vbo);
  glBufferData(GL_ARRAY_BUFFER, size*sizeof(float), data, GL_STATIC_DRAW);
}

void BindVertexBuffer(VertexBuffer *vbo) {
  if (vbo->ID > 0)
    glBindBuffer(GL_ARRAY_BUFFER, vbo->ID);
}
void UnbindVertexBuffer() {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void CreateIndexBuffer(IndexBuffer *vbo, u32 size, const u32 *data) {
  glGenBuffers(1, &vbo->ID);
  BindIndexBuffer(vbo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size*sizeof(u32), data, GL_STATIC_DRAW);
}

void BindIndexBuffer(IndexBuffer *vbo) {
  if (vbo->ID > 0)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo->ID);
}
void UnbindIndexBuffer() {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void VertexArrayAdd(VertexArray *va, struct VertexArrayElement e) {
  if (va->element_count == 128) return;
  va->elements[va->element_count++] = e;
}

void CreateVertexArray(VertexArray *va) {
  glGenVertexArrays(1, &va->ID);
  BindVertexArray(va);
}
void MakeVertexArray(VertexArray *va) {
  BindVertexArray(va);
  u64 stride = 0, offset = 0;
  // TODO implement other types of vertex array elements
  for (u32 i = 0; i < va->element_count; i++) stride += sizeof(float) * va->elements[i].count;
  for (u32 i = 0; i < va->element_count; i++) {
    struct VertexArrayElement e = va->elements[i];
    glVertexAttribPointer(i, e.count, e.type, e.normalized, stride, (void*)offset);
    offset += e.count * sizeof(float);
    glEnableVertexAttribArray(i);
  }
}
void BindVertexArray(VertexArray *va) {
  glBindVertexArray(va->ID);
}
void UnbindVertexArray() {
  glBindVertexArray(0);
}

void InitRenderer() {
  Renderer = CreateChannel("renderer");
}
