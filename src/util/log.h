#ifndef INCLUDE_UTIL_LOG_H
#define INCLUDE_UTIL_LOG_H
#include "mez.h"
#include <stdarg.h>

typedef struct Channel {
  u8 ID;
  char *name;
} Channel;

typedef enum LogLevel {
  LOG_TRACE,
  LOG_INFO,
  LOG_WARN,
  LOG_ERROR,
  LOG_FATAL,
} LogLevel;

void Log(LogLevel level, Channel ch, char *format, ...);

#define LOG(level, ch, ...) Log(level, ch, format, __VA_ARGS__)

#define TRACE(ch, ...) Log(LOG_TRACE, ch, __VA_ARGS__)
#define INFO(ch, ...)  Log(LOG_INFO,  ch, __VA_ARGS__)
#define WARN(ch, ...)  Log(LOG_WARN,  ch, __VA_ARGS__)
#define ERROR(ch, ...) Log(LOG_ERROR, ch, __VA_ARGS__)
#define FATAL(ch, ...) Log(LOG_FATAL, ch, __VA_ARGS__)

Channel CreateChannel(char *name);

#endif
