#ifndef _TEXTURE_
#define _TEXTURE_



#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <png.h>

/*	Free les textures chargés */
void free_texture();

/*	Précharge les textures pour pouvoir les utiliser plus tard */
void preload_texture();

/* Retourne la texture choisie*/
GLuint *get_texture(char *str);

/* Initialise texture */
GLuint *generateID(char *chemin);
#endif
