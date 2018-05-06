#include "jeu.h"
#include "windows.h"

static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;  

void loop(Monde *monde);
void initKeys();
void displayText();
void handle_inputs();

static int KEYS[322]; //Record status of all keys (0 == up & 1 == down)

/*
*   Lance une partie
*   @return : 
*       0 si fail 
*       1 si success
*/
int launch(){
    if(0 == initWindow())
        return 0;
    initKeys(); //Initialisation touches clavier
    preload_texture(); //Initialisation des textures
    Monde *monde = creerMonde(); //Creation du monde
    LancerMonde(monde, 1);

    //Lancement de la boucle d'affichage
    loop(monde);
    
    //Free
    freeWindow();
    freeMonde(monde);
    free_texture();
    return 1;
}



/*
*   Boucle d'affichage
*/
void loop(Monde *monde){
    int loop = 1;    
    while(loop) {
        Uint32 startTime = SDL_GetTicks();

        //Detection des évènements
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
                    break;
                case SDL_KEYDOWN:
                    KEYS[e.key.keysym.sym] = 1;
                    break;
                case SDL_KEYUP:
                    KEYS[e.key.keysym.sym] = 0;
                    break;
                default:
                    break;
            }
        }
        handle_inputs(monde);
        action(monde);

        glClear(GL_COLOR_BUFFER_BIT);
        glEnable(GL_TEXTURE_2D);
    	glEnable(GL_BLEND);
    	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
            afficherMonde(monde);
        glDisable(GL_BLEND);
        glDisable(GL_TEXTURE_2D);

        displayText("Coucou c'est moi",0,0,18,"font/04B_30__.TTF",255,255,255);
        
        //Buffer
        SDL_GL_SwapBuffers();
        Uint32 elapsedTime = SDL_GetTicks() - startTime;
        if(elapsedTime < FRAMERATE_MILLISECONDS) {
            SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
        }
    }
}


/*
*   Initialise toutes les touches à relachée 
*/
void initKeys(){
    for(int i = 0; i < 322; i++)
       KEYS[i] = 0;
}

/*
*   Traite les entrées du clavier
*/
void handle_inputs(Monde *monde){
    if(KEYS[SDLK_DOWN] == 1)
        moving(&(monde->joueur), 0, -1, 0); 
    if(KEYS[SDLK_UP] == 1)
        moving(&(monde->joueur), 0, 1, 0); 
    if(KEYS[SDLK_RIGHT] == 1)
        moving(&(monde->joueur), 1, 0, 0); 
    if(KEYS[SDLK_LEFT] == 1)
        moving(&(monde->joueur), -1, 0, 0); 
}
