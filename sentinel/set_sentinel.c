#include "set_sentinel.h"
#include <stdio.h>
#define UNUSED(x) (void)(x)

void set__free(struct set* se)
{
    UNUSED(se);
}
void set__print(const struct set* se){
    printf("{");
    for (int i=0; (i<SET__SIZE) && (se->s[i] != SET__BOUND);i++){
        printf("%d ",se->s[i]);
    }
    printf("}\n");
}

// returns the first position p in s such that s[p]>=c if any, or
// the position of SET__BOUND otherwise.
size_t find(int const s[], int c){ 
    size_t idx=0;
    for (idx=0;(idx<SET__SIZE) && (s[idx] != SET__BOUND) ;idx++){
        if( s[idx] >= c){
            return idx;
        }
    }
    return idx++;
}
// Returns non-zero if c belongs to se, 0 otherwise
int set__find(const struct set *se, int c){
    size_t IDX=find(se->s,c);
    return (IDX<SET__SIZE) && (se->s[IDX] ==c);
}

// moves all elements in s starting from position begin and up to
// SET__BOUND included, one position to the right.
// The value in s[begin] is left unchanged.
void shift_right(int s[], size_t begin){
    size_t k;
    int cur =s[begin],next;
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
void shift_left(int s[], size_t begin){
    size_t idx;
    for(idx=begin;(idx<SET__SIZE) && (s[idx]!=SET__BOUND);idx++){
        s[idx]=s[idx+1];
    }
    if (idx+1 < SET__SIZE) {
        s[idx] = s[idx+1]; 
        idx++;
    }
    // Marquer la fin logique à la nouvelle position
    if (idx< SET__SIZE) {
        s[idx] =-2; // Remplit la dernière case avec une valeur par défaut (0 ici)
    }
}


// Return a struct set representing the empty set
struct set set__empty(void){
    struct set se= {{SET__BOUND}};
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
int set__add(struct set *se, int c){
    if (c<0 || set__find(se,c) || set__size(se)>= SET__SIZE-1){
        return -1;
    }
    else{
        size_t idx=find(se->s,c);
        shift_right(se->s,idx);
        se->s[idx]=c;
        return 0;
    }
}



// Removes c from se
// Returns 0 if c has been removed from se, a negative value otherwise
// NB: se should not be modified if c cannot be removed from se
int set__remove(struct set *se, int c){
    if (c<0 || !set__find(se,c) || set__is_empty(se)){
        return -1;
    }
    else{
        size_t idx=find(se->s,c);  
        shift_left(se->s,idx);
        return 0;  
    }
}
