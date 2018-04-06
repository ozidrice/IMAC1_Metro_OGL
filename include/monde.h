#ifndef _MONDE_
#define _MONDE_

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>

#include <joueur.h>
#include <element.h>
#include <forme.h>

typedef struct monde
{
	Joueur *joueur;
	Ennemi **liste_ennemis; 
}Monde;


/*	Affiche le monde et ses parametre dans la fenetre */
void afficherMonde(Monde *m);

/* Malloc un monde */
Monde *creerMonde();

/* Charger une image */
void ImgLoad(char *filename);

/* Initialise texture */
GLuint GenerateTexture(char *filename);

#endif
