#ifndef __SET_SENTINEL_H__
#define __SET_SENTINEL_H__

#include<stddef.h>

#ifndef SET__SIZE
#define SET__SIZE 10
#endif

#define SET__BOUND (void *) 0xdeadbeef // sentinel
#define cannary (void *) 0xeeee

/*struct cursor{
  int* a;
};*/
struct set {
  void* s[SET__SIZE];
  int (*cmp)(const void*,const void *);
  void* (*copy)(void const*);
  void (*del)(void*);
  //struct cursor* c;
  void* a;
};


#include "set.h"

// returns the first position p in s such that s[p]>=c if any, or
// the position of SET__BOUND otherwise.
size_t find(void* const s[], void* c,int (*cmp)(const void *,const void*));

// moves all elements in s starting from position begin and up to
// SET__BOUND included, one position to the right.
// The value in s[begin] is left unchanged.
void shift_right(void* s[], size_t begin);

// moves all elements in s starting from position begin and up to
// SET__BOUND included, one position to the left. 
void shift_left(void* s[], size_t begin);


#endif //__SET_SENTINEL_H__
