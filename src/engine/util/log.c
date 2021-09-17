#include "log.h"
#include <time.h>
#include <stdio.h>

Channel channels[64] = {0};
u8 channel_c = 0;

#define FORMAT "[%s] (%5s) (%10s) - %s"
#define BUFFERMAX 8192

char *VLogS(LogLevel level, Channel ch, char *format, va_list args) {
  static char Message[BUFFERMAX], Buffer[BUFFERMAX*2];
  vsnprintf(Message, BUFFERMAX, format, args);

  const char *LevelSTR;
  switch (level) {
    case LOG_TRACE:
      LevelSTR = "TRACE";
      break;
    case LOG_INFO:
      LevelSTR = "INFO";
      break;
    case LOG_WARN:
      LevelSTR = "WARN";
      break;
    case LOG_ERROR:
      LevelSTR = "ERROR";
      break;
    case LOG_FATAL:
      LevelSTR = "FATAL";
      break;
    default:
      LevelSTR = "";
      break;
  }

  time_t now; time(&now);
  char TimeSTR[sizeof "00:00:00"];
  strftime(TimeSTR, sizeof TimeSTR, "%T", gmtime(&now));

  snprintf(Buffer, BUFFERMAX*2, FORMAT, TimeSTR, LevelSTR, ch.name, Message);
  return Buffer;
}

void Log(LogLevel level, Channel ch, char *format, ...) {
  va_list args;
  va_start(args,format);
  char *l = VLogS(level, ch, format, args);
  va_end(args);

  printf("%s\n", l);
}

Channel CreateChannel(char *name) {
  Channel c;
  c.ID = channel_c;
  c.name = name;
  channel_c++;
  channels[channel_c] = c;

  printf("created channel %s\n", name);
  return c;
}
