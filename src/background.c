#include "background.h"

/*
* Image de fond
*/
void creerBackground(){

}


void afficheBackground(){
	glBindTexture(GL_TEXTURE_2D, *get_texture("TEXTURE_FOND"));
	traceRectanglePlein(-1.,1.,1.,-1.);
	glBindTexture(GL_TEXTURE_2D,0);

}