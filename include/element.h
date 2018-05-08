#ifndef _ELEMENT_
#define _ELEMENT_

#include <stdlib.h>
#include <stdio.h>

#include "forme.h"
#include "texture.h"

typedef struct Element {
	int pv; //Point de vie -- -1 si inf
	int pa; //Point d'attaque

	//Positionnement & taille
	float posx, posy, taille;

	//Deplacement
	float vit_deplacement_x;
	float vit_deplacement_y;
	
	//Projectile
	Uint32 intervalle_projectile; //en ms
	Uint32 last_launch; //Timer du dernier projectile lancé 
	float taille_projectile;
	int nombreProjectileParTir;
	float angleTir;
	float vit_deplacement_projectile;

	//Texture
	GLuint *texture;
	
	//Liste chainée
	struct Element *next;
}Joueur, Ennemi, Obstacle, Projectile, Bonus, Malus;



/* Malloc un element */
struct Element *initElement(int pv, int pa, 
	float x, float y, float taille, 
	float vit_deplacement_x, float vit_deplacement_y, 
	Uint32 intervalle_projectile, int nombreProjectileParTir, float angleTir, float taille_projectile, float vit_deplacement_projectile, 
	GLuint *texture);

/*Ajoute un élément à la liste*/
void addElementToList(struct Element **list, struct Element *elem);

/*Retire et free l'élément de la liste*/
void removeElementFromList(struct Element **elem);

/*	Attaque la cible,
*	return 1 si la cible meurt
*	0 sinon 
*/
int attaque(struct Element *attanquant, struct Element *cible);

/* Déplace la liste d'élement e en prenant compte de sa vitesse de déplacement*/
void moving(struct Element** e, float x, float y,  int freeOnTop, int freeOnRight, int freeOnBottom, int freeOnLeft);

/* Affiche la liste d'élément e sur la fenetre*/
void afficheElement(struct Element *e);

/* Malloc un joueur */
Joueur *creerJoueur(GLuint *texture);

/* Malloc un Ennemi */
Ennemi *creerEnnemi(float x, float y, float vit_deplacement_x, float vit_deplacement_y,Uint32 intervalle_projectile, int nombreProjectileParTir, float angleTir, float taille_projectile, float vit_deplacement_projectile, GLuint *texture);

/* Malloc un Bonus */
Bonus *creerBonus(float x, float y, GLuint *texture);

/* Malloc un Malus */
Malus *creerMalus(float x, float y, GLuint *texture);

/* Malloc un Obstacle */
Obstacle *creerObstacle(float x, float y, GLuint *texture);

/* Malloc un Projectile */
Projectile *creerProjectile(float x, float y, float taille, int pa, float vit_deplacement_x, float vit_deplacement_y);

/*	Renvoie 1 si les elements sont en colision
*	0 sinon
*/
int estEnColision(struct Element *e1, struct Element *e2);

/*	Test colisions entre les listes d'elem
*	Retire les elements mort des listes
*/
void colision(struct Element **liste1, struct Element **liste2);

/*
*	Lance un projectile si le délai depuis la dernier lancement est suffisement grand
*	Return le projectile si a été lancé
*	NULL sinon
*/
Projectile *lance_projectile(struct Element *e);


/*	Créé les projectiles necessaire à un tir 
*	en prenant en compte le nombreProjectileParTir
*/
Projectile *creerProjectileMultiple(struct Element *e);


/*	Free la liste d'éléments */
void freeElement(struct Element *e);

#endif
