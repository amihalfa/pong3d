#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
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

#define AI_EASY_SPEED       RACKET_SPEED_MAX/6.0f
#define AI_MEDIUM_SPEED     RACKET_SPEED_MAX/3.0f
#define AI_HARD_SPEED       RACKET_SPEED_MAX
#define AI_EASY_GOODNESS    50
#define AI_MEDIUM_GOODNESS  500
#define AI_HARD_GOODNESS    5000

void AI_easy(State_Game_Env* env, int racket_id) {

    static int mistake = 0;
    int i;
    Ball* ball = NULL;
    Racket* racket = &env->racket[racket_id];
    GLfloat b_y = 1000000.0f;

    /* Choix de la balle a intercepter */
    for (i = 0; i < env->balls_nb; i++) {

        /* Si la balle va dans le bon sens */
        if ((env->ball[i].speed.y > 0 && racket->position.y > env->ball[i].position.y) || (env->ball[i].speed.y < 0 && racket->position.y < env->ball[i].position.y)) {

            /* On va betement suivre la plus proche */
            if (env->ball[i].position.y < b_y) {
                b_y = env->ball[i].position.y;
                ball = &env->ball[i];
            }
        }
    }

    /* Poursuite de la balle */
    if (ball != NULL) {
        float dist = fabs(ball->position.x - racket->position.x);
        float dir = (ball->position.x > racket->position.x) ? 1.0 : -1.0;

        if (rand() % AI_EASY_GOODNESS == 0)
            mistake = rand() % AI_EASY_GOODNESS + 1;

        if (mistake > 0) {
            dir = -dir;
            mistake--;
        }

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

    static int mistake = 0;
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

        if (rand() % AI_MEDIUM_GOODNESS == 0)
            mistake = rand() % 10 + 1;

        if (mistake > 0) {
            dir = -dir;
            mistake--;
        }

        if (dist > racket->width / 4.0) {
            if (dist > AI_MEDIUM_SPEED)
                racket->speed = dir * AI_MEDIUM_SPEED;
            else
                racket->speed = dir * dist;
        } else
            racket->speed = 0.0f;
    } else
        racket->speed = 0.0f;
}

void AI_hard(State_Game_Env* env, int racket_id) {

    static int mistake = 0;
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

        if (rand() % AI_HARD_GOODNESS == 0)
            mistake = rand() % 10 + 1;

        if (mistake > 0) {
            dir = -dir;
            mistake--;
        }

        if (dist > racket->width / 4.0) {
            if (dist > AI_MEDIUM_SPEED)
                racket->speed = dir * AI_MEDIUM_SPEED;
            else
                racket->speed = dir * dist;
        } else
            racket->speed = 0.0f;
    } else
        racket->speed = 0.0f;
}