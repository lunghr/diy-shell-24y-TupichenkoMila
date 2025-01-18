#include <loaders/functions.h>
#include <loaders/loaders.h>
#include <loaders/utils.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <stdio.h>

#undef CreateFile
#undef DeleteFile

#define MAX_THREADS 64

typedef struct {
  size_t iterations;
  size_t thread_id;
} ThreadParams;

DWORD WINAPI DeduplicateWorker(LPVOID param) {
  ThreadParams *params = (ThreadParams *)param;
  int *array = (int *)malloc(ARRAY_SIZE * sizeof(int));
  if (array == NULL)
    return 1;

  for (size_t i = 0; i < ARRAY_SIZE; i++) {
    array[i] = rand() % ARRAY_SIZE;
  }

  for (size_t i = 0; i < params->iterations; i++) {
    size_t length = ARRAY_SIZE;
    int *array_copy = (int *)malloc(ARRAY_SIZE * sizeof(int));
    memcpy(array_copy, array, ARRAY_SIZE * sizeof(int));
    int *deduplicated = Deduplicate(array_copy, &length);
    free(deduplicated);
    free(array_copy);
  }
  free(array);
  return 0;
}

bool RunDeduplicateBenchmark(size_t iterations, size_t threads) {
  if (threads > MAX_THREADS)
    threads = MAX_THREADS;

  HANDLE handles[MAX_THREADS];
  ThreadParams params[MAX_THREADS];

  for (size_t i = 0; i < threads; i++) {
    params[i].iterations = iterations / threads;
    params[i].thread_id = i;
    handles[i] = CreateThread(NULL, 0, DeduplicateWorker, &params[i], 0, NULL);
  }

  WaitForMultipleObjects(threads, handles, TRUE, INFINITE);

  for (size_t i = 0; i < threads; i++) {
    CloseHandle(handles[i]);
  }

  return true;
}

DWORD WINAPI IoThtpReadWorker(LPVOID param) {
  ThreadParams *params = (ThreadParams *)param;
  for (size_t i = 0; i < params->iterations; i++) {
    IoThtpRead("iotest.dat");
  }
  return 0;
}

bool RunIoThtpReadBenchmark(size_t iterations, size_t threads) {
  if (threads > MAX_THREADS)
    threads = MAX_THREADS;

  CreateFile("iotest.dat", FILE_SIZE);

  HANDLE handles[MAX_THREADS];
  ThreadParams params[MAX_THREADS];

  for (size_t i = 0; i < threads; i++) {
    params[i].iterations = iterations / threads;
    params[i].thread_id = i;
    handles[i] = CreateThread(NULL, 0, IoThtpReadWorker, &params[i], 0, NULL);
  }

  WaitForMultipleObjects(threads, handles, TRUE, INFINITE);

  for (size_t i = 0; i < threads; i++) {
    CloseHandle(handles[i]);
  }

  DeleteFile("iotest.dat");
  return true;
}
