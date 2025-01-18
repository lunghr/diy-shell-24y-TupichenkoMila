#include <loaders/functions.h>

#include <stdio.h>
#include <stdlib.h>

// Unefficient, but ok for benchmarking
int *Deduplicate(int *array, size_t *length) {
  int *deduplicated = (int *)malloc(*length * sizeof(int));
  if (deduplicated == NULL) {
    return NULL;
  }

  size_t deduplicatedLength = 0;

  for (size_t i = 0; i < *length; i++) {
    size_t j;
    for (j = 0; j < deduplicatedLength; j++) {
      if (array[i] == deduplicated[j]) {
        break;
      }
    }

    if (j == deduplicatedLength) {
      deduplicated[deduplicatedLength] = array[i];
      deduplicatedLength++;
    }
  }

  *length = deduplicatedLength;

  return deduplicated;
}

double IoThtpRead(const char *filename) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    return -1;
  }

  char buffer[4096];
  size_t bytesRead;
  size_t totalBytesRead = 0;

  while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
    totalBytesRead += bytesRead;
  }

  fclose(file);

  return (double)totalBytesRead;
}