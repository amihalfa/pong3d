#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "includes/Coords.h"
#include "includes/Particles.h"
#include "includes/State.h"
#include "includes/Racket.h"
#include "includes/Ball.h"
#include "includes/Ground.h"
#include "includes/Menu_Item.h"
#include "includes/Config.h"
#include "includes/State_Game.h"
#include "includes/State_Menu.h"
#include "includes/Collisions.h"
#include "includes/Util.h"

/**
 *	Fonction generale de manipulation de l'etat menu
 */
State* state_menu(int action){
	
	static State* state_menu = (State*)0;
	
	if( action == STATE_CREATE && !state_menu ){
		
		state_menu = ( State* ) malloc( sizeof(State) );
		state_menu->env = ( State_Menu_Env* ) malloc( sizeof(State_Menu_Env) );
		state_menu->init_handler = &state_menu_init;
		state_menu->main_handler = &state_menu_main;
		state_menu->events_handler = &state_menu_events;
		
	}
	else if( action == STATE_DESTROY && state_menu ){
			
		free(state_menu->env);
		free(state_menu);
		state_menu = (State*)0;
	}
	

	return state_menu;
}

/**
 *	Creation de l'etat menu
 */
void state_menu_create(){
	state_menu( STATE_CREATE );
}

/**
 *	Recuperation de l'etat menu
 *	@return 	pointeur vers l'etat menu
 */
State* state_get_menu(){
	return state_menu( STATE_GET );
}

/**
 *	Liberation des ressources occupees par l'etat menu
 */
void state_menu_destroy(){
	state_menu( STATE_DESTROY );
}

/**
 *	Initialisation de l'etat menu
 *	@param	env		Envirronnement de l'etat menu
 */
void state_menu_init(State_Menu_Env* env){
	
	env->menu_item[0].position.x = 0.0f;
	env->menu_item[0].position.y = 500.0f;
	env->menu_item[0].texture = util_texture_load ("images/menu/jouer.png");
	env->menu_item[0].anim_step = 0.0f;
	env->menu_item[0].anim_dir = 1;
	
	env->menu_item[1].position.x = 0.0f;
	env->menu_item[1].position.y = 400.0f;
	env->menu_item[1].texture = util_texture_load ("images/menu/quitter.png");
	env->menu_item[1].anim_step = 0.0f;
	env->menu_item[1].anim_dir = 1;
	
	env->selected_item = 1;

	/* Pour gerer les zIndex */
	glDisable(GL_DEPTH_TEST);
	
	/* On enleve les params de la 3D */
	glDisable(GL_LIGHTING);
	glDisable(GL_COLOR_MATERIAL);
	
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	gluOrtho2D(0, 800, 0, 600);
}

/**
 *	Affichage de l'etat menu
 *	@param	env		Envirronnement de l'etat menu
 */
void state_menu_draw(State_Menu_Env* env){
	
	/* On vide le buffer d'affichage */
	glClear( GL_COLOR_BUFFER_BIT );
	
	/* Matrice de manipulation des objets */
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	
	/* On dessinne les objets de la scene */
	menu_item_draw( &(env->menu_item[0]) );
	menu_item_draw( &(env->menu_item[1]) );
	
	/* On s'assure que le dessin est termine */
	glFlush();
	
	/* On affiche */
	SDL_GL_SwapBuffers();
	
}

/**
 *	Gestion des evenements de l'etat menu
 *	@param	env		Envirronnement de l'etat menu
 */
int state_menu_events(State_Menu_Env* env){
	
	/* Variable de gestion des evenements */
	SDL_Event event;
	
	/* Etat des touches */
	Uint8 *keystates;

	while( SDL_PollEvent(&event) ){ 	
		if( event.type == SDL_QUIT ){ 
			return 0; 
		}
	}
	
	keystates = SDL_GetKeyState( NULL );
		
	if( keystates[ SDLK_RETURN ] ) { 
		switch(env->selected_item){
			case 0:
				state_set_current(state_game_get());
			break;
			default:
				return 0;
			break;	
		}
	}
		
	if( keystates[ SDLK_DOWN ] ) { 
		if(env->selected_item+1 < STATE_MENU_ITEMSNB)
			env->selected_item++;
	}
	
	if( keystates[ SDLK_UP ] ) { 
		if(env->selected_item > 0)
			env->selected_item--;
	}

	return 1;
}


void state_menu_main(State_Menu_Env* env, Uint32 e_time){
	
	animation_state_menu(env, e_time);
	state_menu_draw(env);
	
}
