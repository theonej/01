#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h>
#include <stdint.h>

void *memset(void *ptr, int c, size_t size);
int memcompare(void *value1, void *value2, int length);

#endif