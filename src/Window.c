#include "includes/Window.h"
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

/**
 *	Initialisation de la fenetre et de l'affichage 
 */
void window_create(){
	
	
	float ratio;
	
	/* Resolutions possibles sous la config actuelle */
	SDL_Rect **modes;
	
	/* Surface principale */
	SDL_Surface* screen;
	
	/* initialisation de la video */
	SDL_Init( SDL_INIT_VIDEO );
	
	/* Recuperation des resolutions possibles */
	modes = SDL_ListModes(NULL, SDL_FULLSCREEN|SDL_OPENGL);
	
	/* Calcul du ratio de la resolution */
	ratio = (float) modes[0]->w / modes[0]->h;
	
	/* Initialisation de la fenetre */
	screen = SDL_SetVideoMode( modes[0]->w , modes[0]->h , WINDOW_COLOR_DEPTH , SDL_FULLSCREEN|SDL_OPENGL );
	
	/* Mise en place du titre de la fenetre */
	SDL_WM_SetCaption( WINDOW_TITLE , NULL );
	
	/* On masque le curseur de la souris */
	/*SDL_ShowCursor(SDL_DISABLE);*/
	
	/* Pour gérer les zIndex */
	glEnable(GL_DEPTH_TEST);
	
	/* Mise en place de la projection en perspective */
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	
	gluPerspective( 40 , ratio , 1 , 1000);
	
	/* Mise en place des spots d'éclairage */
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	
}

/**
 *	Liberation de la memoire
 */
void window_destroy(){

	SDL_Quit();

}
