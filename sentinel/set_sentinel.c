#include "set_sentinel.h"
#include <stdio.h>
#include <stdlib.h>

#define UNUSED(x) (void)(x)

/*void set__free(struct set* se)
{
    UNUSED(se);
}*/
void set__print(const struct set * se, void (*print)(void *)){
    printf("{");
    for (int i=0; (i<SET__SIZE) && (se->s[i] != SET__BOUND);i++){
        //printf("%p ",se->s[i]);
        print(se->s[i]);
    }
    printf("}\n");
}

// returns the first position p in s such that s[p]>=c if any, or
// the position of SET__BOUND otherwise.
size_t find(void* const s[], void* c,int (*cmp)(const void *,const void*)){ 
    size_t idx=0;
    for (idx=0;(idx<SET__SIZE) && (s[idx] != SET__BOUND) ;idx++){
        if( cmp(s[idx],c) >= 0){
            return idx;
        }
    }
    return idx++;
    /*size_t a = 0;
    size_t b = SET__SIZE;
    while (a < b && s[a] != SET__BOUND) {
        a++;
    }
    b = a-1; 
    a = 0;
    while (a < b) {
        size_t m = a+(b - a) / 2;
        if (s[m] >= c) {
            b = m;
        } 
        else {
            a = m + 1;
        }
    }
    return a;*/
}
// Returns non-zero if c belongs to se, 0 otherwise
int set__find(const struct set *se, void* c){
    size_t IDX=find(se->s,c,se->cmp);
    if (se->s[IDX]==SET__BOUND){
        return 0;
    }
    return (IDX<SET__SIZE) && (se->cmp(se->s[IDX],c) ==0);
}

// moves all elements in s starting from position begin and up to
// SET__BOUND included, one position to the right.
// The value in s[begin] is left unchanged.
void shift_right(void* s[], size_t begin){
    size_t k;
    void* cur =s[begin],*next;
    for (k=begin;(cur!= SET__BOUND) && (k+1<SET__SIZE);k++){
        next=s[k+1];
        s[k+1]=cur;
        cur = next;
    }
    if (k+1 < SET__SIZE){
        s[k+1]=SET__BOUND;
    }
}

// moves all elements in s starting from position begin and up to
// SET__BOUND included, one position to the left. 
void shift_left(void* s[], size_t begin){
    size_t idx;
    for(idx=begin;(idx<SET__SIZE) && (s[idx]!=SET__BOUND);idx++){
        s[idx]=s[idx+1];
    }
    if (idx+1 < SET__SIZE) {
        s[idx] = s[idx+1]; 
        idx++;
    }

    if (idx< SET__SIZE) {
        s[idx] =cannary; 
    };
}


// Return a struct set representing the empty set
struct set *set__empty(int (*cmp)(const void*, const void*),
                        void * (*copy)(void const *),
                        void (*del)(void *)){
    struct set *se=malloc(sizeof(struct set));
    se->s[0]= SET__BOUND;
    //se->s[SET__SIZE-1]=cannary;
    se->copy=copy;
    se->cmp=cmp;
    se->del=del;
    return se;
}

// Returns the number of elements in se
size_t set__size(const struct set *se){
    size_t c=0;
    size_t i;
    for (i=0;(i<SET__SIZE) && (se->s[i] != SET__BOUND);i++){
        c++;
    }
    return c;
}

// Returns non-zero if se is empty, 0 otherwise
int set__is_empty(const struct set* se){
    size_t size=set__size(se);
    return (size==0);
}

// Adds c to se
// Returns 0 if c has been added to se, a negative value otherwise
// NB: se should not be modified if c cannot be added to se
int set__add(struct set *se, void* c){
    int v[1]={0};
    if (se->cmp(c,&v[0]) < 0 || set__find(se,c) || set__size(se)>= SET__SIZE){
        return -1;
    }
    if (set__is_empty(se)){
        void *p=se->copy(c);
        se->s[0]=p;
        se->s[1]=SET__BOUND;
        return 0;
    }
    else{
        size_t idx=find(se->s,c,se->cmp);
        shift_right(se->s,idx);
        void *p=se->copy(c);
        se->s[idx]=p;
        return 0;
    }
}



// Removes c from se
// Returns 0 if c has been removed from se, a negative value otherwise
// NB: se should not be modified if c cannot be removed from se
int set__remove(struct set *se, void* c){
    int v[1]={0};

    if (se->cmp(c,&v[0]) < 0 || !set__find(se,c) || set__is_empty(se)){
        return -1;
    }
    
    else{
        size_t idx=find(se->s,c,se->cmp);  
        se->del(se->s[idx]);
        shift_left(se->s,idx);

        return 0;  
    }
}

struct set * set__filter(const struct set * s, int (*p)(void*)){
    struct set* se=set__empty(s->cmp,s->copy,s->del);
    for (size_t i=0;i<SET__SIZE;i++){
        if (s->s[i]==SET__BOUND) break;
        if(p(s->s[i])){
            set__add(se,s->s[i]);
        }        
    }
    return se;
}

// Frees the dynamically allocated contents of the set se
// Does *not* free the pointer se
void set__free(struct set* se){
    for (size_t i = 0; (i<SET__SIZE) && (se->s[i] != SET__BOUND); i++) {
        se->del(se->s[i]);
    }
    free(se);
}