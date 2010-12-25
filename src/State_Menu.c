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
		state_menu->env = (State_Menu_Env*) malloc( sizeof(State_Menu_Env) );
		state_menu->init_handler = &state_menu_init;
		state_menu->main_handler = &state_menu_main;
		state_menu->events_handler = &state_menu_events;
		
		SDL_Rect **modes = SDL_ListModes(NULL, SDL_FULLSCREEN|SDL_OPENGL);
		GLfloat ratio = (GLfloat)modes[0]->w/(GLfloat)modes[0]->h;
		
 		if(ratio >= 1.33){
			((State_Menu_Env*)(state_menu->env))->w_width = 600.0f * ratio; 
			((State_Menu_Env*)(state_menu->env))->w_height = 600.0f;
		} else {
			((State_Menu_Env*)(state_menu->env))->w_width = 800.0f; 
			((State_Menu_Env*)(state_menu->env))->w_height = 800.0f * ratio;
		} 
		
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
	
	GLfloat first_item_x = env->w_width/2-150.0*3.0/2.0;
	
	env->menu_item[0].position.x = first_item_x;
	env->menu_item[0].position.y = 250.0f;
	env->menu_item[0].texture = util_texture_load ("images/menu/jouer.png");
	env->menu_item[0].anim_step = 0.0f;
	env->menu_item[0].anim_dir = 1;
	
	env->menu_item[1].position.x = first_item_x +150;
	env->menu_item[1].position.y = 250.0f;
	env->menu_item[1].texture = util_texture_load ("images/menu/config.png");
	env->menu_item[1].anim_step = 0.0f;
	env->menu_item[1].anim_dir = 1;
	
	env->menu_item[2].position.x = first_item_x+300;
	env->menu_item[2].position.y = 250.0f;
	env->menu_item[2].texture = util_texture_load ("images/menu/quitter.png");
	env->menu_item[2].anim_step = 0.0f;
	env->menu_item[2].anim_dir = 1;
	
	env->selected_item = 0;
	
	env->logo_texture = util_texture_load("images/menu/logo.png");
	env->top_texture = util_texture_load("images/menu/haut.png");
	
	/* Pour gerer les zIndex */
	glDisable(GL_DEPTH_TEST);
	
	/* On enleve les params de la 3D */
	glDisable(GL_LIGHTING);
	glDisable(GL_COLOR_MATERIAL);
	
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	
	gluOrtho2D(0.0f, env->w_width, 0.0f, env->w_height);
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
	
	/* On dessinne le panneau du haut */
 	util_texture_display(env->top_texture, 0.0f, 500.0f, env->w_width, 100.0f);
	
	/* On dessinne le logo par dessus le panneau du haut */
 	util_texture_display(env->logo_texture, env->w_width/2.0f - 180.0f, 520.0f, 320.0f, 80.0f);
	
	/* On dessinne les objets de la scene */
	menu_item_draw( &(env->menu_item[0]) );
	menu_item_draw( &(env->menu_item[1]) );
	menu_item_draw( &(env->menu_item[2]) );
	
	
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
	
	/* Pour recuperer la touche pressee */
	int key_pressed;
	
	/* Recuperation d'un evenement */
	SDL_PollEvent(&event);
	
	/* Analyse de l'evenement */
	switch(event.type){
		case SDL_QUIT:
			return 0;
		break;
		case SDL_KEYDOWN:
			switch(event.key.keysym.sym){
				case SDLK_RETURN:
					key_pressed = SDLK_RETURN;
				break;
				case SDLK_LEFT:
					key_pressed = SDLK_LEFT;
				break;
				case SDLK_RIGHT:
					key_pressed = SDLK_RIGHT;
				break;
				default:
					return 1;
				break;
			}
		break;
	}
	
	/* Touche entree pressee */
	if( key_pressed == SDLK_RETURN ) { 
		switch(env->selected_item){
			case 0:
				state_set_current(state_game_get());
			break;
			default:
				return 0;
			break;	
		}
	}
	
	/* Fleche gauche pressee */
	else if(key_pressed == SDLK_RIGHT) { 
		if(env->selected_item+1 < STATE_MENU_ITEMSNB)
			env->selected_item++;
	}
	
	/* Fleche droite pressee */
	else if(key_pressed == SDLK_LEFT) { 
		if(env->selected_item > 0)
			env->selected_item--;
	}

	return 1;
}


void state_menu_main(State_Menu_Env* env, Uint32 e_time){
	
	animation_state_menu(env, e_time);
	state_menu_draw(env);
	
}
