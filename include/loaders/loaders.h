#ifndef BENCHMARK_H
#define BENCHMARK_H

#define ARRAY_SIZE 10000
#define FILE_SIZE (1024 * 1024 * 1024)

#include <stdbool.h>
#include <stdlib.h>

bool RunDeduplicateBenchmark(size_t iterations, size_t threads);

bool RunIoThtpReadBenchmark(size_t iterations, size_t threads);

#endif
