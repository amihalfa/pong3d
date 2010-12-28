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
		((State_Menu_Env*)(state_menu->env))->mouse.x = ((State_Menu_Env*)(state_menu->env))->w_width / 2.0f;
		((State_Menu_Env*)(state_menu->env))->mouse.y = ((State_Menu_Env*)(state_menu->env))->w_height / 2.0f;
		
		SDL_Thread *mon_thread = SDL_CreateThread(state_menu_cursor_handler, state_menu->env);
	
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
	
	int i, j;
	env->mouse_texture = util_texture_load("images/menu/souris.png");
	
	/* Enregistrements des nombres d'elements par menu */
	env->itemsnb[STATE_MENU_HOME] = 3;
	env->itemsnb[STATE_MENU_CONTINUE] = 4;
	env->itemsnb[STATE_MENU_PLAY] = 4;
	
	for(i = 0; i < STATE_MENU_PAGES; i++){
		
		GLfloat first_item_x = env->w_width / 2 - 150.0 * (GLfloat)(env->itemsnb[i]) / 2.0;
		for(j = 0; j < env->itemsnb[i]; j++){
			
			env->menu_item[i][j].position.x = first_item_x + j * 150;
			env->menu_item[i][j].position.y = 250.0f;
			env->menu_item[i][j].anim_step = 0.0f;
			env->menu_item[i][j].anim_dir = 1;
		}
	}
	
	env->menu_item[STATE_MENU_HOME][0].texture = util_texture_load ("images/menu/jouer.png");
	env->menu_item[STATE_MENU_HOME][1].texture = util_texture_load ("images/menu/config.png");
	env->menu_item[STATE_MENU_HOME][2].texture = util_texture_load ("images/menu/quitter.png");
	
	env->menu_item[STATE_MENU_CONTINUE][0].texture = util_texture_load ("images/menu/reprendre.png");
	env->menu_item[STATE_MENU_CONTINUE][1].texture = util_texture_load ("images/menu/jouer.png");
	env->menu_item[STATE_MENU_CONTINUE][2].texture = util_texture_load ("images/menu/config.png");
	env->menu_item[STATE_MENU_CONTINUE][3].texture = util_texture_load ("images/menu/quitter.png");
	
	env->menu_item[STATE_MENU_PLAY][0].texture = util_texture_load ("images/menu/facile.png");
	env->menu_item[STATE_MENU_PLAY][1].texture = util_texture_load ("images/menu/moyen.png");
	env->menu_item[STATE_MENU_PLAY][2].texture = util_texture_load ("images/menu/difficile.png");
	env->menu_item[STATE_MENU_PLAY][3].texture = util_texture_load ("images/menu/retour.png");
	
	
	env->selected_item = 0;
	if(state_game_get_pause() == 0)
		env->selected_page = STATE_MENU_HOME;
	else
		env->selected_page = STATE_MENU_CONTINUE;
	
	env->logo_texture = util_texture_load("images/menu/logo.png");
	env->top_texture = util_texture_load("images/menu/haut.png");
	env->bottom_texture = util_texture_load("images/menu/bas_fond.png");
	env->footer_texture = util_texture_load("images/menu/bas.png");
	
	/* On enleve les params de la 3D */
	glDisable(GL_DEPTH_TEST);
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
	
	int i;
	
	/* On vide le buffer d'affichage */
	glClear( GL_COLOR_BUFFER_BIT );
	
	/* Matrice de manipulation des objets */
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	
	/* On dessinne le panneau du haut */
 	util_texture_display(env->top_texture, 0.0f, 500.0f, env->w_width, 100.0f);
	
	/* On dessinne le logo par dessus le panneau du haut */
 	util_texture_display(env->logo_texture, env->w_width/2.0f - 180.0f, 520.0f, 320.0f, 80.0f);
	
	/* On dessinne le bas de page */
 	util_texture_display(env->bottom_texture, 0.0f, 0.0f, env->w_width, 16.0f);
	util_texture_display(env->footer_texture, env->w_width/2.0f - 128.0f, 0, 256.0f, 32.0f);
	
	/* On dessinne les objets de la scene */
	for(i = 0; i < env->itemsnb[env->selected_page]; i++){
		menu_item_draw( &(env->menu_item[env->selected_page][i]) );
	}
	
	/* Dessin de la souris */
	util_texture_display(env->mouse_texture, env->mouse.x, env->mouse.y, 32.0f, 32.0f);
	
	
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
	while(SDL_PollEvent(&event)){
		/* Analyse de l'evenement */
		switch(event.type){
			case SDL_QUIT:
				return 0;
			break;
			case SDL_KEYDOWN:
				if(event.key.keysym.sym == SDLK_ESCAPE)
					return 0;
				break;
			case SDL_MOUSEBUTTONDOWN:
				if(state_menu_select_item(env) == 0){
					return 0;
				}
				break;
			default:
				break;
		}
	}
	return 1;
}

