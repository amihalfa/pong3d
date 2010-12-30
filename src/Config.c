#include <SDL/SDL.h>
#include <GL/gl.h>
#include "includes/Coords.h"
#include "includes/Particles.h"
#include "includes/State.h"
#include "includes/Racket.h"
#include "includes/Ball.h"
#include "includes/Ground.h"
#include "includes/State_Game.h"
#include "includes/Menu_Item.h"
#include "includes/State_Menu.h"
#include "includes/Config.h"

int config_load(float* config){
	char* vars[CONFIG_NB] = {
		"mouse_sensibility=%f\n", 
		"reflection=%f\n",
		"particles=%f\n"
	};
	int i;
	FILE* file_config = fopen("config/config.cfg", "r+");
	if (!file_config) {
		return 0;
	}
	for (i = 0; i < CONFIG_NB; i++) {
		fscanf(file_config, vars[i], &config[i]);
	}
	return 1;
}

int config_load_state_game(State_Game_Env* env){
	float config[CONFIG_NB];
	int i;
	if(config_load(config)){
		for (i = 0; i < CONFIG_NB; i++) {
			env->config[i] = config[i];
		}
		return 1;
	}
	return 0;
}

int config_load_state_menu(State_Menu_Env* env){
	
	return 1;
}