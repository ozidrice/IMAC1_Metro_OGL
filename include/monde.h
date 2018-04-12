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
	float defilement_x;
	float vit_defilement_x;
}Monde;


/*	Affiche le monde et ses parametre dans la fenetre */
void afficherMonde(Monde *m);

/* Malloc un monde */
Monde *creerMonde();

/* Initialise texture */
GLuint *generateID(char *chemin);

void defilerMonde(Monde *m);


#endif
