#include "util/file.h"

void FileCreate(struct File *f) {
  (void)f;
}

void FileOpen(struct File *f, const char *args) {
  f->fp = fopen(f->path, args);
}

void FileClose(struct File *f) {
  fclose(f->fp);
}

void FileStop(struct File *f) {
  (void)f;
}
