#include "debug.h"
#include <stdio.h>

void REPORT_ASSERTION(const char *expr, const char *file, i32 line, const char *msg) {
  printf("%s | Assertion failed! %s in %s:%d\n", msg, expr, file, line);
}
