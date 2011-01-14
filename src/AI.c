#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <float.h>
#include "includes/Coords.h"
#include "includes/Particles.h"
#include "includes/State.h"
#include "includes/Racket.h"
#include "includes/Ball.h"
#include "includes/Ground.h"
#include "includes/Config.h"
#include "includes/State_Game.h"
#include "includes/Collisions.h"
#include "includes/AI.h"

#define AI_EASY_SPEED       RACKET_SPEED_MAX/5.0f
#define AI_MEDIUM_SPEED     RACKET_SPEED_MAX/3.0f
#define AI_HARD_SPEED       RACKET_SPEED_MAX
#define AI_EASY_SIGHT       env->ground.length / 4.0f
#define AI_MEDIUM_SIGHT     env->ground.length / 2.0f

void AI_easy(State_Game_Env* env, int racket_id) {

    int i;
    Ball* ball = NULL;
    Racket* racket = &env->racket[racket_id];
    float dist_temp, dist = 1000.0f;

    /* Choix de la balle a intercepter */
    for (i = 0; i < env->balls_nb; i++) {

        /* Si la balle va dans le bon sens */
        if ((env->ball[i].speed.y > 0.0f && racket->position.y > env->ball[i].position.y) || (env->ball[i].speed.y < 0.0f && racket->position.y < env->ball[i].position.y)) {

            /* On va betement suivre la plus proche */
			dist_temp = fabs(env->ball[i].position.y - racket->position.y);
            if ( dist_temp < dist && dist > AI_EASY_SIGHT) {
                dist = dist_temp;
                ball = &env->ball[i];
            }
        }
    }

    /* Poursuite de la balle */
    if (ball != NULL) {

		fabs(ball->position.x - racket->position.x);
        float dir = (ball->position.x > racket->position.x) ? 1.0 : -1.0;

        if (dist > racket->width / 4.0) {
            if (dist > AI_EASY_SPEED)
                racket->speed = dir * AI_EASY_SPEED;
            else
                racket->speed = dir * dist;
        } else
            racket->speed = 0.0f;
    } else
        racket->speed = 0.0f;
}

void AI_medium(State_Game_Env* env, int racket_id) {

    int i;
    Ball* ball = NULL;
    Racket* racket = &env->racket[racket_id];
    GLfloat b_s = 1000000.0f, b_s_temp;

    /* Choix de la balle a intercepter */
    for (i = 0; i < env->balls_nb; i++) {

        /* Si la balle va dans le bon sens */
        if ((env->ball[i].speed.y > 0 && racket->position.y > env->ball[i].position.y) || (env->ball[i].speed.y < 0 && racket->position.y < env->ball[i].position.y)) {

            /* On va suivre celle qui arrivera en premier */
            b_s_temp = (racket->position.y - env->ball[i].position.y) / env->ball[i].speed.y;
            if (b_s_temp < b_s) {
                b_s = b_s_temp;
                ball = &env->ball[i];
            }
        }
    }

    /* Poursuite de la balle */
    if (ball != NULL) {
        float dist = fabs(ball->position.x - racket->position.x);

        if (fabs(ball->position.y - racket->position.y) < AI_MEDIUM_SIGHT) {
            float dir = (ball->position.x > racket->position.x) ? 1.0 : -1.0;

            if (dist > racket->width / 4.0) {
                if (dist > AI_MEDIUM_SPEED)
                    racket->speed = dir * AI_MEDIUM_SPEED;
                else
                    racket->speed = dir * dist;
            } else
                racket->speed = 0.0f;
        }
    } else if (racket->position.x > 0.5f) {
        racket->speed = -AI_MEDIUM_SPEED;
    } else if (racket->position.x < -0.5f) {
        racket->speed = AI_MEDIUM_SPEED;
    } else
        racket->speed = 0.0f;
}

void AI_hard(State_Game_Env* env, int racket_id) {

    int i;
    Ball* ball = NULL;
    Racket* racket = &env->racket[racket_id];
    GLfloat b_s = 1000000.0f, b_s_temp;

    /* Choix de la balle a intercepter */
    for (i = 0; i < env->balls_nb; i++) {

        /* Si la balle va dans le bon sens */
        if ((env->ball[i].speed.y > 0 && racket->position.y > env->ball[i].position.y) || (env->ball[i].speed.y < 0 && racket->position.y < env->ball[i].position.y)) {

            /* On va suivre celle qui arrivera en premier */
            b_s_temp = (env->ball[i].position.y - racket->position.y) / env->ball[i].speed.y;
            if (b_s_temp < b_s) {
                b_s = b_s_temp;
                ball = &env->ball[i];
            }
        }
    }

    /* Poursuite de la balle */
    if (ball != NULL) {
        float dist = fabs(ball->position.x - racket->position.x);
        float dir = (ball->position.x > racket->position.x) ? 1.0 : -1.0;

        if (dist > racket->width / 4.0) {
            if (dist > AI_HARD_SPEED)
                racket->speed = dir * AI_HARD_SPEED;
            else
                racket->speed = dir * dist;
        } else
            racket->speed = 0.0f;
    } else if (racket->position.x > 0.5f) {
        racket->speed = -AI_HARD_SPEED;
    } else if (racket->position.x < -0.5f) {
        racket->speed = AI_HARD_SPEED;
    } else
        racket->speed = 0.0f;
    ;
}
