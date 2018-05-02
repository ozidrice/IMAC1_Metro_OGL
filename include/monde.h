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
	float vit_defilement_x;
}Monde;


/* Affiche le monde et ses parametre dans la fenetre */
void afficherMonde(Monde *m);

/* Ajoute l'obstacle o au Monde */
void ajouterObstacle(Monde *m, Obstacle *o);

/* Ajoute l'ennemi en au Monde */
void ajouterEnnemi(Monde *m, Ennemi *en);

/* Charge le monde (ajouter lien vers le fichier de la map en parametre ?) */
void chargerMonde(Monde *m);

/* obtient un pixel de la surface */
Uint32 obtenirPixel(SDL_Surface *surface, int x, int y);

/* Malloc un monde */
Monde *creerMonde();

/* free tous les élements du monde */
void freeMonde(Monde *m);

/* Initialise texture */
GLuint *generateID(char *chemin);

void defilerMonde(Monde *m);

/*Fait lancer et déplacer les élements necessaires*/
void action(Monde *m);


#endif
