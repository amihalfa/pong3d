#include <GL/gl.h>
#include <GL/glu.h>
#include "includes/Window.h"
#include "includes/Racket.h"
#include "includes/Ball.h"
#include "includes/Ground.h"
#include "includes/State.h"
#include "includes/State_Game.h"

/**
 *	Programme principal Pong
 *	Creation de la fenetre
 *	Permet le basculement entre les differents etats de l'application
 */
int main(){

	state_game_create();
	
	state_current_change(state_game_get());
	
	window_create();

	state_current_get()->init_handler( state_current_get()->env );
	
	while( state_current_get()->events_handler( state_current_get()->env ) ){
		
		state_current_get()->draw_handler( state_current_get()->env );
		
	}
	
	window_destroy();
	
	state_game_destroy();
	
	return 0;
}