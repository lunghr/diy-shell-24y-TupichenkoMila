#ifndef DEDUPLICATE_H
#define DEDUPLICATE_H

#include <stdlib.h>

// Deduplicate values in an int array
int *Deduplicate(int *array, size_t *length);

// Function to measure read throughput
double IoThtpRead(const char* filename);

#endif
