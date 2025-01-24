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


/*// returns the first position p in s such that s[p]>=c if any
size_t find(int const s[], int c){ 
    size_t idx=0;
    for (idx=0;(idx < se->size) ;idx++){
        if( s[idx] >= c){
            return idx;
        }
    }
    return idx++;
}*/

// Returns non-zero if c belongs to se, 0 otherwise
/*int set__find(const struct set *se, int c){
    size_t IDX=find(se->s,c);
    return (IDX<SET__SIZE) && (se->s[IDX] ==c);
}*/

// Adds c to se
// Returns 0 if c has been added to se, a negative value otherwise
// NB: se should not be modified if c cannot be added to se
/*int set__add(struct set *se, int c){
    if (c<0 || set__find(se,c) || set__size(se)>= SET__SIZE-1){
        return -1;
    }
}*/

/*void s_D(struct set se){
    struct set* se=malloc()
    

    if (se.capacity==0){
        se.capacity=1;
    }
    else if (se.capacity==se.size){
        se.capacity*=2;
    }

}*/