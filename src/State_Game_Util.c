#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <time.h>
#include "includes/Coords.h"
#include "includes/Particles.h"
#include "includes/State.h"
#include "includes/Racket.h"
#include "includes/Ball.h"
#include "includes/Ground.h"
#include "includes/Menu_Item.h"
#include "includes/Config.h"
#include "includes/State_Game.h"
#include "includes/State_Game_Util.h"

/**
 * Gestion de la pause
 * @param	pause	Pour definir l'etat (-1: Renvoi de l'etat en cours)
 * @return 	0 : Jeu pas encore lance - 1 : Attente de clic pour demarrer - 2 : Pas en pause
 */
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

/**
 * Gestion des niveaux
 */
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

void sgu_destroy_balls_out(State_Game_Env* env) {

    int i;
    for (i = 0; i < env->balls_nb; i++) {
        if (fabs(env->ball[i].position.y) > env->ground.length / 2) {

            /* La belle en cours d'etude est en dehors du terrain */
            env->ball[i] = env->ball[env->balls_nb - 1];
            env->balls_nb--;
        }
    }

}
