#include <assert.h>
#include <limits.h>
#include <stdlib.h>

#include "link.h"

const struct lelement sentinel = {INT_MAX, (struct lelement *) &sentinel}; 

// Retourne un booléen attestant si `e` est la butée
int llm__is_end_mark(const struct lelement *e){
	return (e == LLM_SENTINEL_PTR);
}

// Retourne le maillon suivant le maillon `e`
struct lelement *llm__next(const struct lelement *e){
	return (e->next);
}

// Crée une liste vide
// Post : le champ `head` pointe sur la butée
struct link lnk__empty(void){
	struct link l;
	l.head=LLM_SENTINEL_PTR;
	return l;
}


