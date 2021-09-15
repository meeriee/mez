#ifndef INCLUDE_UI_RENDERER_H
#define INCLUDE_UI_RENDERER_H
#include "mez.h"
#include "ui/render/shader.h"
#include "ui/render/framebuffer.h"
#include "util/log.h"

static Channel Renderer;

typedef struct VertexBuffer {
  u32 ID;
} VertexBuffer;
void CreateVertexBuffer(struct VertexBuffer *vbo, u32 size, const f32 *data);
void BindVertexBuffer(struct VertexBuffer *vbo);
void UnbindVertexBuffer();

typedef struct IndexBuffer {
  u32 ID;
} IndexBuffer;
void CreateIndexBuffer(struct IndexBuffer *vbo, u32 size, const u32 *data);
void BindIndexBuffer(struct IndexBuffer *vbo);
void UnbindIndexBuffer();

typedef struct VertexArrayElement {
  u32 type;
  u32 count;
  u32 normalized;
} VertexArrayElement;
typedef struct VertexArray {
  u32 ID;
  struct VertexArrayElement elements[128];
  u32 element_count;
} VertexArray;

void VertexArrayAdd(struct VertexArray *va, struct VertexArrayElement e);
void CreateVertexArray(struct VertexArray *va);
void MakeVertexArray(struct VertexArray *va);
void BindVertexArray(struct VertexArray *va);
void UnbindVertexArray();

typedef struct RendererStats {
  u64 drawcalls;
  u64 quads;
} RendererStats;

//RendererStats g_Stats;

void InitRenderer();
void ShutdownRenderer();

#endif

