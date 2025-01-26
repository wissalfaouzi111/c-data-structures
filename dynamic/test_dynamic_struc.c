#include "set_dynamic.h"
#include <assert.h>


static void test_set__print(void){
  printf("%s\n",__func__);
  struct set s1;
  s1.capacity=4;
  s1.size=4;
  s1.s=malloc(s1.capacity * sizeof(int));
  s1.s[0]=2;
  s1.s[1]=3;
  s1.s[2]=8;
  s1.s[3]=9;
  set__print(&s1);
  free(s1.s);
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
  //créer une structure pour les tests
  struct set s1;
  s1.capacity=4;
  s1.size=4;
  s1.s=malloc(s1.capacity * sizeof(int));
  s1.s[0]=2;
  s1.s[1]=3;
  s1.s[2]=8;
  s1.s[3]=9;
  set__print(&s1);
  printf("s1 est %s\n",set__is_empty(&s1) ? "vide" : "non vide");
  struct set s2=set__empty();;
  set__print(&s2);
  printf("s2 est %s\n",set__is_empty(&s2) ? "vide" : "non vide");
  printf("test_valide:)\n\n");
  free(s1.s);    
}

static void test_set__size(void){
  printf("%s\n", __func__);
  struct set s1;
  s1.capacity=4;
  s1.size=4;
  s1.s=malloc(s1.capacity * sizeof(int));
  s1.s[0]=2;
  s1.s[1]=3;
  s1.s[2]=8;
  s1.s[3]=9;
  set__print(&s1);
  printf("size: %ld\n",set__size(&s1));

  struct set s3=set__empty();
  set__print(&s3);
  printf("size: %ld\n",set__size(&s3));
  free(s1.s);
  printf("test_valide:)\n\n");    
}

static void test_find(void){
  printf("%s\n", __func__);
  //
  struct set s1;
  s1.capacity=4;
  s1.size=4;
  s1.s=malloc(s1.capacity * sizeof(int));
  s1.s[0]=2;
  s1.s[1]=3;
  s1.s[2]=8;
  s1.s[3]=9;
  assert(find(s1.s,set__size(&s1),10)==set__size(&s1));
  assert(find(s1.s,set__size(&s1),3)==1); 
  assert(find(s1.s,set__size(&s1), 0) == 0);
  //
  struct set s3=set__empty();
  assert(find(s3.s,set__size(&s3),1)==set__size(&s3));
  free(s1.s);
  printf("test_valide:)\n\n"); 
}

int main(){
    test_set__print();
    test_set_empty();
    test_set__is_empty();
    test_set__size();
    test_find();
}