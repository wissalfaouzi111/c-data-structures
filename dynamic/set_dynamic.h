#ifndef __SET_SENTINEL_D__
#define __SET_SENTINEL_D__

#include <stdlib.h>
#include <stdio.h>

struct set {
    int *s;
    size_t capacity;
    size_t size;
};

void set__print(struct set* se);

#endif