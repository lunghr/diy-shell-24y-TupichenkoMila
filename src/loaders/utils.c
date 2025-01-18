#include <loaders/utils.h>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool CreateFile(const char *filename, size_t size) {
  FILE *file = fopen(filename, "w");
  if (file == NULL) {
    return false;
  }

  char buffer[4096];
  size_t bytesWritten = 0;

  while (bytesWritten < size) {
    size_t bytesToWrite = size - bytesWritten;
    if (bytesToWrite > sizeof(buffer)) {
      bytesToWrite = sizeof(buffer);
    }

    size_t written = fwrite(buffer, 1, bytesToWrite, file);
    if (written == 0) {
      fclose(file);
      return false;
    }

    bytesWritten += written;
  }

  fclose(file);

  return true;
}

bool DeleteFile(const char *filename) { return remove(filename) == 0; }
