#include "set_link.h"
#include "link.h"
#include <stdlib.h>
// Return a struct set representing the empty set
struct set set__empty(void){
    struct set s;
    s.l=malloc(sizeof(struct link));
    struct link link =lnk__empty();
    *(s.l)=link;
    return s;
}
// Returns non-zero if se is empty.h, 0 otherwise
int set__is_empty(const struct set* se){
    return se->l->head == LLM_SENTINEL_PTR;
}


void link_free(struct link* l){
    struct lelement* next =lnk__first(l);
    while (!llm__is_end_mark(next)){
        struct lelement* mail=llm__next(next);
        free(next);
        next=mail;
    }
}

/*// Returns NULL if l is empty, or if f is smaller than or equal to the first 
// value in l
// Otherwise, returns the cell e such that:
// - f is the data of the next cell of e,
// - or f should be inserted after e (if e is not in l)
// pre-condition: l is sorted in increasing order
struct lelement * find(struct link *l, int f){
    if (l->head == LLM_SENTINEL_PTR || f <= l->head->data){
        return NULL;
    }
    struct lelement *first=lnk__first(l);
    struct lelment *next=llm__next(first);
    while (!llm__is_end_mark(first)){
        if (first->data ==  )
    }
}


// Frees the dynamically allocated contents of the set se
// Does *not* free the pointer se
void set__free(struct set* se){
    link_free(se->l);   
}*/

