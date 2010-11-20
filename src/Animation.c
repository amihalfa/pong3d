#include "includes/Animation.h"
#include "includes/State_Menu.h"

void animation_state_menu(State_Menu_Env* env, Uint32 e_time){

	int i;
	
	/* On remet les elements du menu non selectionnes a 0 */
	for(i = 0; i < STATE_MENU_ITEMSNB; i++){
		if(i != env->selected_item ){
			menu_item_animate_to_0(&env->menu_item[i], e_time);
		}
	}
	
	/* On anime l'element selectionne */
	menu_item_animate(&env->menu_item[env->selected_item], e_time);
	
}
