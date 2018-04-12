#ifndef _JEU_
#define _JEU_


#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <png.h>

#include "monde.h"
#include "element.h"
/*
*	Lance une partie
*   @return : 
*       0 si fail 
*       1 si success
*/
int launch();


/*
*	Boucle d'affichage
*/
void loop();

#endif
