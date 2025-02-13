#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "set.h"
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

static void test_create_set(void) {
  printf("%s", __func__);
  int v[4]={11,12,13,78};
  struct set * st = set__empty(cmp_int,copy_int,del_int);

  assert(set__is_empty(st));
  assert(set__size(st) == 0);
  assert(! set__find(st, &v[0]));
  set__add(st,&v[1]);

  //ajouter le même élément à un ensemble non vide.
  set__add(st,&v[2]);
  set__add(st,&v[2]);
  assert(set__add(st,&v[2])==-1);
  assert(set__remove(st, &v[3]) != 0);

  set__free(st);

  printf("\tOK\n");
}

struct person {
  char * firstname;
  char * lastname;
  unsigned int year;
  unsigned char month;
  unsigned char day;
};


//Adding a struct person to and from an empty set
void test_add_person(void){
  struct set * st = set__empty(cmp_int,copy_int,del_int);
  struct person p={"wissal","faouzi",2004,12,20};
  assert(set__add(st,&p)==0);
  set__free(st);
}

int main(void) {
  printf("%s\n", __FILE__);

  test_create_set();

  return 0;
}
