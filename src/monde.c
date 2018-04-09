#include "monde.h"

/* génère texture à partir d'un chemin en paramètres */
GLuint generateID(char *chemin){
	SDL_Surface* texture_img;
		texture_img= IMG_Load(chemin);
		if(texture_img==NULL){
			fprintf(stderr, "Le pointeur est NULL, déso.\n");
		        return EXIT_FAILURE;
		}
	GLuint textureID;
	glGenTextures(1,&textureID);
	
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGBA,
		texture_img->w,
		texture_img->h,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		texture_img->pixels);

	glBindTexture(GL_TEXTURE_2D,0);
	SDL_FreeSurface(texture_img);
	return textureID;
}

void drawSquare(){
	glBegin(GL_QUADS);
		glTexCoord2f(0,1);
		glVertex2f(-0.5,-0.5);
		glTexCoord2f(1,1);
		glVertex2f(0.5,-0.5);
		glTexCoord2f(1,0);
		glVertex2f(0.5,0.5);
		glTexCoord2f(0,0);
		glVertex2f(-0.5,0.5);
	glEnd();
}

