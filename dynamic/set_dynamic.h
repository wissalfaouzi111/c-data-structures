#ifndef __SET_SENTINEL_D__
#define __SET_SENTINEL_D__

#include <stdlib.h>
#include <stdio.h>
#include "set.h"
struct set {
    int *s;
    size_t capacity;
    size_t size;
};

#endif