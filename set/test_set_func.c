#include <assert.h>
#include <stdio.h>

#include "set.h"

static void test_create_set(void) {
  printf("%s", __func__);
  
  struct set * st = set__empty();

  assert(set__is_empty(st));
  assert(set__size(st) == 0);
  assert(! set__find(st, 11));
  set__add(st,12);
  set__add(st,13);
  set__add(st,13);
  assert(set__add(st,13)==-1);
  assert(set__remove(st, 78) != 0);

  set__free(st);

  printf("\tOK\n");
}

int main(void) {
  printf("%s\n", __FILE__);

  test_create_set();

  return 0;
}
