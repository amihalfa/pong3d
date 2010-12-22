#include <SDL/SDL.h>
#include "GL/gl.h"
#include "includes/Coords.h"
#include "includes/Particles.h"
#include "includes/State.h"
#include "includes/Racket.h"
#include "includes/Ball.h"
#include "includes/Ground.h"
#include "includes/Config.h"
#include "includes/State_Game.h"

int config_load(State_Game_Env* env_game){
	char* vars[CONFIG_NB] = {
		"mouse_sensibility=%f\n", 
		"reflection=%f\n",
		"particles=%f\n"
	};
	int i;
	FILE* config = fopen("config/config.cfg", "r+");
	if (!config) {
		return 0;
	}
	for (i = 0; i < CONFIG_NB; i++) {
		fscanf(config, vars[i], &env_game->config[i]);
	}
	return 1;
}