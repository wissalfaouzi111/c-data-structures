#include <assert.h>
#include <stdio.h>
#include "set_sentinel.h"
#include <stdlib.h>

int cmp_int(const void* a,const void* b){
  return (*((int*)a)) - (*((int*)b));
}

void* copy_int(void const *p){
  int *res=malloc(sizeof(int));
  *res = *((int*)p);
  return res;
}

void del_int(void* p){
  free(p);
}

void print_int(void* n){
  printf("%p\n",n);
}

static void test_set__print(void){
  printf("%s\n", __func__);
  struct set* s1=set__empty(cmp_int,copy_int,del_int);
  set__print(s1,print_int);
  int v[4]={2,3,8,9};
  for (int i=0;i<4;i++){
    s1->s[i]=&v[i];
  }
  s1->s[4]=SET__BOUND;
  set__print(s1,print_int);
  struct set* s2=set__empty(cmp_int,copy_int,del_int);
  set__print(s2,print_int);
  printf("test_valide :)\n\n"); 
}

/*
static void test_find(void){
  printf("%s\n", __func__);
  //
  int v[]={10,3}
  struct set s1={{2,3,8,9,-1}};
  assert(find(s1.s,&v[0])==4);
  assert(find(s1.s,&v[1])==1); 
  //
  struct set s2={{}};
  for (size_t i =0;i<SET__SIZE;i++ ){
    s2.s[i]=i;
  }
  assert(find(s2.s,SET__SIZE+1)==SET__SIZE);
  //
  struct set s3={{-1}};
  assert(find(s3.s,3)==0);
  printf("test_valide:)\n\n"); 
}

static void test_shift_right(void){
  printf("%s\n", __func__);
  struct set s1={{1,3,4,6,10,-1}};
  printf("Avant:");
  set__print(&s1);
  shift_right(s1.s,2);
  printf("Après:");
  set__print(&s1);  
  printf("test_valide:)\n\n");   
}

static void test_shift_left(void){
  printf("%s\n", __func__);
  struct set s1={{1,3,4,6,10,-1}};
  printf("Avant:");
  set__print(&s1);
  shift_left(s1.s,2);
  printf("Après:"); 
  set__print(&s1); 
  printf("test_valide:)\n\n");   
}
static void test_set__find(void){
  printf("%s\n", __func__);
  struct set s1={{2,3,8,9,-1}};
  assert(set__find(&s1,3)==1);
  assert(set__find(&s1,11)==0);
  printf("test_valide:)\n\n");   
}

static void test_set_empty(void){
  printf("%s\n", __func__);
  struct set *se = set__empty();
  set__print(se);
  set__free(se);
  printf("test_valide:)\n\n");    
}

static void test_set__size(void){
  printf("%s\n", __func__);
  struct set s1={{2,3,8,9,-1}};
  set__print(&s1);
  printf("size: %ld\n",set__size(&s1));
  struct set s2={{}};
  set__print(&s2);
  printf("size: %ld\n",set__size(&s2));
  struct set s3={{-1}};
  set__print(&s3);
  printf("size: %ld\n",set__size(&s3));
  printf("test_valide:)\n\n");    
}

static void test_set__is_empty(void){
  printf("%s\n", __func__);
  struct set s1={{2,3,8,9,-1}};
  set__print(&s1);
  printf("s1 est %s\n",set__is_empty(&s1) ? "vide" : "non vide");
  struct set *s2=set__empty();
  set__print(s2);
  printf("s2 est %s\n",set__is_empty(s2) ? "vide" : "non vide");
  set__free(s2);
  printf("test_valide:)\n\n");    
}

static void test_set__add(void){
  printf("%s\n", __func__);
  struct set s1={{2,3,8,9,-1}};
  assert(set__add(&s1,3)==-1);
  assert(set__add(&s1,4)==0);
  assert(set__add(&s1,10)==0);
  assert(set__add(&s1,-2)==-1);

  struct set s2={{}};
  for (size_t i=0;i<SET__SIZE;i++){
    s2.s[i]=i;
  }
  assert(set__add(&s2,SET__SIZE)==-1);  
  printf("test_valide:)\n\n");    
}

static void test_set__remove(void){
  printf("%s\n",__func__);
  struct set s1={{2,3,8,9,-1}};
  assert(set__remove(&s1,1)==-1);
  assert(set__remove(&s1,3)==0);
  assert(set__remove(&s1,-2)==-1);

  struct set s2={{-1}};
  assert(set__remove(&s2,1)==-1);  
  printf("test_valide:)\n\n");     
}

static void test_set__remove_with_shift (void) {
  printf("%s", __func__);
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
  
  
  printf("\tnot yet\n");
}
int is_even(int a){
  return a%2 == 0;
}

void test_set_filter(void){
  printf("%s\n",__func__);
  struct set* s=set__empty();
  for (size_t i=0;i<SET__SIZE;i++){
    set__add(s,i);
  }
  set__print(s);
  struct set* res=set__filter(s,is_even);
  set__print(res);
  set__free(s);
  set__free(res);
  printf("\tOK\n");
}*/

int main () {
  printf("%s\n", __FILE__);
  test_set__print();
  /*test_shift_right();
  test_shift_left();
  test_set__remove_with_shift();
  test_find();
  test_set__find();
  test_set_empty();
  test_set__size();
  test_set__is_empty();
  test_set__add();
  test_set__remove();
  test_set_filter();*/
  return 0;
}
