#ifndef _JOUEUR_
#define _JOUEUR_

#include "element.h"
typedef struct joueur {
	Element *e;
	float vit_deplacement_x;
	float vit_deplacement_y;
}Joueur;



/*malloc un joueur*/
Joueur *creerJoueur();

/*affiche un joueur sur la fenetre*/
void afficheJoueur(Joueur *j);

/* Déplace le joueur */
void deplacer(Joueur *j, float x, float y);

#endif
