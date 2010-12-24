#include <SDL/SDL.h>
#include <SDL/SDL_mouse.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "includes/Window.h"

/**
 *	Initialisation de la fenetre et de l'affichage 
 */
void window_create(){
	
	/* Resolutions possibles sous la config actuelle */
	SDL_Rect **modes;
	
	/* initialisation de la video */
	SDL_Init( SDL_INIT_VIDEO );
	
	/* Recuperation des resolutions possibles */
	modes = SDL_ListModes(NULL, SDL_FULLSCREEN|SDL_OPENGL);
	
	/* Initialisation de la fenetre */
	SDL_SetVideoMode( modes[0]->w , modes[0]->h , WINDOW_COLOR_DEPTH , SDL_FULLSCREEN|SDL_OPENGL );
	
	/* Mise en place du titre de la fenetre */
	SDL_WM_SetCaption( WINDOW_TITLE , NULL );
	
	/* On masque le curseur de la souris */
	SDL_ShowCursor(SDL_DISABLE);
}

/**
 *	Liberation de la memoire
 */
void window_destroy(){

	SDL_Quit();

}
