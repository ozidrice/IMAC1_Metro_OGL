#ifndef _ELEMENT_
#define _ELEMENT_

#include <stdlib.h>
#include <stdio.h>
#include "forme.h"

typedef struct Element {
	int pv; //-1 si inf
	float posx, posy, taille;
	float vit_deplacement_x;
	float vit_deplacement_y;
	GLuint *texture;
	struct Element *next;
}Joueur, Ennemi, Bonus, Obstacle;


/* Malloc un element */
struct Element *initElement(int pv, float x, float y, float taille, float vit_deplacement_x, float vit_deplacement_y,char * path_texture);


/*Ajoute un élément à la liste*/
void addElementToList(struct Element *list, struct Element *elem);

/* Déplace un élement */
void moving(struct Element* e, float x, float y);

/* Affiche un element sur la fenetre*/
void afficheElement(struct Element *e);

/* Malloc un joueur */
Joueur *creerJoueur();

/* Malloc un Ennemi */
Ennemi *creerEnnemi();

/* Malloc un Bonus */
Bonus *creerBonus();

/* Malloc un Obstacle */
Obstacle *creerObstacle();

#endif
