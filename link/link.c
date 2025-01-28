#include <assert.h>
#include <limits.h>
#include <stdlib.h>

#include "link.h"

const struct lelement sentinel = {INT_MAX, (struct lelement *) &sentinel}; 

// Retourne un booléen attestant si `e` est la butée
int llm__is_end_mark(const struct lelement *e){
	return (e->next == LLM_SENTINEL_PTR);
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

// Retourne le 1er maillon de la liste `l`
struct lelement *lnk__first(const struct link *l){
	return (l->head->next);
}


// Ajoute le maillon `add` en tête de la liste `l`
// Pre : add->next == NULL,
//       add n'est pas la butée
int lnk__add_head(struct link *l, struct lelement *add){
	if (add->next == NULL || llm__is_end_mark(add)){
		return 0;
	}
	else{
		struct lelement *first=lnk__first(l);
		l->head=add;
		add->next=first;
		return 1;
	}
}

// Enlève le premier maillon de la liste `l` et le retourne
// Si la liste est vide, renvoie NULL.
// Post : return->next == NULL || return == NULL
struct lelement *lnk__remove_head(struct link *l){
	if (l->head	== LLM_SENTINEL_PTR ){
		return NULL;
	}
	else{
		struct lelement *first=lnk__first(l);
		l->head=llm__next(first);
		return first;
	}
}

