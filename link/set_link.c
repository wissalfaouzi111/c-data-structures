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
    return (se==NULL ||  se->l==NULL || se->l->head==NULL || lnk__first(se->l)== LLM_SENTINEL_PTR);
}



/// Returns NULL if l is empty, or if f is smaller than or equal to the first 
// value in l
// Otherwise, returns the cell e such that:
// - f is the data of the next cell of e,
// - or f should be inserted after e (if e is not in l)
// pre-condition: l is sorted in increasing order
struct lelement * find(struct link *l, int f){
    if (lnk__first(l) == LLM_SENTINEL_PTR || f <= lnk__first(l)->data){
        return NULL;
    }
    struct lelement *el=lnk__first(l);
    while (!llm__is_end_mark(el)){
        struct lelement *e=el;
        el=llm__next(el);
        if (el->data >= f){
            return e;
        }
    }
    return NULL; //NEVER REACHED
}

// Returns non-zero if c belongs to se, 0 otherwise
int set__find(const struct set *se, int c){
    if (lnk__first(se->l) == LLM_SENTINEL_PTR || c < lnk__first(se->l)->data){
        return 0;
    }
    return (lnk__first(se->l)->data == c || (llm__next(find(se->l,c)))->data == c );
}

// Returns the number of elements in se
size_t set__size(const struct set *se){
    size_t size=0;
    if (set__is_empty(se)){
        return size;
    }
    else{
        struct lelement *el=lnk__first(se->l);
        while (!llm__is_end_mark(el)){
            size++;
            el=llm__next(el);
        }
        return size;
    }
}

 //Frees the dynamically allocated contents of the set se
// Does *not* free the pointer se
void set__free(struct set* se){
    link_free(se->l);
}

void link_free(struct link* l){
    struct lelement* next =lnk__first(l);
    while (!llm__is_end_mark(next)){
        struct lelement* mail=llm__next(next);
        free(next);
        next=mail;
    }  
}
// Adds c to se
// Returns 0 if c has been added to se, a negative value otherwise
// NB: se should not be modified if c cannot be added to se
int set__add(struct set *se, int c){
    if (set__find(se,c) || c<0){
        return -1;
    }
    
        struct lelement *add=malloc(sizeof(struct lelement));
        add->data=c;
        add->next=  NULL;
        if (set__is_empty(se)){
            se->l->head=add;
            add->next=LLM_SENTINEL_PTR;
            return 0;
        }
        int res=lnk__add_after(se->l,find(se->l,c),add);
        if (res){
            return 0;
        }
        else{
            return -1;
        }
    
}

// Removes c from se
// Returns 0 if c has been removed from se, a negative value otherwise
// NB: se should not be modified if c cannot be removed from se
int set__remove(struct set *se, int c){
    if (!set__find(se,c) || set__is_empty(se)){
        return -1;
    }
    if (set__size(se)==1){
        struct lelement *deleted=lnk__remove_head(se->l);
        free(deleted);       
        return 0;
    }
    else{
        struct lelement *after=find(se->l,c);
        struct lelement *deleted=lnk__remove_after(se->l,after);
        free(deleted);
        return 0;
    }
}
