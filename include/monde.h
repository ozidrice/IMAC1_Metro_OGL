#ifndef _MONDE_
#define _MONDE_

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>

/* Charger une image */
void ImgLoad(char *filename);

/* Initialise texture */
GLuint GenerateTexture(char *filename);

#endif
