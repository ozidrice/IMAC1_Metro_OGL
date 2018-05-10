#include "forme.h"
#include <math.h>


#define NB_SEGMENTS 100

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

void traceCercle(float xOrigine, float yOrigine, float ray){
	int i;
	glBegin(GL_POLYGON);
	float delta = 2 * M_PI / (float) NB_SEGMENTS;
	for(i=0; i<100; i++){
        glColor3ub(255,255,255);
		float x = ((cos(i * delta)))*xOrigine;// truc RATIO
		float y = ((sin(i * delta)))*xOrigine; // truc RATIO
		glVertex2f(x,y);
	}
	glEnd();
}
	
