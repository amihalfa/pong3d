#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <time.h>
#include "includes/Coords.h"
#include "includes/Particles.h"
#include "includes/State.h"
#include "includes/Ball.h"
#include "includes/Menu_Item.h"
#include "includes/State_Menu.h"
#include "includes/Animation.h"

void animation_state_menu(State_Menu_Env* env, Uint32 e_time){

	int i;
	
	/* On remet les elements du menu non selectionnes a 0 */
	for(i = 0; i < env->itemsnb[env->selected_page]; i++){
		if(i != env->selected_item ){
			menu_item_animate_to_0(&env->menu_item[env->selected_page][i], e_time);
		}
	}
	
	/* On anime l'element selectionne */
	menu_item_animate(&env->menu_item[env->selected_page][env->selected_item], e_time);
	
}