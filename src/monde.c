#include "monde.h"

/* générer la texture à partir d'un nom de fichier */
GLuint GenerateTexture(char *filename){
	SDL_Surface* texture;
	texture = IMG_Load(filename);
	if(texture==NULL){
		fprintf(stderr, "Problème de chargement de la texture.\n");
	        return EXIT_FAILURE;
		}
	
	GLuint textureID;
	glGenTextures(1, &textureID);
	
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGB,
		texture->w,
		texture->h,
		0,
		GL_RGB,
		GL_UNSIGNED_BYTE,
		texture->pixels);
	
	glBindTexture(GL_TEXTURE_2D,0);

	/* libérer la mémoire allouée */
	SDL_FreeSurface(texture);
	
	return textureID;
}

