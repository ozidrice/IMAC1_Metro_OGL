#ifndef _MONDE_
#define _MONDE_

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <png.h>

#include "element.h"
#include "forme.h"

typedef struct monde
{
	Joueur *joueur;
	Projectile *liste_projectiles;
	Ennemi *liste_ennemis; 
	Obstacle *liste_obstacle;
	Bonus *liste_bonus;
	Malus *liste_malus;
	float vit_defilement_x;
}Monde;


/* Affiche le monde et ses parametre dans la fenetre */
void afficherMonde(Monde *m);


/* Ajoute le malus m au Monde */
void ajouterMalus(Monde *m, Malus *ma);

/* Ajoute le bonus b au Monde */
void ajouterBonus(Monde *m, Bonus *b);

/* Ajoute l'obstacle o au Monde */
void ajouterObstacle(Monde *m, Obstacle *o);

/* Ajoute l'ennemi e au Monde */
void ajouterEnnemi(Monde *m, Ennemi *e);

/* Charge le monde (ajouter lien vers le fichier de la map en parametre ?) */
void chargerMonde(Monde *m, char * MAP);

/* Gestion des niveaux */
void LancerMonde(Monde *m, int niveau);

/* obtient un pixel de la surface */
Uint32 obtenirPixel(SDL_Surface *surface, int x, int y);

/* Ajoute l'obstacle o au Monde */
void ajouterObstacle(Monde *m, Obstacle *o);

/*	Ajoute l'ennemi e au monde*/
void ajouterEnnemi(Monde *m, Ennemi *e);

/* obtient un pixel de la surface */
Uint32 obtenirPixel(SDL_Surface *surface, int x, int y);

/* Malloc un monde */
Monde *creerMonde();

/* free tous les élements du monde */
void freeMonde(Monde *m);

/* Initialise texture */
GLuint *generateID(char *chemin);

void defilerMonde(Monde *m);
void defilerProjectiles(Monde *m);

/*	Créé les projectiles necessaire*/
void generateNewProjectiles(Monde *m, struct Element *liste_elem);


/*Fait lancer et déplacer les élements necessaires*/
void action(Monde *m);

void colisionsElement(Monde *m);
void colisionsJoueur(Monde *m);


#endif
