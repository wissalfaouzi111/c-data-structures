#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "link.h"
#include "set_link.h"
void test_llm_is_end_mark() {
    printf("Test llm__is_end_mark:\n");

    // Cas 1: Vérifier si la sentinelle est bien détectée
    llm__is_end_mark(LLM_SENTINEL_PTR) ?  printf("[PASS] Sentinelle détectée correctement.\n") : printf("Sentinelle non détectée.\n");
    

    // Cas 2: Vérifier si un élément normal n'est pas détecté comme sentinelle
    struct lelement normal_element = {42, NULL};
    llm__is_end_mark(&normal_element) ?  printf("[PASS] Sentinelle détectée correctement.\n") : printf("Sentinelle non détectée.\n\n");
}

void test_llm_next() {
    printf("Test llm__next:\n");

    // Cas 1: Vérifier le comportement avec un élément normal
    struct lelement element1 = {10, LLM_SENTINEL_PTR};
    struct lelement element2 = {20, &element1};
    llm__next(&element2) == &element1 ? printf("[PASS] Pointeur suivant correct pour un élément normal.\n") : printf("Pointeur suivant incorrect.\n");
    // Cas 2: Vérifier le comportement avec la sentinelle
    llm__next(LLM_SENTINEL_PTR) == LLM_SENTINEL_PTR ? printf("[PASS] Pointeur suivant correct pour la sentinelle.\n\n") : printf("Pointeur suivant incorrect pour la sentinelle.\n\n");
}

void test_lnk_empty() {
    printf("Test lnk__empty:\n");

    // Créer une liste vide
    struct link list = lnk__empty();
    // Vérifier si la tête pointe vers la sentinelle
    list.head == LLM_SENTINEL_PTR ? printf("[PASS] Liste vide correctement initialisée.\n\n") : printf("Liste vide non initialisée correctement.\n\n");
}

void test_lnk_first() {
    printf("Test lnk__first:\n");

    // Cas 1: Liste vide
    struct link empty_list = lnk__empty();
    lnk__first(&empty_list) == LLM_SENTINEL_PTR ? printf("[PASS] Premier élément d'une liste vide correctement détecté.\n") : printf("Premier élément d'une liste vide incorrect.\n");
    // Cas 2: Liste non vide
    struct lelement element1 = {10, NULL};
    struct link list = lnk__empty();
    lnk__add_head(&list, &element1);
    lnk__first(&list) == &element1 ? printf("[PASS] Premier élément d'une liste non vide correctement détecté.\n\n") : printf("Premier élément d'une liste non vide incorrect.\n");
}

void test_lnk_add_head() {
    printf("Test lnk__add_head:\n");

    // Cas 1: Ajout dans une liste vide
    struct link list = lnk__empty();
    struct lelement element1 = {10, NULL};
    if (lnk__add_head(&list, &element1) == 1 && list.head == &element1) {
        printf("[PASS] Ajout en tête dans une liste vide réussi.\n");
    } else {
        printf("Ajout en tête dans une liste vide échoué.\n");
    }

    // Cas 2: Ajout dans une liste non vide
    struct lelement element2 = {20, NULL};
    if (lnk__add_head(&list, &element2) == 1 && list.head == &element2 && element2.next == &element1) {
        printf("[PASS] Ajout en tête dans une liste non vide réussi.\n");
    } else {
        printf("Ajout en tête dans une liste non vide échoué.\n");
    }

    // Cas 3: Ajout d'un élément invalide (sentinelle ou next non NULL)
    struct lelement invalid_element = {30, LLM_SENTINEL_PTR};
    if (lnk__add_head(&list, &invalid_element) == 0) {
        printf("[PASS] Ajout d'un élément invalide correctement refusé.\n\n");
    } else {
        printf("Ajout d'un élément invalide incorrectement accepté.\n");
    }
}

void test_lnk_remove_head() {
    printf("Test lnk__remove_head:\n");

    // Cas 1: Suppression dans une liste vide
    struct link empty_list = lnk__empty();
    if (lnk__remove_head(&empty_list) == NULL) {
        printf("  [PASS] Suppression dans une liste vide correctement gérée.\n");
    } else {
        printf("  [FAIL] Suppression dans une liste vide incorrecte.\n");
    }

    // Cas 2: Suppression dans une liste non vide
    struct link list = lnk__empty();
    struct lelement element1 = {10, NULL};
    lnk__add_head(&list, &element1);
    struct lelement *removed = lnk__remove_head(&list);
    if (removed == &element1 && list.head == LLM_SENTINEL_PTR) {
        printf("  [PASS] Suppression en tête dans une liste non vide réussie.\n\n");
    } else {
        printf("  [FAIL] Suppression en tête dans une liste non vide échouée.\n");
    }
}

