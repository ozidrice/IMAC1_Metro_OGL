#include<arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include "affichage/background.h"


void get_png_size(char *path, int *w, int *h);
void *read_image(char *path);

/*
* Image de fond
*/
Background *creerBackground(char *path_texture, float largeur, float vitesse){
	Background *b = malloc(sizeof(Background));
	if(b != NULL){
		b->texture_background = generateID(path_texture);
		int w,h;
		get_png_size(path_texture,&w,&h);
		float ratio_texture = (w/(h*1.))/2.;
		b->largeur = largeur;
		b->hauteur = largeur/ratio_texture;
		b->vitesse = vitesse;  
		b->posX = 0;
	}
	return b;
}


void afficheBackground(Background *b){
	glBindTexture(GL_TEXTURE_2D, *b->texture_background);
	float demi_largeur = b->largeur/2;
	float demi_hauteur = b->hauteur/2;
	traceRectanglePlein(-demi_largeur+b->posX,-demi_hauteur,demi_largeur+b->posX,demi_hauteur);
	glBindTexture(GL_TEXTURE_2D,0);
	if(b->largeur-2 + b->posX > 2){
		if(b->largeur-2 + b->posX < 4){
			b->posX-=b->vitesse*(((b->posX+4)/4)-.5)*2;
		}else{
			b->posX-=b->vitesse;
		}
	}

}


void freeBackground(Background *b){
	glDeleteTextures(1,b->texture_background);
}



/*
*	Retourne la largeur et longueur de l'image
*/
void get_png_size(char *path, int *w, int *h){
	char *ptr=read_image(path);
	uint32_t *point1=ptr+16;
	uint32_t *point2=ptr+20;
	uint32_t point1_res=ntohl(*point1);
	uint32_t point2_res=ntohl(*point2);
	*w = point1_res;
	*h = point2_res;	
}


/*
*	Lit l'image
*/
void *read_image(char *path) {
	int fd = open(path, O_RDONLY);
	if (fd < 0) {
		return NULL;
	}
	size_t size = 1000;
	size_t offset = 0;
	size_t res;
	char *buff = malloc(size);

	while((res = read(fd, buff + offset, 100)) != 0) {
	    offset += res;
	    if (offset + 100 > size) {
	            size *= 2;
	            buff = realloc(buff, size);
	    }
	}
	close(fd);
	return buff; 
}

