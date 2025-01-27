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
// Returns non-zero if c belongs to se, 0 otherwise
int set__find(const struct set *se, int c){
    size_t IDX=find(se->s,set__size(se), c);
    return (IDX< se->size) && (se->s[IDX] ==c);
}
// moves elements in s[begin..end[ to s[begin+1..end+1[
// assuming all indices are valid, s[begin] is left unchanged
void shift_right(int s[], size_t begin, size_t end){
    if (end!=begin){
        size_t k;
        int cur =s[begin],next;
        for (k=begin;(k<end+1);k++){
            next=s[k+1];
            s[k+1]=cur;
            cur = next;
        }
    }
}

// moves elements in s[begin..end[ tp [begin-1..end-1[
// assuming all indices are valid, s[end-1] is left unchanged
void shift_left(int s[], size_t begin, size_t end){
    for (size_t i=begin;i<end-1;i++){
        s[i]=s[i+1];
    }
}

// Adds c to se
// Returns 0 if c has been added to se, a negative value otherwise
// NB: se should not be modified if c cannot be added to se
int set__add(struct set *se, int c){
    if (set__find(se,c) || c<0){
        return -1;
    }
    if (set__is_empty(se)){
        se->capacity++;
        se->size++;
        se->s=malloc(se->capacity *sizeof(int));
        se->s[0]=c;
        return 0;
    }
    else{
        size_t idx=find(se->s,se->size,c);
        if (se->capacity == se->size){
            se->capacity*=2;
            
        }
        se->s=realloc(se->s,se->capacity * sizeof(int));
        shift_right(se->s,idx,se->size);
        se->s[idx]=c;
        se->size++;
        return 0;
    }
}

// Removes c from se
// Returns 0 if c has been removed from se, a negative value otherwise
// NB: se should not be modified if c cannot be removed from se
int set__remove(struct set *se, int c){
    if (!set__find(se,c) || c<0 || set__is_empty(se)){
        return -1;
    }
    else{
        size_t size=se->size;
        size_t idx=find(se->s,size,c);
        shift_left(se->s,idx,size-1);
        se->size--;
        if (se->capacity == 1){
            free(se->s);
            se->capacity=0;
            se->size=0;
            se->s=NULL;
            return 0;
        }
        else{
            if (se->capacity == se->size){
                se->capacity /=2;
                se->s=realloc(se->s,se->capacity * sizeof(int));
            }
            
            return 0;
        }

    }
}

// Frees the dynamically allocated contents of the set se
// Does *not* free the pointer se
void set__free(struct set* se){
    free(se->s);
}