void test_lnk_add_after() {
    printf("Test lnk__add_after:\n");

    // Cas 1: Ajout après un élément normal
    struct link list = lnk__empty();
    struct lelement element1 = {10, NULL};
    struct lelement element2 = {20, NULL};
    lnk__add_head(&list, &element1);
    lnk__add_after(&list,&element1,&element2);
    if (element1.next == &element2) {
        printf("  [PASS] Ajout après un élément normal réussi.\n");
    } else {
        printf("  [FAIL] Ajout après un élément normal échoué.\n");
    }

    // Cas 2: Ajout après la sentinelle (doit échouer)
    if (lnk__add_after(&list, LLM_SENTINEL_PTR, &element2) == 0) {
        printf("  [PASS] Ajout après la sentinelle correctement refusé.\n");
    } else {
        printf("  [FAIL] Ajout après la sentinelle incorrectement accepté.\n");
    }
}

void test_lnk_remove_after() {
    printf("Test lnk__remove_after:\n");

    // Cas 1: Suppression après un élément normal
    struct link list = lnk__empty();
    struct lelement element1 = {10, NULL};
    struct lelement element2 = {20, NULL};
    lnk__add_head(&list, &element2);
    lnk__add_head(&list, &element1);
    struct lelement *removed = lnk__remove_after(&list, &element1);
    if (removed == &element2 && element1.next == LLM_SENTINEL_PTR  && llm__next(removed)==NULL) {
        printf("  [PASS] Suppression après un élément normal réussie.\n");
    } else {
        printf("  [FAIL] Suppression après un élément normal échouée.\n");
    }

    // Cas 2: Suppression après la sentinelle (doit échouer)
    if (lnk__remove_after(&list, LLM_SENTINEL_PTR) == NULL) {
        printf("  [PASS] Suppression après la sentinelle correctement refusée.\n");
    } else {
        printf("  [FAIL] Suppression après la sentinelle incorrectement acceptée.\n");
    }
}
void test_set_empty() {
    printf("%s\n", __func__);
    struct set *s = set__empty();
    assert(s->l != NULL);  
    assert(set__is_empty(s) == 1); 
    set__free(s);
    printf("okkkk;)\n");
}

void test_set_is_empty() {
    printf("%s\n", __func__);
    struct set *s = set__empty();
    assert(set__is_empty(s) == 1);  
    struct lelement elem1 = {5, NULL};
    s->l->head = &elem1;
    assert(set__is_empty(s) == 0);
    set__free(s);
    printf("okkkk;)\n");
}

int is_even(int a){
  return a%2 == 0;
}

void test_set_filter(void){
  printf("%s\n",__func__);
  struct set* s=set__empty();
  for (size_t i=0;i<10;i++){
    set__add(s,i);
  }
  set__print(s);
  struct set* res=set__filter(s,is_even);
  set__print(res);
  set__free(s);
  set__free(res);
  printf("\tOK\n");
}


void test_find() {
    printf("%s\n", __func__);
    struct link l = lnk__empty();
    assert(find(&l, 5) == NULL); 

    struct lelement elem1 = {3, LLM_SENTINEL_PTR};
    l.head = &elem1;
    assert(find(&l, 2) == NULL);  
    assert(find(&l, 3) == NULL);  
    assert(find(&l, 4) == &elem1);

    struct lelement elem2 = {7, LLM_SENTINEL_PTR};
    elem1.next = &elem2;
    assert(find(&l, 6) == &elem1); 
    assert(find(&l, 7) == &elem1); 
    assert(find(&l, 8) == &elem2); 
    printf("okkkk;)\n");
}
void test_set_find(){
    printf("%s\n", __func__);
    struct set *se =set__empty();
    assert(set__find(se,1)==0);
    struct lelement el1={2,NULL};
    se.l->head=&el1;
    assert(set__find(se,2)==1);
    struct lelement el2={3,LLM_SENTINEL_PTR};
    el1.next=&el2;
    assert(set__find(se,0)==0);  
    assert(set__find(se,3)==1); 
    assert(set__find(se,4)==0); 
    set__free(se);
    printf("okkkk;)\n");
}
/*
void test_mar(){
    printf("%s\n", __func__);
    struct set s=set__empty();
    set__print(&s);
    set__add(&s,1890);
    set__print(&s);
    set__add(&s,12);
    printf("Find 12 ? %d\n", set__find(&s, 12));
    set__print(&s);
    set__free(&s);
}*/

int main () {
  printf("%s\n", __FILE__);
  test_llm_is_end_mark();
  test_llm_next();
  test_lnk_empty();
  test_lnk_first();
  test_lnk_add_head();
  test_lnk_remove_head();
  test_lnk_add_after();
  test_lnk_remove_after();
  test_set_filter();
  test_set_empty();
  
  
  test_set_is_empty();
  test_find();
  test_set_find();
  /*test_mar();*/
  return EXIT_SUCCESS;
}
