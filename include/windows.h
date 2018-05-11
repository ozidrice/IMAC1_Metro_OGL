#ifndef _WINDOWS_
#define _WINDOWS_

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <GL/gl.h>
#include <GL/glu.h>

static unsigned int WINDOW_WIDTH = 1200;
static unsigned int WINDOW_HEIGHT = 800;
	
/*	Init la fenetre
*	Return 1 if ok
*/
int initWindow();

/*	Free la fenetre*/
void freeWindow();

/*   Changement de viewport*/
void resizeViewport();

/*	Print text*/
void displayText(const char *text, int x, int y, int size, char *font_path, int r, int g, int b);

/*	 renvoie le ratio largeur/hauteur de l'image */
float windowRatio();

#endif
