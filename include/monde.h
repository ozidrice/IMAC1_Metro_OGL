#ifndef _MONDE_
#define _MONDE_

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Element {
	int pv;
	float posx, posy, taille;
	char* texture;
}Element;


/* Initialise joueur/ennemis/obstacle */
Element* initElement(int pv, float x, float y, float taille, char * texture);

/* Charger une image */
void ImgLoad(char *filename);

/* Initialise texture */
GLuint GenerateTexture(char *filename);

#endif
