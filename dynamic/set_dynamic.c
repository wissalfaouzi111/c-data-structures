#include "set_dynamic.h"
#include "set.h"
void set__print(const struct set * se, void (*print)(void *)){
    printf("{  .size = %ld, .capacity = %ld, .s = {",se->size,se->capacity);
    for (size_t i=0;i < se->size; i++){
        print(se->s[i]);
        if (i != se->size -1){
            printf(",");
        }
    }
    printf("}  }\n");
}

// Return a struct set representing the empty set
struct set *set__empty(int (*cmp)(const void*, const void*),
                        void * (*copy)(void const *),
                        void (*del)(void *)){
    struct set *se=malloc(sizeof(struct set));
    se->size=0;
    se->capacity=0;
    se->s=NULL;
    se->copy=copy;
    se->cmp=cmp;
    se->del=del;
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
size_t find(void* const s[], size_t size, void* c,int (*cmp)(const void*,const void *)){
    for (size_t i=0;i<size;i++){
        if (cmp(s[i],c)>=0){
            return i;
        }
    }
    return size;
}
// Returns non-zero if c belongs to se, 0 otherwise
int set__find(const struct set *se, void* c){
    size_t IDX=find(se->s,set__size(se), c,se->cmp);
    return (IDX< se->size) && (se->cmp(se->s[IDX],c) ==0);
}
// moves elements in s[begin..end[ to s[begin+1..end+1[
// assuming all indices are valid, s[begin] is left unchanged
void shift_right(void* s[], size_t begin, size_t end){
    if (end>begin){
       for (size_t i = end; i > begin; --i) {
        s[i] = s[i - 1];
       }
    }
}

// moves elements in s[begin..end[ tp [begin-1..end-1[
// assuming all indices are valid, s[end-1] is left unchanged
void shift_left(void* s[], size_t begin, size_t end){
    if (begin<end){
        for (size_t i=begin;i<end-1;i++){
            s[i]=s[i+1];
        }
    }
}

// Adds c to se
// Returns 0 if c has been added to se, a negative value otherwise
// NB: se should not be modified if c cannot be added to se
int set__add(struct set *se, void* c){
    if (set__find(se,c) /*|| c<0 */){
        return -1;
    }
    if (set__is_empty(se)){
        se->capacity++;
        se->size++;
        se->s=malloc(se->capacity *sizeof(void *));
        void* p=se->copy(c);
        se->s[0]=p;
        return 0;
    }
    if (se->capacity == se->size){
        se->capacity*=2;
        se->s=realloc(se->s,se->capacity * sizeof(void *));   
    }
    size_t idx=find(se->s,se->size,c,se->cmp);
    shift_right(se->s,idx,se->size);
    void* p=se->copy(c);
    se->s[idx]=p;
    se->size++;
    return 0;
}

// Removes c from se
// Returns 0 if c has been removed from se, a negative value otherwise
// NB: se should not be modified if c cannot be removed from se
int set__remove(struct set *se, void* c){
    if (!set__find(se,c) /*|| c<0 */|| set__size(se)==0){
        return -1;
    }
    else{
        size_t size=se->size;
        size_t idx=find(se->s,size,c,se->cmp);
        se->del(se->s[idx]);
        shift_left(se->s,idx,size);
        se->size--;
        if (se->capacity == 1){
            free(se->s);
            se->capacity=0;
            se->size=0;
            se->s=NULL;
            return 0;
        }
        else{
            if ( (se->capacity)/2 >= se->size){
                se->capacity /=2;
                se->s=realloc(se->s,se->capacity * sizeof(void *));
            }
            
            return 0;
        }

    }
}

// Frees the dynamically allocated contents of the set se
// Does *not* free the pointer se
void set__free(struct set* se){
    for (size_t i=0;i< se->size;i++){
        se->del(se->s[i]);
    }
    free(se->s);
    free(se);
}

struct set * set__filter(const struct set * s, int (*p)(void* c)){
    struct set* se=set__empty(s->cmp,s->copy,s->del);
    for (size_t i=0;i< s->size;i++){
        if(p(s->s[i])){
            set__add(se,s->s[i]);
        }
    }
    return se;
}

