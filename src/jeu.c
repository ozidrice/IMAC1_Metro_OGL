#include <stdio.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "monde.h"
#include "jeu.h"

static char *WINDOW_TITLE = "Jeu -- OpenGL";
static unsigned int WINDOW_WIDTH = 800;
static unsigned int WINDOW_HEIGHT = 800;
static const unsigned int BIT_PER_PIXEL = 32;
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

/*
*   Changement de viewport
*/
void resizeViewport() {
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1., 1., -1., 1.);
    SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE);
}

/*
*   Boucle d'affichage
*/
void loop(){
    char *filename = "./img/0.png";
    GLuint textureID = generateID(filename);
    int loop = 1;
    glClearColor(0.1, 0.1, 0.1 ,1.0);
    while(loop) {
        Uint32 startTime = SDL_GetTicks();
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
        
	// Bind la texture sur un carré puis débind et désactive la texture
	glBindTexture(GL_TEXTURE_2D, textureID);
	drawSquare();
	glBindTexture(GL_TEXTURE_2D,0);
	glDisable(GL_TEXTURE_2D); 
	

        SDL_Event e;
	
        while(SDL_PollEvent(&e)) {
            switch(e.type) {

                case SDL_QUIT:
                loop = 0;
                break;

                case SDL_VIDEORESIZE:
                WINDOW_WIDTH = e.resize.w;
                WINDOW_HEIGHT = e.resize.h;
                resizeViewport();

                default:
                break;
            }
        }

        //Buffer
        SDL_GL_SwapBuffers();
        Uint32 elapsedTime = SDL_GetTicks() - startTime;
        if(elapsedTime < FRAMERATE_MILLISECONDS) {
            SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
        }
    }
	glDeleteTextures(1,&textureID);
}



/*
*	Lance une partie
*   @return : 
*       0 si fail 
*       1 si success
*/
int launch(){
	// Initialisation de la SDL
    if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
        return 0;
    }

    // Ouverture d'une fenêtre et création d'un contexte OpenGL
    if(NULL == SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE)) {
        fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
        return 0;
    }
    SDL_WM_SetCaption(WINDOW_TITLE, NULL);
        
    loop();

    // Liberation des ressources associÃ©es Ã  la SDL
    SDL_Quit();
    return 1;
}



