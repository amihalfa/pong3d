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
#include "includes/State_Menu_Items.h"

void state_menu_items_init_textures(State_Menu_Env* env){
	
	/* Menu d'accueil */
	env->menu_item[STATE_MENU_HOME][0].texture = util_texture_load("images/menu/jouer.png");
	env->menu_item[STATE_MENU_HOME][1].texture = util_texture_load("images/menu/config.png");
	env->menu_item[STATE_MENU_HOME][2].texture = util_texture_load("images/menu/quitter.png");

	/* Menu suite au jeu (avec bouton reprendre) */
	env->menu_item[STATE_MENU_CONTINUE][0].texture = util_texture_load("images/menu/reprendre.png");
	env->menu_item[STATE_MENU_CONTINUE][1].texture = env->menu_item[STATE_MENU_HOME][0].texture;
	env->menu_item[STATE_MENU_CONTINUE][2].texture = env->menu_item[STATE_MENU_HOME][1].texture;
	env->menu_item[STATE_MENU_CONTINUE][3].texture = env->menu_item[STATE_MENU_HOME][2].texture;

	/* Menu de choix de niveau */
	env->menu_item[STATE_MENU_PLAY][0].texture = util_texture_load("images/menu/facile.png");
	env->menu_item[STATE_MENU_PLAY][1].texture = util_texture_load("images/menu/moyen.png");
	env->menu_item[STATE_MENU_PLAY][2].texture = util_texture_load("images/menu/difficile.png");
	env->menu_item[STATE_MENU_PLAY][3].texture = util_texture_load("images/menu/retour.png");

	/* Menu de config */
	env->menu_item[STATE_MENU_CONFIG][0].texture = util_texture_load("images/menu/souris.png");
	env->menu_item[STATE_MENU_CONFIG][1].texture = util_texture_load("images/menu/reflets.png");
	env->menu_item[STATE_MENU_CONFIG][2].texture = util_texture_load("images/menu/particules.png");
	env->menu_item[STATE_MENU_CONFIG][3].texture = util_texture_load("images/menu/valider.png");
	env->menu_item[STATE_MENU_CONFIG][4].texture = env->menu_item[STATE_MENU_PLAY][3].texture;
	
}

int state_menu_items_select(State_Menu_Env* env){
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
				state_menu_items_select_config(env);
			}
			break;
		default:
			break;
	}
	return 1;
}

void state_menu_items_select_config(State_Menu_Env* env){
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