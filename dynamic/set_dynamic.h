#ifndef __SET_SENTINEL_D__
#define __SET_SENTINEL_D__

#include <stdlib.h>
#include <stdio.h>
#include "set.h"

struct set {
    void* *s;
    size_t capacity;
    size_t size;
    int (*cmp)(const void*,const void *);
    void* (*copy)(void const*);
    void (*del)(void*);
};

// returns the first position p in s such that s[p]>=c
// or size if no such p exists
size_t find(void* const s[], size_t size, void* c,int (*cmp)(const void*,const void*));

// moves elements in s[begin..end[ to s[begin+1..end+1[
// assuming all indices are valid, s[begin] is left unchanged
void shift_right(void* s[], size_t begin, size_t end);

// moves elements in s[begin..end[ tp [begin-1..end-1[
// assuming all indices are valid, s[end-1] is left unchanged
void shift_left(void* s[], size_t begin, size_t end);

#endif