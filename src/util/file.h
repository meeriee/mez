#ifndef INCLUDE_UTIL_FILE_H
#define INCLUDE_UTIL_FILE_H
#include "mez.h"
#include <stdio.h>

struct File {
  const char *path;
  FILE *fp;
};

void FileCreate(struct File *f);
void FileOpen(struct File *f, const char *args);
void FileClose(struct File *f);
void FileStop(struct File *f);


#endif
