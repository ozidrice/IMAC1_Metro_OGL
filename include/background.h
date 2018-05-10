#ifndef _BACKGROUND_
#define _BACKGROUND_



#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <png.h>

#include "forme.h"
#include "texture.h"

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

void get_png_size(char *path, int *w, int *h);

void *read_image(char *path);

void afficheBackground(Background *b);
#endif
