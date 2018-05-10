#include "menu.h"
#include "jeu.h"
#include "background.h"
#include "windows.h"
#include <SDL/SDL_ttf.h>

static GLuint *TEXTURE_MENU;
static GLuint *TEXTURE_TITRE;




int actionBouton(){
	float x = 0;
	float y = 0;
        SDL_Event e;

	float ratio = windowRatio();
   
   		while(SDL_PollEvent(&e)) {
			x = -1 + 2. * e.button.x / WINDOW_WIDTH;
			y = -(-1 + 2. * e.button.y / WINDOW_HEIGHT);
	
			if(e.type == SDL_MOUSEBUTTONUP){
				if(x > -0.1*ratio && x < 0.1*ratio ){
					if( y < -0.05*ratio && y > -0.2*ratio) {
						printf("tu vas changer ton personnage\n");
						return 2;
					}
					else if( y < -0.25*ratio  && y > -0.4*ratio){
						printf(" tu vas changer de niveau\n");	
						return 1;
					}
				}
			}	
   		}
	return 0;
}


/*
* Image Menu
*/
int afficheMenu(){
	char* path = "./img/menu.PNG";
	TEXTURE_MENU = generateID(path);
	glBindTexture(GL_TEXTURE_2D, *TEXTURE_MENU);
	traceRectanglePlein(-1,-1, 1,1);
	glBindTexture(GL_TEXTURE_2D,0);
	afficheBouton();
	afficheTitre();
	/*actionBouton(monde);*/
	return 1;
}


/*
* Free la texture Menu
*/
void freeMenu(){
	glDeleteTextures(1,TEXTURE_MENU);
}

void afficheTitre(){
	TEXTURE_TITRE = generateID("img/minimetro.png");
	glBindTexture(GL_TEXTURE_2D, *TEXTURE_TITRE);
	float ratio = windowRatio();
	traceRectanglePlein(-0.3*ratio,0 ,0.3*ratio, ratio/2); 
	glBindTexture(GL_TEXTURE_2D,0);
}


/*
* Affichage boutons
*/
void afficheBouton(){
	float ratio = windowRatio();

	// Fond noir 
	glColor3f(0,0,0);
	traceRectanglePlein(-0.3*ratio,-0.05*ratio, 0.3*ratio,-0.2*ratio);
	traceRectanglePlein(-0.3*ratio,-0.25*ratio, 0.3*ratio,-0.4*ratio);

	// Boutons blancs
	glColor3f(255,255,255);
	traceRectanglePlein(-0.1*ratio,-0.05*ratio,0.1*ratio,-0.2*ratio);
	traceRectanglePlein(-0.1*ratio,-0.25*ratio,0.1*ratio,-0.4*ratio);

	// textes 
	char* CHOISIR = "choisir son";
	char* NIVEAU = "   niveau";
	char* PERSONNAGE = "personnage";
	char* font_path ="./font/04B_30__.TTF";

	displayText(PERSONNAGE,WINDOW_WIDTH/(1.55*ratio),(WINDOW_HEIGHT/ratio)-(WINDOW_HEIGHT/(ratio*9)) ,20,font_path,0,0,255);
	displayText(CHOISIR,WINDOW_WIDTH/(1.55*ratio),(WINDOW_HEIGHT/ratio)-(WINDOW_HEIGHT/(ratio*6.5)),20,font_path, 0, 0,255);

	displayText(NIVEAU,WINDOW_WIDTH/(1.55*ratio),(WINDOW_HEIGHT/ratio)+(WINDOW_HEIGHT/(ratio*9)) ,20,font_path,255,0,0);
	displayText(CHOISIR,WINDOW_WIDTH/(1.55*ratio),(WINDOW_HEIGHT/ratio)+(WINDOW_HEIGHT/(ratio*13)),20,font_path, 255, 0,0);

	/*traceCercle(0.5,0.5,0.5);*/
	/*traceCercle(x,y,ray);*/
}


