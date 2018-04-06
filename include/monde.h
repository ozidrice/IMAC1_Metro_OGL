#ifndef _MONDE_
#define _MONDE_

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>

/* Initialise texture */
GLuint generateID(char *chemin);

/* Dessine carré */
void drawSquare();

#endif
