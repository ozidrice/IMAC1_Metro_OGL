#include "monde/jeu.h"
#include "affichage/windows.h"
#include "affichage/menu.h"

static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;  

void loop(Monde *monde);
void initKeys();
void displayText();
void handle_inputs();
void affichageHUD(Monde *m);
void freeHUD();
void gestionNiveau();

static int KEYS[322]; //Record status of all keys (0 == up & 1 == down)


/*
*   Lance une partie
*   @return : 
*       0 si fail 
*       1 si success
*/
int launch(){
    initKeys(); //Initialisation touches clavier
    
    
    gestionNiveau();
    
    //Free
    freeWindow();
    freeHUD();
    free_texture();
    freeMenu();
    return 1;
}

/*Charge le niveau courant et lance la partie*/
void gestionNiveau(){
    Monde *monde; 

    //Chargement du monde en fonction du niveau
    int first_time_executed = 1, niveau = 1, continuer = 1, joueur_a_reussi_niveau = 0;
    while(continuer){
        //Au premier lancement on affiche pas le menu d'entre niveau
        if(first_time_executed != 1){
            char * str_button = (joueur_a_reussi_niveau) ? "Suivant" : "Recommencer"; 
            continuer = afficheMenu(str_button);
            printf("CONTINUER : %d\n",continuer  );
        }
        
        if(continuer){
            //On charge le niveau
            monde = creerMonde(); 
            if(chargerNiveau(monde, niveau) == 0){
                continuer = 0;
            }else{
                // Lancement de la boucle d'affichage
                loop(monde);    
                joueur_a_reussi_niveau = joueur_a_gagne(monde);
                freeMonde(monde);
            }

            //Si le joueur a gagné il passe au niveau suivant
            if(joueur_a_reussi_niveau == 1)
                niveau++;  
            first_time_executed = 0;          
        }
    }
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
                set_WINDOW_WIDTH(e.resize.w);
                set_WINDOW_HEIGHT(e.resize.h);
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
        	affichageHUD(monde);
        glDisable(GL_BLEND);
        glDisable(GL_TEXTURE_2D);

        
        if(1 == est_finit(monde)){
            printf("LOL\n");
            loop=0;
        }


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
    Joueur *j = monde->joueur;
    if(KEYS[SDLK_DOWN] == 1 && j->posy-(j->taille) > -1.)
        moving(&(monde->joueur), 0, -1, 0, 0, 0, 0); 
    if(KEYS[SDLK_UP] == 1 && j->posy+(j->taille) < 1)
        moving(&(monde->joueur), 0, 1, 0, 0, 0, 0); 
    if(KEYS[SDLK_RIGHT] == 1 && j->posx+(j->taille)/2. < 1)
        moving(&(monde->joueur), 1, 0, 0, 0, 0, 0); 
    if(KEYS[SDLK_LEFT] == 1 && j->posx-(j->taille)/2. > -1.)
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
