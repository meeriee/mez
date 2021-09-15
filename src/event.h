#ifndef INCLUDE_EVENT_H
#define INCLUDE_EVENT_H
#include "mez.h"

typedef enum EventType {
  EVENT_NONE,
  EVENT_APP_RENDER, EVENT_APP_UPDATE,
  EVENT_WINDOW_CLOSE, EVENT_WINDOW_MOVE, EVENT_WINDOW_RESIZE,
  EVENT_MOUSE_PRESS, EVENT_MOUSE_RELEASE, EVENT_MOUSE_MOVE, EVENT_MOUSE_SCROLL,
  EVENT_KEY_PRESS, EVENT_KEY_RELEASE, EVENT_KEY_REPEAT,

} EventType;

typedef enum ArgType {
  ARG_END, ARG_PTR,
  ARG_I8, ARG_U8,
  ARG_I16, ARG_U16,
  ARG_I32, ARG_U32,
  ARG_I64, ARG_U64,
  
  ARG_F32, ARG_F64,
} ArgType;

typedef struct EventArg {
  ArgType type;

  union {
    i8 i8data;   u8  u8data;
    i16 i16data; u16 u16data;
    i32 i32data; u32 u32data;
    i64 i64data; u64 u64data;

    f32 f32data; f64 f64data;

    void *ptrdata;
  };
} EventArg;

typedef struct Event {
  EventType type;
  EventArg args[32];
} Event;

typedef void (*EventCallbackFun)(Event);

#endif
