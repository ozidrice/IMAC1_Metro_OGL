#include "menu.h"
#include "jeu.h"
#include "background.h"
#include "windows.h"
#include <SDL/SDL_ttf.h>

static GLuint *TEXTURE_MENU;
static GLuint *TEXTURE_TITRE;
static const Uint32 FRAMERATE_MILLISECONDS2 = 1000 / 60;

/* 
*  Gère l'action choisi par le joueur 
*/
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
						printf("Let's go ! \n");
						return 2;
					}
					else if( y < -0.25*ratio  && y > -0.4*ratio){
						printf("Tu nous quitte déjà ?!\n");	
						return 1;
					}
				}
			}	
   		}
	return 0;
}


/*
* Loop avec affichage du Menu et lancement du jeu 
*/
int afficheMenu(){
/*	Monde *monde = creerMonde();*/

	int loop = 1;

	if(0 == initWindow())
	        return 0;

	while(loop){

		char* path = "./img/menu.PNG";
		TEXTURE_MENU = generateID(path);
	        Uint32 startTime2 = SDL_GetTicks();
        	SDL_Event e;

        	while(SDL_PollEvent(&e)) {
        	    switch(e.type) {
        	        case SDL_QUIT:
        	        loop = 0;
        	            break;
        	        default:
        	            break;
        	    }
        	}

		
		glClear(GL_COLOR_BUFFER_BIT);
	        glEnable(GL_TEXTURE_2D);
	       	glEnable(GL_BLEND);
	    	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		ElementMenu();		

		int choix = actionBouton();
		if(choix == 2)
			loop = 0;
		if(choix == 1)
			return 1;

        	glDisable(GL_BLEND);
	        glDisable(GL_TEXTURE_2D);

        	SDL_GL_SwapBuffers();
        	Uint32 elapsedTime2 = SDL_GetTicks() - startTime2;
        	if(elapsedTime2 < FRAMERATE_MILLISECONDS2) {
        	    SDL_Delay(FRAMERATE_MILLISECONDS2 - elapsedTime2);
		}
	}


	if(launch() == 1)
		return 1;
	return 1;
}

/* 
* Permet affichage des différents éléments du menu
*/
void ElementMenu(){
	glBindTexture(GL_TEXTURE_2D, *TEXTURE_MENU);
	traceRectanglePlein(-1,-1, 1,1);
	glBindTexture(GL_TEXTURE_2D,0);
	afficheBouton();
	afficheTitre();	
}


/*
* Free la texture Menu
*/
void freeMenu(){
	glDeleteTextures(1,TEXTURE_MENU);
	glDeleteTextures(1,TEXTURE_TITRE);
}

/*
* chargement de la texture de fond
*/
void afficheTitre(){
	TEXTURE_TITRE = generateID("img/littlejourney.png");
	glBindTexture(GL_TEXTURE_2D, *TEXTURE_TITRE);
	float ratio = windowRatio();
	traceRectanglePlein(-0.5*ratio,0 ,0.5*ratio, ratio/2); 
	glBindTexture(GL_TEXTURE_2D,0);
}


/*
* Affichage boutons avec textes 
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
	/*char* CHOISIR = "choisir son";
	char* NIVEAU = "   niveau";
	char* PERSONNAGE = "personnage";*/
	char* font_path ="./font/04B_30__.TTF";

	char* JOUER = "JOUER";
	char* QUITTER = "QUITTER";

	/*displayText(PERSONNAGE,WINDOW_WIDTH/(1.55*ratio),(WINDOW_HEIGHT/ratio)-(WINDOW_HEIGHT/(ratio*9)) ,20,font_path,0,0,255);
	displayText(CHOISIR,WINDOW_WIDTH/(1.55*ratio),(WINDOW_HEIGHT/ratio)-(WINDOW_HEIGHT/(ratio*6.5)),20,font_path, 0, 0,255);

	displayText(NIVEAU,WINDOW_WIDTH/(1.55*ratio),(WINDOW_HEIGHT/ratio)+(WINDOW_HEIGHT/(ratio*9)) ,20,font_path,255,0,0);
	displayText(CHOISIR,WINDOW_WIDTH/(1.55*ratio),(WINDOW_HEIGHT/ratio)+(WINDOW_HEIGHT/(ratio*13)),20,font_path, 255, 0,0);*/

	displayText(JOUER,WINDOW_WIDTH/(1.55*ratio),(WINDOW_HEIGHT/ratio)-(WINDOW_HEIGHT/(ratio*6.5)),20,font_path, 0, 0,255);

	displayText(QUITTER,WINDOW_WIDTH/(1.55*ratio),(WINDOW_HEIGHT/ratio)+(WINDOW_HEIGHT/(ratio*13)),20,font_path, 255, 0,0);
}


