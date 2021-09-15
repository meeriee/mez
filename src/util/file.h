#ifndef INCLUDE_UTIL_FILE_H
#define INCLUDE_UTIL_FILE_H
#include "mez.h"
#include <stdio.h>

typedef struct File {
  const char *path;
  FILE *fp;
} File;

void FileCreate(File *f);
void FileOpen(File *f, const char *args);
void FileClose(File *f);
void FileStop(File *f);


#endif
