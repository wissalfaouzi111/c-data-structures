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
  printf("%p  ",n);
}

static void test_set_empty(void){
  printf("%s\n", __func__);
  struct set *se = set__empty(cmp_int,copy_int,del_int);
  set__print(se,print_int);
  free(se);
  printf("test_valide:)\n\n");    
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
  free(s1);
  printf("test_valide :)\n\n"); 
}

static void test_set__size(void){
  printf("%s\n", __func__);
  struct set* s1=set__empty(cmp_int,copy_int,del_int);
  set__print(s1,print_int);
  printf("size: %ld\n\n",set__size(s1));
  int v[4]={2,3,8,9};
  for (int i=0;i<4;i++){
    s1->s[i]=&v[i];
  }
  s1->s[4]=SET__BOUND;
  set__print(s1,print_int);
  printf("size: %ld\n",set__size(s1)); 
  free(s1); 
  printf("test_valide:)\n\n");    
}

static void test_set__is_empty(void){
  printf("%s\n", __func__);
  struct set* s1=set__empty(cmp_int,copy_int,del_int);
  set__print(s1,print_int);
  printf("s1 est %s\n",set__is_empty(s1) ? "vide" : "non vide");
  int v[4]={2,3,8,9};
  for (int i=0;i<4;i++){
    s1->s[i]=&v[i];
  }
  s1->s[4]=SET__BOUND;
  set__print(s1,print_int);
  printf("s1 est %s\n",set__is_empty(s1) ? "vide" : "non vide");
  free(s1);
  printf("test_valide:)\n\n");    
}

static void test_find(void){
  printf("%s\n", __func__);
  //
  struct set* s1=set__empty(cmp_int,copy_int,del_int);
  int v1[3]={10,3,SET__SIZE+1};
  assert(find(s1->s,&v1[0],cmp_int)==0);
  int v[4]={2,3,8,9};
  for (int i=0;i<4;i++){
    s1->s[i]=&v[i];
  }
  s1->s[4]=SET__BOUND;
  assert(find(s1->s,&v1[0],cmp_int)==4);
  assert(find(s1->s,&v1[1],cmp_int)==1); 
  int v2[SET__SIZE];
  struct set *s2=set__empty(cmp_int,copy_int,del_int);
  for (size_t i =0;i<SET__SIZE;i++ ){
    v2[i]=i;
  }
  for (int i=0;i<SET__SIZE;i++){
    s2->s[i]=&v2[i];
  }
  s2->s[SET__SIZE]=SET__BOUND;
  assert(find(s2->s,&v1[2],cmp_int)==SET__SIZE);
  free(s1);
  free(s2);
  printf("test_valide:)\n\n"); 
}

static void test_set__find(void){
  printf("%s\n", __func__);
  struct set* s1=set__empty(cmp_int,copy_int,del_int);
  int v[4]={2,3,8,9};
  for (int i=0;i<4;i++){
    s1->s[i]=&v[i];
  }
  s1->s[4]=SET__BOUND;

  int v1[4]={4,3,11,-1};
  assert(set__find(s1,&v1[1])==1);
  assert(set__find(s1,&v1[2])==0);
  assert(set__find(s1,&v1[3])==0);
  assert(set__find(s1,&v1[0])==0);
  free(s1);
  printf("test_valide:)\n\n");   
}


static void test_shift_right(void){
  printf("%s\n", __func__);
  struct set* s1=set__empty(cmp_int,copy_int,del_int);
  int v[4]={2,3,8,9};
  for (int i=0;i<4;i++){
    s1->s[i]=&v[i];
  }
  s1->s[4]=SET__BOUND;
  printf("Avant:");
  set__print(s1,print_int);
  shift_right(s1->s,2);
  printf("Après:");
  set__print(s1,print_int);
  free(s1);
  printf("test_valide:)\n\n");   
}

static void test_shift_left(void){
  printf("%s\n", __func__);
  struct set* s1=set__empty(cmp_int,copy_int,del_int);
  int v[4]={2,3,8,9};
  for (int i=0;i<4;i++){
    s1->s[i]=&v[i];
  }
  s1->s[4]=SET__BOUND;
  printf("Avant:");
  set__print(s1,print_int);
  shift_left(s1->s,2);
  printf("Après:"); 
  set__print(s1,print_int);
  free(s1);
  printf("test_valide:)\n\n");   
}






