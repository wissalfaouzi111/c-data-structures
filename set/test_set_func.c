#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

  printf("\tOK\n\n");
}




//cas de struct person

struct person {
  char * firstname;
  char * lastname;
  unsigned int year;
  unsigned char month;
  unsigned char day;
};

int cmp_person(const void*a,const void *b){
  const struct person *p1=a;
  const struct person *p2=b;
  int cmp_firstname=strcmp(p1->firstname,p2->firstname);
  if (cmp_firstname!=0){
    return cmp_firstname;
  }
  int cmp_lastname=strcmp(p1->lastname,p2->lastname);
  if (cmp_lastname!=0){
    return cmp_lastname;
  }
  if (p1->year != p2->year){
    return p1->year - p2->year;
  }
  if (p1->month != p2->month){
    return p1->month - p2->month;
  }
  return p1->day - p2->day;
}

void* copy_person(void const *p){
  struct person *res=malloc(sizeof(struct person));
  *res=*((struct person *)p);
  return res;
}


//Adding removing a struct person to and from an empty set
void test_add_remove_person(void){
  printf("%s", __func__);
  struct set * st = set__empty(cmp_person,copy_person,del_int);
  struct person p={"wissal","faouzi",2004,12,20};
  
  assert(set__add(st,&p)==0);
  assert(set__remove(st,&p)==0);
  set__free(st);
  printf("\tOK\n");
}

int main(void) {
  printf("%s\n", __FILE__);

  test_create_set();
  test_add_remove_person();
  return 0;
}
