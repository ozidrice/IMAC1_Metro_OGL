#ifndef _BACKGROUND_
#define _BACKGROUND_



#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <png.h>

#include "affichage/forme.h"
#include "affichage/texture.h"

typedef struct background
{
	GLuint *texture_background;
	float hauteur;
	float largeur;
	float vitesse;
	float posX;
}Background;


/* image de fond */
Background *creerBackground(char *path_texture, float largeur, float vitesse);

/* récupère les dimensions d'une image */
void get_png_size(char *path, int *w, int *h);

/* lit une image */
void *read_image(char *path);

/* Affiche les éléments qui appartiennent au background*/
void afficheBackground(Background *b);

void freeBackground(Background *b);
#endif
