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
  struct set *se = set__empty();
  set__print(se);
  set__free(se);
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
  struct set *s2=set__empty();;
  set__print(s2);
  printf("s2 est %s\n",set__is_empty(s2) ? "vide" : "non vide");
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

  struct set *s3=set__empty();
  set__print(s3);
  printf("size: %ld\n",set__size(s3));
  free(s1.s);
  set__free(s3);
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
  struct set *s3=set__empty();
  assert(find(s3->s,set__size(s3),1)==set__size(s3));
  free(s1.s);
  set__free(s3);
  printf("test_valide:)\n\n"); 
}

// Returns non-zero if c belongs to se, 0 otherwise
static void test_set__find(void){
  printf("%s\n", __func__);
  struct set s1;
  s1.capacity=4;
  s1.size=4;
  s1.s=malloc(s1.capacity * sizeof(int));
  s1.s[0]=2;
  s1.s[1]=3;
  s1.s[2]=8;
  s1.s[3]=9;
  assert(set__find(&s1,3)==1);
  assert(set__find(&s1,11)==0);
  set__free(&s1);
  printf("test_valide:)\n\n");
}

static void test_shift_right(void){
  printf("%s\n", __func__);
  //test_1
  int s1[]={1,3,6,8,9};
  printf("Avant:");
  printf("{");
  for (int i=0;i<5;i++){
    printf("%d ",s1[i]);
  }
  printf("}\n");
  shift_right(s1,2,5);
  printf("Après:");
  printf("{");
  for (int i=0;i<6;i++){
    printf("%d ",s1[i]);
  }
  printf("}\n\n");


  //test_2
  int s2[]={1,3,6,8,9};
  printf("Avant:");
  printf("{");
  for (int i=0;i<5;i++){
    printf("%d ",s2[i]);
  }
  printf("}\n");
  shift_right(s2,1,1);
  printf("Après:");
  printf("{");
  for (int i=0;i<5;i++){
    printf("%d ",s2[i]);
  }
  printf("}\n");
  printf("test_valide:)\n\n");   
}
static void test_shift_left(void){
  printf("%s\n", __func__);
  //test_1
  int s1[]={1,3,6,8,9};
  printf("Avant:");
  printf("{");
  for (int i=0;i<5;i++){
    printf("%d ",s1[i]);
  }
  printf("}\n");
  shift_left(s1,2,5);
  printf("Après:");
  printf("{");
  for (int i=0;i<4;i++){
    printf("%d ",s1[i]);
  }
  printf("}\n\n");
}
static void test_set__add(void){
  printf("%s\n",__func__);
  struct set s1;
  s1.capacity=4;
  s1.size=4;
  s1.s=malloc(s1.capacity * sizeof(int));
  s1.s[0]=2;
  s1.s[1]=3;
  s1.s[2]=8;
  s1.s[3]=9;
  printf("Avant:");
  set__print(&s1);
  set__add(&s1,10);
  printf("Après:");
  set__print(&s1);
  //je dois implementer autres tests§§§§§§!!!!!!!!!!!!!!!!!!!(AJOUTER LE CAS D 'AJOUT A UN ENSEMBLE VIDE)
  assert(set__add(&s1,3)==-1);
  assert(set__add(&s1,-2)==-1);
  free(s1.s);
  printf("test_valide:)\n\n");     
}
static void test_set__remove(void){
  printf("%s\n",__func__);
  struct set s1;
  s1.capacity=4;
  s1.size=4;
  s1.s=malloc(s1.capacity * sizeof(int));
  s1.s[0]=2;
  s1.s[1]=3;
  s1.s[2]=8;
  s1.s[3]=9;
  printf("Avant:");
  set__print(&s1);
  set__remove(&s1,9);
  printf("Après:");
  set__print(&s1);
  free(s1.s);
  printf("test_valide:)\n\n");    
}
int main(){
    test_set__print();
    test_set_empty();
    test_set__is_empty();
    test_set__size();
    test_find();
    test_set__find();
    test_shift_right();
    test_shift_left();
    test_set__add();
    test_set__remove();
}