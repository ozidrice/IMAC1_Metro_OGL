#ifndef _WINDOWS_
#define _WINDOWS_

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <GL/gl.h>
#include <GL/glu.h>
	
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

float windowRatio();

unsigned int get_WINDOW_WIDTH();

unsigned int get_WINDOW_HEIGHT();

void set_WINDOW_WIDTH(unsigned int w);

void set_WINDOW_HEIGHT(unsigned int h);

#endif
