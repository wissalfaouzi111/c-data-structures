#include <assert.h>
#include <limits.h>
#include <stdlib.h>

#include "link.h"

#define UNUSED(x) (void)(x)

const struct lelement sentinel = {INT_MAX, (struct lelement *) &sentinel}; 

// Retourne un booléen attestant si `e` est la butée
int llm__is_end_mark(const struct lelement *e){
	return (e == LLM_SENTINEL_PTR);
}

// Retourne le maillon suivant le maillon `e`
struct lelement *llm__next(const struct lelement *e){
	if(e==NULL){
		return NULL;
	}
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
	return (l->head);
}


// Ajoute le maillon `add` en tête de la liste `l`
// Pre : add->next == NULL,
//       add n'est pas la butée
int lnk__add_head(struct link *l, struct lelement *add){
	if (add->next != NULL || llm__is_end_mark(add)){
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

// Ajoute le maillon `add` à la suite du maillon `after` dans
// la liste `l`
// Rq : `l` peut ne pas être utilisé dans cette fonction.
// Pre : after n'est pas la butée,
//       add n'est pas la butée,
//       after->next != NULL,
//       add->next == NULL
int lnk__add_after(struct link *l, struct lelement *after,struct lelement * add){
	UNUSED(l);
	if (llm__is_end_mark(after) || llm__is_end_mark(add) || llm__next(after)==NULL || llm__next(add)!=NULL ){
		return 0;
	}
	if ((llm__next(after) != LLM_SENTINEL_PTR && add->data > after->data && add->data < llm__next(after)->data) || ((llm__next(after) == LLM_SENTINEL_PTR && add->data > after->data))) {
		add->next=after->next;
		after->next=add;
		return 1;
	}
	return 0;
}

// Enlève le maillon se trouvant *après* `after` dans la liste `l` et
// le retourne. Renvoie NULL si le maillon après `after` est la butée.
// Pre  : after n'est pas la butée
//        after->next != NULL
// Post : return->next == NULL || return == NULL
struct lelement *lnk__remove_after(struct link *l, struct lelement *after){
	UNUSED(l);
	if (llm__is_end_mark(after) || llm__next(after)==NULL || llm__next(after)==LLM_SENTINEL_PTR){
		return NULL;
	}
	else{
		struct lelement *ml_remove=llm__next(after);
		struct lelement *ml_next=llm__next(ml_remove);
		after->next=ml_next;
		ml_remove->next=NULL;
		return ml_remove;
	}
}