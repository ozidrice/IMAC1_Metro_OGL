#include "affichage/menu.h"
#include "monde/jeu.h"
#include "affichage/background.h"
#include "affichage/windows.h"
#include <SDL/SDL_ttf.h>

static const Uint32 FRAMERATE_MILLISECONDS2 = 1000 / 60;

/*
* Loop avec affichage du Menu et lancement du jeu 
*/
int afficheMenu(char *str_button1, int fin){
/*	Monde *monde = creerMonde();*/

	int loop = 1;
	if(0 == initWindow())
	        return 0;
	
	preload_texture();
	

	while(loop){
	        Uint32 startTime2 = SDL_GetTicks();
        	SDL_Event e;


			float ratio, x = 0, y = 0;
        	while(SDL_PollEvent(&e)) {
        	    switch(e.type) {
        	        case SDL_QUIT:
        	        	loop = 0;
        	        	return 0;
        	        case SDL_MOUSEBUTTONUP:

						ratio = windowRatio(); 
        	        	x = -1 + 2. * e.button.x / get_WINDOW_WIDTH();
						y = -(-1 + 2. * e.button.y / get_WINDOW_HEIGHT());
				
						if(x > -0.1*ratio && x < 0.1*ratio ){
							if( y < -0.05*ratio && y > -0.2*ratio) {
								printf("Let's go ! \n");
								loop = 0;
							}
							else if( y < -0.25*ratio  && y > -0.4*ratio){
								printf("Tu nous quitte déjà ?!\n");	
								return 0;
							}
						}
						
						break;
        	        default:
        	            break;
        	    }
        	}
		
		glClear(GL_COLOR_BUFFER_BIT);
	        glEnable(GL_TEXTURE_2D);
	       	glEnable(GL_BLEND);
	    	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		ElementMenu(str_button1,fin);		

        	glDisable(GL_BLEND);
	        glDisable(GL_TEXTURE_2D);

        	SDL_GL_SwapBuffers();
        	Uint32 elapsedTime2 = SDL_GetTicks() - startTime2;
        	if(elapsedTime2 < FRAMERATE_MILLISECONDS2) {
        	    SDL_Delay(FRAMERATE_MILLISECONDS2 - elapsedTime2);
		}
	}
	return 1;
}

/* 
* Permet affichage des différents éléments du menu
*/
void ElementMenu(char *str_button1, int fin){
	if (fin == 0){
		GLuint *texture_menu = get_texture("TEXTURE_MENU");
		glBindTexture(GL_TEXTURE_2D, *texture_menu);
		traceRectanglePlein(-1,-1, 1,1);
		glBindTexture(GL_TEXTURE_2D,0);
		afficheBouton(str_button1);
		afficheTitre();	
	}
	else{
		char* font_path ="bin/font/Moon Flower.ttf";
		GLuint *texture_menu = get_texture("TEXTURE_MENU");
		glBindTexture(GL_TEXTURE_2D, *texture_menu);
		traceRectanglePlein(-1,-1, 1,1);
		displayText(str_button1,220,100,100,font_path, 0, 0,0);
	}
}


/*
* Free la texture Menu
*/
void freeMenu(){
}

/*
* chargement de la texture de fond
*/
void afficheTitre(){
	GLuint *texture_titre = get_texture("TEXTURE_TITRE");
	glBindTexture(GL_TEXTURE_2D, *texture_titre);
	float ratio = windowRatio();
	traceRectanglePlein(-0.4*ratio,0,0.4*ratio, ratio/2.5); 
	glBindTexture(GL_TEXTURE_2D,0);
}


/*
* Affichage boutons avec textes 
*/
void afficheBouton(char *str_button1){
	float ratio = windowRatio();

	// Boutons blancs
	glColor3f(255,255,255);
	traceRectanglePlein(-0.1*ratio,-0.05*ratio,0.1*ratio,-0.2*ratio);
	traceRectanglePlein(-0.1*ratio,-0.25*ratio,0.1*ratio,-0.4*ratio);

	char* font_path ="bin/font/Moon Flower.ttf";
	char* BUTTON_1 = str_button1;
	char* QUITTER = "QUITTER";

	displayText(BUTTON_1,get_WINDOW_WIDTH()/(1.55*ratio),(get_WINDOW_HEIGHT()/ratio)-(get_WINDOW_HEIGHT()/(ratio*6.2)),50,font_path, 0, 0,0);

	displayText(QUITTER,get_WINDOW_WIDTH()/(1.52*ratio),(get_WINDOW_HEIGHT()/ratio)+(get_WINDOW_HEIGHT()/(ratio*17)),70,font_path, 0, 0,0);
}



