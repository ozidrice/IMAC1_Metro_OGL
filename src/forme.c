#include "forme.h"


/*
*   Trace le rectangle avec TopLeft le point en haut à gauche et BottomRight le point en bas à droite
*/
void traceRectanglePlein(float xTopLeft, float yTopLeft, float xBottomRigth, float yBottomRight){
    glBegin(GL_QUADS);
	glTexCoord2f(0,1);
	glVertex2f(xTopLeft,yTopLeft);
	glTexCoord2f(1,1);
	glVertex2f(xBottomRigth,yTopLeft);
	glTexCoord2f(1,0);
	glVertex2f(xBottomRigth,yBottomRight);
	glTexCoord2f(0,0);
	glVertex2f(xTopLeft,yBottomRight);
	glEnd();
}
