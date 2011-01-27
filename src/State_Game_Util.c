#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <time.h>
#include "includes/State_Game_Util.h"
#include "includes/Coords.h"
#include "includes/Particles.h"
#include "includes/State.h"
#include "includes/Racket.h"
#include "includes/Ball.h"
#include "includes/Ground.h"
#include "includes/Menu_Item.h"
#include "includes/Config.h"
#include "includes/State_Game.h"


int sgu_pause(int pause) {
    static int p = 0;
    if (pause != -1) {
        p = pause;
    }
    return p;
}

int sgu_get_pause() {
    return sgu_pause(-1);
}

void sgu_set_pause(int pause) {
    sgu_pause(pause);
}

int sgu_level(int level) {
    static int l = 1;
    if (level != -1) {
        l = level;
    }
    return l;
}

int sgu_get_level() {
    return sgu_level(-1);
}

void sgu_set_level(int level) {
    sgu_level(level);
}

void sgu_handle_balls_out(void* environment) {

	State_Game_Env* env;
	env = (State_Game_Env*) environment;
	
    int i;
    for (i = 0; i < env->balls_nb; i++) {
        if (env->ball[i].position.y > env->ground.length / 2) {

			env->racket[RACKET_TOP].lifes--;

			/* La belle en cours d'etude est en dehors du terrain */
			if( env->racket[RACKET_TOP].lifes > 0 ){
				env->ball[i].position.x = 0;
				env->ball[i].position.y = 0;
			}
        }
        else if (env->ball[i].position.y < -env->ground.length / 2) {

			env->racket[RACKET_BOTTOM].lifes--;

			/* La belle en cours d'etude est en dehors du terrain */
			if( env->racket[RACKET_BOTTOM].lifes > 0 ){
				env->ball[i].position.x = 0;
				env->ball[i].position.y = 0;
			}
		}
    }

}
