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
		config_load_state_menu((State_Menu_Env*)(state_menu->env));
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
	
	/* Chargement de la texture pour le curseur de la souris */
	env->mouse_texture = util_texture_load("images/menu/souris.png");

	/* Enregistrements des nombres d'elements par menu */
	env->itemsnb[STATE_MENU_HOME] = 3;
	env->itemsnb[STATE_MENU_CONTINUE] = 4;
	env->itemsnb[STATE_MENU_PLAY] = 4;
	env->itemsnb[STATE_MENU_CONFIG] = 5;

	for(i = 0; i < STATE_MENU_PAGES; i++){

		GLfloat first_item_x = env->w_width / 2 - 150.0 * (GLfloat)(env->itemsnb[i]) / 2.0;
		for(j = 0; j < env->itemsnb[i]; j++){

			env->menu_item[i][j].position.x = first_item_x + j * 150;
			env->menu_item[i][j].position.y = 250.0f;
			env->menu_item[i][j].anim_step = 0.0f;
			env->menu_item[i][j].anim_dir = 1;
			env->menu_item[i][j].type = MENU_ITEM_DEFAULT;
			env->menu_item[i][j].value = 0;
		}
	}

	/* Menu d'accueil */
	env->menu_item[STATE_MENU_HOME][0].texture = util_texture_load ("images/menu/jouer.png");
	env->menu_item[STATE_MENU_HOME][1].texture = util_texture_load ("images/menu/config.png");
	env->menu_item[STATE_MENU_HOME][2].texture = util_texture_load ("images/menu/quitter.png");

	/* Menu suite au jeu (avec bouton reprendre) */
	env->menu_item[STATE_MENU_CONTINUE][0].texture = util_texture_load ("images/menu/reprendre.png");
	env->menu_item[STATE_MENU_CONTINUE][1].texture = env->menu_item[STATE_MENU_HOME][0].texture;
	env->menu_item[STATE_MENU_CONTINUE][2].texture = env->menu_item[STATE_MENU_HOME][1].texture;
	env->menu_item[STATE_MENU_CONTINUE][3].texture = env->menu_item[STATE_MENU_HOME][2].texture;

	/* Menu de choix de niveau */
	env->menu_item[STATE_MENU_PLAY][0].texture = util_texture_load ("images/menu/facile.png");
	env->menu_item[STATE_MENU_PLAY][1].texture = util_texture_load ("images/menu/moyen.png");
	env->menu_item[STATE_MENU_PLAY][2].texture = util_texture_load ("images/menu/difficile.png");
	env->menu_item[STATE_MENU_PLAY][3].texture = util_texture_load ("images/menu/retour.png");

	/* Menu de config */
	env->menu_item[STATE_MENU_CONFIG][0].type = MENU_ITEM_SLIDER;
	env->menu_item[STATE_MENU_CONFIG][0].texture = util_texture_load ("images/menu/retour.png");
	env->menu_item[STATE_MENU_CONFIG][1].type = MENU_ITEM_CHECKBOX;
	env->menu_item[STATE_MENU_CONFIG][1].texture = util_texture_load ("images/menu/retour.png");
	env->menu_item[STATE_MENU_CONFIG][2].type = MENU_ITEM_CHECKBOX;
	env->menu_item[STATE_MENU_CONFIG][2].texture = util_texture_load ("images/menu/retour.png");
	env->menu_item[STATE_MENU_CONFIG][3].texture = util_texture_load ("images/menu/retour.png");
	env->menu_item[STATE_MENU_CONFIG][4].texture = util_texture_load ("images/menu/retour.png");

	/* Valeur des configs */
	for(i = 0; i < CONFIG_NB; i++){
		env->menu_item[STATE_MENU_CONFIG][i].value = env->config[i];
	}
	
	env->selected_item = -1;
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
	util_texture_display(env->mouse_texture, env->mouse.x, env->mouse.y-32.0f, 32.0f, 32.0f);

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

    state_menu_cursor_handler(env);

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
	if(env->selected_item != -1)
	switch(env->selected_page){
		case STATE_MENU_HOME:
			switch(env->selected_item){
				case 0:
					env->selected_item = -1;
					env->selected_page = STATE_MENU_PLAY;
					break;
				case 1:
					env->selected_item = -1;
					env->selected_page = STATE_MENU_CONFIG;
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
					env->selected_item = -1;
					env->selected_page = STATE_MENU_PLAY;
					break;
				case 2:
					env->selected_item = -1;
					env->selected_page = STATE_MENU_CONFIG;
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
					state_game_set_level(1);
					state_game_set_pause(0);
					state_set_current(state_game_get());
					break;
				case 1:
					state_game_set_level(2);
					state_game_set_pause(0);
					state_set_current(state_game_get());
					break;
				case 2:
					state_game_set_pause(0);
					state_game_set_level(3);
					state_set_current(state_game_get());
					break;
				case 3:
					env->selected_item = -1;
					if(state_game_get_pause() != 0)
						env->selected_page = STATE_MENU_CONTINUE;
					else
						env->selected_page = STATE_MENU_HOME;
					break;
				default:
					break;
			}
			break;
		case STATE_MENU_CONFIG:
			if(env->selected_item == 4){
				env->selected_item = -1;
				if(state_game_get_pause() != 0) {
					env->selected_page = STATE_MENU_CONTINUE;
				} else {
					env->selected_page = STATE_MENU_HOME;
				}
			}
			else if(env->selected_item == 3){
				state_menu_save_config_items(env);
				env->selected_item = -1;
				if(state_game_get_pause() != 0) {
					env->selected_page = STATE_MENU_CONTINUE;
				} else {
					env->selected_page = STATE_MENU_HOME;
				}
			}
			else {
				state_menu_select_config_item(env);
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
 * pour changer la position de la souris
 */
int state_menu_cursor_handler(State_Menu_Env* env){

	int rel_x, rel_y, i;

    /* Recuperation de la position relative de la souris */
	SDL_GetRelativeMouseState(&rel_x, &rel_y);
	env->mouse_motion.y = -(GLfloat)rel_y;
	env->mouse_motion.x = (GLfloat)rel_x;
	state_menu_move_cursor(env);
	env->selected_item = -1;
	for(i = 0; i < env->itemsnb[env->selected_page]; i++){
        if( menu_item_mouse_over(&(env->menu_item[env->selected_page][i]), &env->mouse) ){
            env->selected_item = i;
        }
    }
	return 0;
}


void state_menu_select_config_item(State_Menu_Env* env){
	Menu_Item* item = &(env->menu_item[env->selected_page][env->selected_item]);
	
	if(item->type == MENU_ITEM_CHECKBOX){
		if(item->value > 0){
			item->value = 0;
		}
		else {
			item->value = 1;
		}		
	}
	else if(item->type == MENU_ITEM_SLIDER){
		GLfloat y_min, y_max;
		y_min = item->position.y + 40.0f;
		y_max = item->position.y + 128.0f - 8.0f;
		if(env->mouse.y > y_min && env->mouse.y < y_max){
			item->value = (int)(env->mouse.y - y_min);
		}
		else if(env->mouse.y < y_min){
			item->value = 0;
		}
		else{
			item->value = 80;
		}
	}
}

void state_menu_save_config_items(State_Menu_Env* env){
	
	/* On repasse à l'envirronement les valeurs des items de config */
	env->config[CONFIG_MOUSE_SENSIBILITY] = env->menu_item[STATE_MENU_CONFIG][CONFIG_MOUSE_SENSIBILITY].value;
	env->config[CONFIG_REFLECTION] = env->menu_item[STATE_MENU_CONFIG][CONFIG_REFLECTION].value;
	env->config[CONFIG_PARTICLES] = env->menu_item[STATE_MENU_CONFIG][CONFIG_PARTICLES].value;
	
	/* On lance la sauvegarde dans le fichier de config */
	config_save_state_menu(env->config);
	
}