int state_menu_select_item(State_Menu_Env* env){
	switch(env->selected_page){
		case STATE_MENU_HOME:
			switch(env->selected_item){
				case 0:
					env->selected_item = 0;
					env->selected_page = STATE_MENU_PLAY;
					break;
				case 1:
					break;
				case 2:
					return 0;
					break;
				default:
					break;
			}
			break;
		case STATE_MENU_CONTINUE:
			switch(env->selected_item){
				case 0:
					state_set_current(state_game_get());
					break;
				case 1:
					env->selected_item = 0;
					env->selected_page = STATE_MENU_PLAY;
					break;
				case 3:
					return 0;
					break;
				default:
					break;
			}
			break;
		case STATE_MENU_PLAY:
			switch(env->selected_item){
				case 0:
					state_game_set_pause(0);
					state_set_current(state_game_get());
					break;
				case 1:
					state_game_set_pause(0);
					state_set_current(state_game_get());
					break;
				case 3:
					env->selected_item = 0;
					if(state_game_get_pause() != 0)
						env->selected_page = STATE_MENU_CONTINUE;
					else
						env->selected_page = STATE_MENU_HOME;
					break;
				default:
					break;
			}
			break;	
		default:
			break;
	}
	return 1;
}

void state_menu_main(State_Menu_Env* env, Uint32 e_time){
	
	env->ellapsed_time = e_time;
	animation_state_menu(env, e_time);
	state_menu_draw(env);
	
}

void state_menu_move_cursor(State_Menu_Env* env){
	
	Coord2d move;
	
	/* S'il ya eu reellement un mouvement */
	if ( env->mouse_motion.x != 0 && env->mouse_motion.y != 0){
		/* Si la souris ne sort pas de l'ecran */
		move.x = env->mouse.x + (GLfloat)env->ellapsed_time/10.0 * env->mouse_motion.x;
		move.y = env->mouse.y + (GLfloat)env->ellapsed_time/10.0 * env->mouse_motion.y;
		
		if(move.x >= 0 && move.x <= env->w_width)
			env->mouse.x = move.x;
		
		if(move.y > 0 && move.y <= env->w_height)
			env->mouse.y = move.y;
	}
	
}


/**
 *	Thread pour changer la position de la souris
 */ 
int state_menu_cursor_handler(void* e){
	
	State_Menu_Env* env = e;
	int rel_x, rel_y, i;
	
	while(1){
		
		SDL_Delay(10);
		
		/* Recuperation de la position relative de la souris */
		SDL_GetRelativeMouseState(&rel_x, &rel_y);	
		
		env->mouse_motion.y = -(GLfloat)rel_y;
		env->mouse_motion.x = (GLfloat)rel_x;
		
		state_menu_move_cursor(env);
		
		for(i = 0; i < env->itemsnb[env->selected_page]; i++){
			if( menu_item_mouse_over(&(env->menu_item[env->selected_page][i]), &env->mouse) ){
				env->selected_item = i;
			}
		}
		
	}
	return 0;
}