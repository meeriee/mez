#ifndef INCLUDE_UTIL_ASSERT_H
#define INCLUDE_UTIL_ASSERT_H
#include "mez.h"
#include "debug.h"
#include <signal.h>

#ifdef __linux__
#define BREAK() raise(SIGTRAP);
#endif

#define ASSERT(expr, msg)				\
  if (expr) {						\
  } else {						\
    REPORT_ASSERTION(#expr, __FILE__, __LINE__, msg);	\
  BREAK();						\
  }

#define TODO(msg) REPORT_ASSERTION("", __FILE__, __LINE__, msg);

#endif
