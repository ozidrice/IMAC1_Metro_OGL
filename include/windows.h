#ifndef _WINDOWS_
#define _WINDOWS_

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>


static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

/*	Init la fenetre
*	Return 1 if ok
*/
int initWindow();

/* Free la fenetre*/
void freeWindow();

/*   Changement de viewport*/
void resizeViewport();

/*	Print text*/
void displayText(const char *text, int x, int y, int size, char *font_path, int r, int g, int b);
#endif