static void test_set__add(void){
  printf("%s\n", __func__);
  struct set* s1=set__empty(cmp_int,copy_int,del_int);
  set__print(s1,print_int);
  int v[4]={2,3,8,9};
  for (int i=0;i<4;i++){
    assert(set__add(s1,&v[i])==0);;
  }
  int v1[3]={3,4,10};
  assert(set__add(s1,&v1[0])==-1);
  assert(set__add(s1,&v1[1])==0);
  set__print(s1,print_int);
  assert(set__add(s1,&v1[2])==0);
  printf("Après avoir ajouté les adresses:");
  set__print(s1,print_int);


  struct set* s2=set__empty(cmp_int,copy_int,del_int);
  int v2[SET__SIZE];
  for (size_t i=0;i<SET__SIZE;i++){
    v2[i]=i;
  }
  for (size_t i=0;i<SET__SIZE-1;i++){
    assert(set__add(s2,&v2[i])==0);
  }
  assert(set__add(s2,&v2[SET__SIZE])==-1); 
  set__free(s1); 
  set__free(s2); 
  printf("test_valide:)\n\n");    
}

static void test_set__remove(void){
  printf("%s\n",__func__);
  struct set* s1=set__empty(cmp_int,copy_int,del_int);
  int v[4]={2,3,8,9};
  for (int i=0;i<4;i++){
    assert(set__add(s1,&v[i])==0);
  }
  int v1[3]={1,3,-2};
  assert(set__remove(s1,&v1[0])==-1);
  assert(set__remove(s1,&v1[1])==0);
  assert(set__remove(s1,&v1[2])==-1);

  struct set *s2=set__empty(cmp_int,copy_int,del_int);
  assert(set__remove(s2,&v1[0])==-1); 


  //ajouter puis enlever un élèment
  struct set* s3=set__empty(cmp_int,copy_int,del_int);
  assert(set__add(s3,&v[0])==0);
  assert(set__remove(s3,&v[0])==0);
  set__free(s1); 
  set__free(s3); 
  set__free(s2); 
  printf("test_valide:)\n\n");     
}

static void test_set__remove_with_shift (void) {
  printf("%s", __func__);
  struct set* st=set__empty(cmp_int,copy_int,del_int);
  int v[4]={1,2,3,4};
  for (int i=0;i<4;i++){
    assert(set__add(st,&v[i])==0);
  }

  set__remove(st, &v[2]);
  assert(st->cmp(st->s[0],&v[0])==0);
  assert(st->cmp(st->s[1],&v[1])==0);
  assert(st->cmp(st->s[2],&v[3])==0);
  assert(st->s[3]==SET__BOUND);

  set__remove(st, &v[3]);
  assert(st->cmp(st->s[0],&v[0])==0);
  assert(st->cmp(st->s[1],&v[1])==0);
  assert(st->s[2] == SET__BOUND);

  set__remove(st,&v[0]);
  assert(st->cmp(st->s[0],&v[1])==0);
  assert(st->s[1] == SET__BOUND);

  set__remove(st,&v[1]);
  assert(st->s[0] == SET__BOUND);
  set__free(st); 
  
  printf("\tOK\n\n");
  
}
int is_even(void* a){
  return (*(int *)a)%2 == 0;
}
/*
void test_set_filter(void){
  printf("%s\n",__func__);
  struct set* s=set__empty(cmp_int,copy_int,del_int);
  int v[SET__SIZE];
  for (size_t i=0;i<SET__SIZE;i++){
    v[i]=i;
    assert(set__add(s,&v[i]));
  }
  set__print(s,print_int);
  struct set* res=set__filter(s,is_even);
  set__print(res,print_int);
  set__free(s);
  set__free(res);
  printf("\tOK\n");
}*/

static void test_cursor_fst(){
  printf("%s", __func__);
  struct set* st=set__empty(cmp_int,copy_int,del_int);
  int v[4]={1,2,3,4};
  for (int i=0;i<4;i++){
    assert(set__add(st,&v[i])==0);
  }
  assert(st->s[0]==cursor_fst(st));
  printf("\tOK\n\n");
}

static void test_cursor_next(){
  printf("%s", __func__);
  struct set* st=set__empty(cmp_int,copy_int,del_int);
  int v[4]={1,2,3,4};
  
  assert(NULL==cursor_next(st,&v[0]));
  
  for (int i=0;i<4;i++){
    assert(set__add(st,&v[i])==0);
  }
  
  assert(st->s[2]==cursor_next(st,&v[1]));
  assert(SET__BOUND==cursor_next(st,&v[3]));
  assert(NULL==cursor_next(st,&v[4]));
  printf("\tOK\n\n");
}
/*
static void test_cursor_end(){
  printf("%s", __func__);
  struct set* st=set__empty(cmp_int,copy_int,del_int);
  int v[4]={1,2,3,4};
  for (int i=0;i<4;i++){
    assert(set__add(st,&v[i])==0);
  }
}*/
int main () {
  printf("%s\n", __FILE__);
  test_set__print();
  test_find();
  test_set__find();
  test_set_empty();
  test_set__size();
  test_set__is_empty();
  test_shift_right();
  test_shift_left();
  test_set__add();
  test_set__remove();

  test_set__remove_with_shift();
  test_cursor_fst();
  test_cursor_next();
  
  //test_set_filter();
  return 0;
}
