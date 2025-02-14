#ifndef __SET_H__
#define __SET_H__

#include <stddef.h>

struct set;

struct cursor;

// Return a struct set representing the empty set
struct set *set__empty(int (*cmp)(const void*, const void*),
                        void * (*copy)(void const *),
                        void (*del)(void *));

// Returns non-zero if se is empty, 0 otherwise
int set__is_empty(const struct set* se);

// Returns non-zero if c belongs to se, 0 otherwise
int set__find(const struct set *se, void* c);

// Returns the number of elements in se
size_t set__size(const struct set *se);

// Adds c to se
// Returns 0 if c has been added to se, a negative value otherwise
// NB: se should not be modified if c cannot be added to se
int set__add(struct set *se, void* c);

// Removes c from se
// Returns 0 if c has been removed from se, a negative value otherwise
// NB: se should not be modified if c cannot be removed from se
int set__remove(struct set *se, void* c);

// Frees the dynamically allocated contents of the set se
// Does *not* free the pointer se
void set__free(struct set* se);

//helper function for debugging : display all elements in se
void set__print(const struct set * se, void (*print)(void *));

struct set * set__filter(const struct set * s, int (*p)(void*));

void* cursor_fst(struct set* se);
void* cursor_next(struct set* se,void* a);
void* cursor_end(struct set* se);
int curseur_data(void* a);

#endif // __SET_H__
