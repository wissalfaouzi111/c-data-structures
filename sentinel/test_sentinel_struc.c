#include <assert.h>
#include <stdio.h>

#include "set_sentinel.h"

static void test_set__remove_with_shift (void) {
  printf("%s", __func__);
  /*
  struct set st = {{1,2,3,4, SET__BOUND}};

  set__remove(&st, 3);
  assert(st.s[0] == 1);
  assert(st.s[1] == 2);
  assert(st.s[2] == 4);
  assert(st.s[3] == SET__BOUND);

  set__remove(&st, 4);
  assert(st.s[0] == 1);
  assert(st.s[1] == 2);
  assert(st.s[2] == SET__BOUND);

  set__remove(&st, 1);
  assert(st.s[0] == 2);
  assert(st.s[1] == SET__BOUND);

  set__remove(&st, 2);
  assert(st.s[0] == SET__BOUND);

  printf("\tOK\n");
  */
  
  printf("\tnot yet\n");
}

int main () {
  printf("%s\n", __FILE__);

  test_set__remove_with_shift();
  return 0;
}
