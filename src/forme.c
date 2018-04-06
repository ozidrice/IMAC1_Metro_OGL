#include "forme.h"


/*
*   Trace le rectangle avec TopLeft le point en haut à gauche et BottomRight le point en bas à droite
*/
void traceRectanglePlein(float xTopLeft, float yTopLeft, float xBottomRigth, float yBottomRight){
    glBegin(GL_QUADS);
	glVertex2f(xTopLeft,yTopLeft);
	glVertex2f(xBottomRigth,yTopLeft);
	glVertex2f(xBottomRigth,yBottomRight);
	glVertex2f(xTopLeft,yBottomRight);
	glEnd();
}
