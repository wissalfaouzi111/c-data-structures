#ifndef __SET_LINK__
#define __SET_LINK__

#include "set.h"

struct link;

struct set {
  struct link *l;
};

// Returns NULL if l is empty, or if f is smaller than or equal to the first 
// value in l
// Otherwise, returns the cell e such that:
// - f is the data of the next cell of e,
// - or f should be inserted after e (if e is not in l)
// pre-condition: l is sorted in increasing order
struct lelement * find(struct link *l, int f);

void link_free(struct link* l);
#endif /* __SET_LINK__ */
