#include "set_dynamic.h"
 
static void test_set__print(void){
    printf("%s\n",__func__);
    int s[]={1,2,3,4,5};
    struct set s1={s,8,4};
    set__print(&s1);
    printf("test_valide:)\n\n");    
}

static void test_set_empty(void){
  printf("%s\n", __func__);
  struct set se = set__empty();
  set__print(&se);
  printf("test_valide:)\n\n");    
}

static void test_set__is_empty(void){
  printf("%s\n", __func__);
  int s[]={1,2,3,4,5};
  struct set s1={s,8,4};
  set__print(&s1);
  printf("s1 est %s\n",set__is_empty(&s1) ? "vide" : "non vide");
  struct set s2=set__empty();;
  set__print(&s2);
  printf("s2 est %s\n",set__is_empty(&s2) ? "vide" : "non vide");
  printf("test_valide:)\n\n");    
}
/*static void test_set__add(void){
    
}*/

int main(){
    test_set__print();
    test_set_empty();
    test_set__is_empty();
}