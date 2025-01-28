#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "link.h"

/*static void test_llm__is_end_mark(void){
  printf("\n%s\n",__func__);
  struct lelement e ;
  e.data= __INT_MAX__;
  e.next=(struct lelement *) &e;
  assert(llm__is_end_mark(&e)==0);
  struct lelement e1 ;
  struct lelement next_e1 ;
  e1.data= 11;
  e1.next=&next_e1;
  assert(llm__is_end_mark(&e1)==0);
  printf("test valid :)\n\n");
}*/


int main () {
  printf("%s\n", __FILE__);
  return EXIT_SUCCESS;
}
