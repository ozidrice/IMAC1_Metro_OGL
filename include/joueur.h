#ifndef _JOUEUR_
#define _JOUEUR_

#include "element.h"

typedef struct joueur {
	Element *e;
	/* ... */
}Joueur;

/*malloc un joueur*/
Joueur *creerJoueur();

/*affiche un joueur sur la fenetre*/
void afficheJoueur(Joueur *j);


#endif
