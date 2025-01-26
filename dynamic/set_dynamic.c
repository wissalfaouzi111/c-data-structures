#include "set_dynamic.h"

void set__print(const struct set* se){
    printf("{  .size = %ld, .capacity = %ld, .s = {",se->size,se->capacity);
    for (size_t i=0;i < se->size; i++){
        printf("%d",se->s[i]);
        if (i != se->size -1){
            printf(",");
        }
    }
    printf("}  }\n");
}

// Return a struct set representing the empty set
struct set set__empty(void){
    struct set se;
    se.size=0;
    se.capacity=0;
    se.s=NULL;
    return se;
}

// Returns non-zero if se is empty, 0 otherwise
int set__is_empty(const struct set* se){
    return (se->size == 0 && se->capacity == 0 && se->s ==NULL);
}

// Returns the number of elements in se
size_t set__size(const struct set *se){
    return se->size;
}


// returns the first position p in s such that s[p]>=c
// or size if no such p exists
size_t find(int const s[], size_t size, int c){
    for (size_t i=0;i<size;i++){
        if (s[i]>=c){
            return i;
        }
    }
    return size;
}

/*// moves elements in s[begin..end[ to s[begin+1..end+1[
// assuming all indices are valid, s[begin] is left unchanged
void shift_right(int s[], size_t begin, size_t end){
    size_t k;
    int cur =s[begin],next;
    for (k=begin;k<end;k++){
        next=s[k+1];
        s[k+1]=cur;
        cur = next;
    }
    if (k+1 < SET__SIZE){
        s[k+1]=SET__BOUND;
    }
}*/