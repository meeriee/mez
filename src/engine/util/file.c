#include "util/file.h"

void FileCreate(File *f) {
  (void)f;
}

void FileOpen(File *f, const char *args) {
  f->fp = fopen(f->path, args);
}

void FileClose(File *f) {
  fclose(f->fp);
}

void FileStop(File *f) {
  (void)f;
}
