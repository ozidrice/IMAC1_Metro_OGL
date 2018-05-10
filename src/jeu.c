#include "jeu.h"
#include "windows.h"
#include "menu.h"

static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;  

void loop(Monde *monde);
void initKeys();
void displayText();
void handle_inputs();
void affichageHUD(Monde *m);
void freeHUD();

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
    freeHUD();
    freeMonde(monde);
    free_texture();
    freeMenu();
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
	afficheMenu();
	afficherMonde(monde);
	affichageHUD(monde);
        glDisable(GL_BLEND);
        glDisable(GL_TEXTURE_2D);

        
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
        moving(&(monde->joueur), 0, -1, 0, 0, 0, 0); 
    if(KEYS[SDLK_UP] == 1)
        moving(&(monde->joueur), 0, 1, 0, 0, 0, 0); 
    if(KEYS[SDLK_RIGHT] == 1)
        moving(&(monde->joueur), 1, 0, 0, 0, 0, 0); 
    if(KEYS[SDLK_LEFT] == 1)
        moving(&(monde->joueur), -1, 0, 0, 0, 0, 0); 
}



static GLuint *TEXTURE_COEUR = NULL;
void afficheHUD_Vie(int pv){
    if(TEXTURE_COEUR == NULL)
        TEXTURE_COEUR = generateID("img/coeur.png");

    int i;
    float posX = -.95;
    float posY = .95;
    float taille = .05;
    float ecart = .05;
    glBindTexture(GL_TEXTURE_2D, *TEXTURE_COEUR);
    for(i=0;i<pv;i++)
        traceRectanglePlein(posX+taille+i*ecart,posY-taille,posX+i*ecart,posY);
    glBindTexture(GL_TEXTURE_2D,0);
}

void affichageHUD(Monde *m){

    Joueur *j = m->joueur;
    if(j != NULL){
        afficheHUD_Vie(j->pv); 
    }
}

void freeHUD(){
    if(TEXTURE_COEUR != NULL)
        glDeleteTextures(1,TEXTURE_COEUR);
}
