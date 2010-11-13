#include <GL/gl.h>
#include <GL/glu.h>
#include "includes/Window.h"
#include "includes/Racket.h"
#include "includes/Ball.h"
#include "includes/Ground.h"
#include "includes/State.h"
#include "includes/Menu_Item.h"
#include "includes/Util.h"
#include "includes/State_Game.h"
#include "includes/State_Menu.h"

/**
 *	Programme principal Pong
 *	Creation de la fenetre
 *	Permet le basculement entre les differents etats de l'application
 */
int main(int argc, char **argv){
	
	state_menu_create();
	state_game_create();
	
	window_create();
	
	state_current_change(state_menu_get());
	
	while( state_current_get()->events_handler( state_current_get()->env ) ){
		
		state_current_get()->draw_handler( state_current_get()->env );
		
	}
	
	window_destroy();
	
	state_menu_destroy();
	state_game_destroy();
	
	return 0;
}