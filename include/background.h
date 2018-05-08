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
	float posX;
}Background;


/* image de fond */
void creerBackground();

void afficheBackground();
#endif
