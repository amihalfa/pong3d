#include "includes/Window.h"
#include <SDL/SDL.h>
#include <SDL/SDL_mouse.h>
#include <GL/gl.h>
#include <GL/glu.h>

/**
 *	Initialisation de la fenetre et de l'affichage 
 */
void window_create(Uint16* height, Uint16* width){
	
	
	float ratio;
	
	/* Resolutions possibles sous la config actuelle */
	SDL_Rect **modes;
	
	/* Surface principale */
	SDL_Surface* screen;
	
	/* initialisation de la video */
	SDL_Init( SDL_INIT_VIDEO );
	
	/* Recuperation des resolutions possibles */
	modes = SDL_ListModes(NULL, SDL_FULLSCREEN|SDL_OPENGL);
	
	/* recuêration de la hauteur et largeur de la fenetre */
	*height = modes[0]->h;
	*width = modes[0]->w;

	/* Calcul du ratio de la resolution */
	ratio = (float) *width / *height;
	
	/* Initialisation de la fenetre */
	screen = SDL_SetVideoMode( *width , *height , WINDOW_COLOR_DEPTH , SDL_FULLSCREEN|SDL_OPENGL );
	
	/* Mise en place du titre de la fenetre */
	SDL_WM_SetCaption( WINDOW_TITLE , NULL );
	
	/* On masque le curseur de la souris */
	SDL_ShowCursor(SDL_DISABLE);

	/* Pour gerer les zIndex */
	glEnable(GL_DEPTH_TEST);
	
	/* Mise en place de la projection en perspective */
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	
	gluPerspective( 40 , ratio , 1 , 1000);
	
	/* Mise en place des spots d'eclairage */
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);

}

/**
 *	Liberation de la memoire
 */
void window_destroy(){

	SDL_Quit();

}
