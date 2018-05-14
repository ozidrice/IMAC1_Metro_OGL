#ifndef _FORME_
#define _FORME_

#include <GL/gl.h>

/*
*   Trace le rectangle avec TopLeft le point en haut à gauche et BottomRight le point en bas à droite
*/
void traceRectanglePlein(float xTopLeft, float yTopLeft, float xBottomRigth, float yBottomRight);

/*
* Trace un cercle 
*/
void traceCercle(float xOrigine, float yOrigine, float ray);

#endif
