#ifndef _ELEMENT_
#define _ELEMENT_

#include <stdlib.h>
#include <stdio.h>
#include "forme.h"

typedef struct Element {
	int pv; //Point de vie -- -1 si inf
	int pa; //Point d'attaque

	//Positionnement & taille
	float posx, posy, taille;

	//Deplacement
	float vit_deplacement_x;
	float vit_deplacement_y;
	
	//Projectile
	float frequence_projectile;
	float taille_projectile;

	//Texture
	GLuint *texture;
	
	//Liste chainée
	struct Element *next;
}Joueur, Ennemi, Bonus, Obstacle, Projectile;


/* Malloc un element */
struct Element *initElement(int pv, int pa, 
	float x, float y, float taille, 
	float vit_deplacement_x, float vit_deplacement_y, 
	float frequence_projectile, float taille_projectile,
	char * path_texture);


/*Ajoute un élément à la liste*/
void addElementToList(struct Element *list, struct Element *elem);

/* Déplace un élement */
void moving(struct Element* e, float x, float y);

/* Affiche un element sur la fenetre*/
void afficheElement(struct Element *e);

/* Malloc un joueur */
Joueur *creerJoueur();

/* Malloc un Ennemi */
Ennemi *creerEnnemi(float x, float y);

/* Malloc un Bonus */
Bonus *creerBonus(float x, float y);

/* Malloc un Obstacle */
Obstacle *creerObstacle(float x, float y);

/* Malloc un Projectile */
Projectile *creerProjectile(float x, float y);

#endif
