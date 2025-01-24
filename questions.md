# Réponses aux questions sur la mise en œuvre d'un TAD

Travail à effectuer en binôme: 
Faouzi wissal, Nour Doghmi

## Prototypes des fonctions en langage C

### TAD

1. À quoi fait référence le terme *abstrait* dans le concept de ``Type Abstrait de Données''?

%
le terme abstrait fait reference a la difference qu'il y a entre la description de la donnee dans le TAD et son implementation, le TAD ne definit que les proprietes au niveau logique de la donnee son implementation depend entierement du codeur. 
%

2. Quel aspect différentie les mises en œuvre d'un TAD?

%
les mises en oeuvre de TAD different de par comment sont implementees les strucrtures de donnes et les algorithmes de manipulation de ces structures, ces choix d'implementation peuvent etre tres differentes meme si le TAD est lememe.
%

3. Pourquoi chercher à écrire un algorithme (ou à le programmer en langage C) à partir d'un TAD?

%
Cela permet de mieux visualiser les structures en dehors d'un contexte fixe (language de programmation predefini)et donc de pouvoir implementer les strcutres du TAD de differentes manieres dans differents languages en plus de se concentrer sur la logique du probleme et d'avoir une vision plus clair des algorithmes assurant flexibilite,maintenabilite et efficacite. 
%

4. Dans la mise en œuvre que vous avez réalisée, pourquoi mettre le tableau dans une structure au lieu de l'utiliser directement comme paramètre, par exemple: `int set__add(int * s, int i)`?

%
Encapsuler un tableau dans une structure au lieu de l'utiliser directement comme parametre permet de regrouper toutes les informations liees au TAD(comme la taille d'un tableau)dans un seul objet.Cette approche ameliore la lisibilite et l'abstraction, en evitant a l'utilisateur de gerer les details externes.
%

### set__is_empty

1. Donner les prototypes de la fonction `set__is_empty` correspondant aux deux passages de paramètres possibles.

%
int set_is_empty(const struct set* se);
int set_is_empty(const struct set se);

%

2. Sur un exemple, montrer qu'il est préférable d'avoir un passage par adresse pour le paramètre d'entrée.

%
passer une structure par adresse est plus efficace car cela evite copier les donnees.La fonction agit directement sur l'original , sans creer de copie , ce qui est particulierement utile pour les structure de grandes tailles 
%

3. Pourquoi le passage par adresse ne correspond pas à la description (au comportement) de cette opération dans le TAD? Justifier l'utilisation du mot-clé `const` dans le prototype de la fonction.

%
il ne correspond pas au comportement de cette fonction dans le TAD car set_add retorune un set qui est pris en parametre par set empty et non un pointeur.
const est bien utilise ici car il empeche le set d'etre modifie par set_is empty .
%

### set__add

1. Pourquoi est-il possible, en langage C, d'avoir un prototype de la fonction `set__add` qui n'a pas de valeur de retour?

%
car on peut ajouter les valeurs par effet de bords.
%

2. Pourquoi avoir choisi de retourner une valeur entière? Lister tous les cas d'utilisation que vous avez mis en œuvre.

%
en retournant une valeur entiere il est possible d'avoir des informations
sur le deroulement de la fonctions par exemple retourner 0 si tout se passe bien,retourner 1 si set n'as pas changer du tout , retourner 2 si on a ajouter l'element au mauvais emplacement(set non trie).
%

### set__empty

La fonction `set__empty` initialise un ensemble vide.

1. Le TAD n'indique pas le mode d'allocation mémoire. Deux modes sont possibles: allocation par le TAD ou allocation par l'utilisateur du TAD. Il y a alors trois prototypes possibles pour la fonction:

```c
struct set * set__empty();

struct set set__empty();

void set__empty(struct set *);
```

À quel mode d'allocation mémoire correspond chacun de ces prototypes? Montrer qu'avec le premier prototype une allocation sur la pile n'est pas correcte.

%
la premiere correspond a l'allocation d'une adresse(pointeur) elle est doncfaites sur le tas car sinon on retournerait l'adresse d'un element qui va etre supprime a la fin de la fonction.
la deuxieme se fait sur la pile car on retourne une copie et donc a la fin de la fonction meme si le struct a l'interieur est supprimer on garde une copie
la troisieme se fait sur le tas.
%

2. On choisit que l'allocation des `struct set` soit *faite par l'utilisateur du TAD*. Par exemple dans la fonction `main`:
```c
int main() {
    struct set s = set__empty();
    set__add(&s, 64);
    set__free(&s);
    return 0;
}
```

Expliquer pourquoi le compilateur doit connaître la définition de `struct set` afin de compiler la fonction `main` ci-dessus.

%
car sans la definition du struct set il ne sait pas combien de memoire allouer.
%

3. Écrire un exemple d'utilisation des deux derniers prototypes, et donner leurs avantages et inconvénients.

%
struct set new_set=set__empty();
****************************************
struct set new_set;
set__empty(&s);

le premier est simple pour des structures de petites taills et le deuxieme est moins simples mais plus adapte pour les structures de grandes tailles.
%