#ifndef _MONDE_
#define _MONDE_

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>

#include "element.h"
<<<<<<< HEAD
#include "joueur.h"
=======
>>>>>>> 296767f831ef38fe47a29c14bf4f9af24b37365c
#include "forme.h"

typedef struct monde
{
	Joueur *joueur;
	Ennemi **liste_ennemis; 
}Monde;


/*	Affiche le monde et ses parametre dans la fenetre */
void afficherMonde(Monde *m);

/* Malloc un monde */
Monde *creerMonde();

/* Initialise texture */
GLuint *generateID(char *chemin);

/* Dessine carré */
void drawSquare();

#endif
