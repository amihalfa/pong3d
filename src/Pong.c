#include <SDL/SDL.h>
#include "includes/Window.h"
#include "includes/Util.h"
#include "includes/State_Game.h"
#include "includes/State_Menu.h"

#define FRAME_DURATION 10

/**
 *	Programme principal Pong
 *	Creation de la fenetre
 *	Permet le basculement entre les differents etats de l'application
 */
int main(int argc, char **argv){
	
	Uint32 s_time, e_time = 0;
	
	/* Creation des differents etats de l'application */
	state_menu_create();
	state_game_create();
	
	/* Mise en place du fenetrage */
	window_create();
	
	/* Mise en place de l'etat courant */
	current_state_set(state_menu_get());
	
	s_time = SDL_GetTicks();
	
	/* Boucle de gestion des evenements et de l'affichage */
	while( current_state_events( e_time ) ){
		
		/* Fonction principale de l'etat courant */
		current_state_main( e_time );
		
		e_time = SDL_GetTicks() - s_time;
			
		if (e_time < FRAME_DURATION){
			SDL_Delay(FRAME_DURATION - e_time);
		}
		
		s_time = SDL_GetTicks();
	}
	
	window_destroy();
	
	state_menu_destroy();
	state_game_destroy();
	
	return 0;
}
