#include "windows.h"
#define glVertex2px(x,y) glVertex2d((double)(x) * 2.0 / (double)WINDOW_WIDTH - 1.0, 1.0 - (double)(y) * 2.0 / (double)WINDOW_HEIGHT);

static const unsigned int BIT_PER_PIXEL = 32;
static unsigned int WINDOW_WIDTH = 800;
static unsigned int WINDOW_HEIGHT = 800;
static char *WINDOW_TITLE = "Jeu -- OpenGL"; 

/*
*	Return 1 if ok
*/
int initWindow(){
	// Initialisation de la SDL
    if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
        return 0;
    }


    // Ouverture d'une fenêtre et création d'un contexte OpenGL
    if(!SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE | SDL_HWSURFACE | SDL_DOUBLEBUF)){
        fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
        return 0;
    }
    SDL_WM_SetCaption(WINDOW_TITLE, NULL);
    
    TTF_Init();
    return 1;
}

/* 
*	Free la fenetre
*/
void freeWindow(){
	SDL_Quit();
}


/*
*   Changement de viewport
*/
void resizeViewport() {
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1., 1., -1., 1.);
    SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE | SDL_HWSURFACE | SDL_DOUBLEBUF);
}


/*
*	Print text
* 	(Readapted from stackoverflow)
*/
void displayText(const char *text, int x, int y, int size, char *font_path, int r, int g, int b) {
	SDL_Color color = {r, g, b};
	TTF_Font *font = TTF_OpenFont(font_path, size);

    GLuint texture;
    SDL_Surface *surface;
    surface = TTF_RenderText_Blended(font,text,color);
    
    glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    glGenTextures(1,&texture);
    glBindTexture(GL_TEXTURE_2D,texture);
    
    gluBuild2DMipmaps(GL_TEXTURE_2D,4,surface->w,surface->h,GL_RGBA,GL_UNSIGNED_BYTE,surface->pixels);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    
    GLboolean textureIsEnabled = glIsEnabled(GL_TEXTURE_2D);
    
    glEnable(GL_TEXTURE_2D);
    glColor3ub(255,255,255);
    glBegin(GL_QUADS);
        glTexCoord2f(0,0);
        glVertex2px(x,y);
        glTexCoord2f(0,1);
        glVertex2px(x,y + surface->h);
        glTexCoord2f(1,1);
        glVertex2px(x + surface->w,y + surface->h);
        glTexCoord2f(1,0);
        glVertex2px(x + surface->w,y);
    glEnd();
    if(!textureIsEnabled){
        glDisable(GL_TEXTURE_2D);
    }

	TTF_CloseFont(font);
    glDeleteTextures(1, &texture);
	SDL_FreeSurface(surface);
}