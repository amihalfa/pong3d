#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
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
#include "includes/State_Menu.h"
#include "includes/Collisions.h"
#include "includes/Util.h"
#include "includes/Animation.h"
#include "includes/AI.h"
#include "includes/State_Game_OpenGL.h"
#include "includes/State_Game_Util.h"

State* state_game(int action) {
    static State* state_game = (State*) 0;

    if (action == STATE_CREATE && !state_game) {

        state_game = (State*) malloc(sizeof (State));
        state_game->env = (State_Game_Env*) malloc(sizeof (State_Game_Env));
        state_game->init_handler = &state_game_init;
        state_game->main_handler = &state_game_main;
        state_game->events_handler = &state_game_events;

        SDL_Rect **modes = SDL_ListModes(NULL, SDL_FULLSCREEN | SDL_OPENGL);
        ((State_Game_Env*) state_game->env)->w_height = modes[0]->h;
        ((State_Game_Env*) state_game->env)->w_width = modes[0]->w;
        ((State_Game_Env*) state_game->env)->sound = Mix_LoadWAV("son/collision.wav");

    } else if (action == STATE_DESTROY && state_game) {

        Mix_FreeChunk(((State_Game_Env*) state_game->env)->sound);
        free(state_game->env);
        free(state_game);
        state_game = (State*) 0;
    }
    return state_game;
}

void state_game_create() {
    State* state = state_game(STATE_CREATE);
}

State* state_game_get() {
    return state_game(STATE_GET);
}

void state_game_destroy() {
    state_game(STATE_DESTROY);
}

void state_game_init(State_Game_Env* env) {

    int i, j, nbcols;

    /* Initialisation du gen. de nbrs aleatoires, positions et vitesses des balles */
    srand(time(NULL));

    config_load_state_game(env);

    env->heart_texture = util_texture_load("images/game/jaime.png");

    if (sgu_get_pause() == 0) {

        /* Mise en place du terrain dans la scene */
        env->ground.height = 2.0f;
        env->ground.length = 40.0f;
        env->ground.width = 30.0f;

        /* ... Raquette du haut... */
        env->racket[RACKET_TOP].position.x = 0.0f;
        env->racket[RACKET_TOP].position.y = 18.0f;
        env->racket[RACKET_TOP].position.z = 0.8f;
        env->racket[RACKET_TOP].width = 5.0f;
        env->racket[RACKET_TOP].radius = 0.8f;
        env->racket[RACKET_TOP].speed = 0.0f;
        env->racket[RACKET_TOP].lifes = 3;

        /* ... Raquette du bas ... */
        env->racket[RACKET_BOTTOM] = env->racket[RACKET_TOP];
        env->racket[RACKET_BOTTOM].position.y = -18.0f;

        /* ... Donnees de l'env ... */

        /* Nombre de balles suivant le niveau */
        if (sgu_get_level() == 1) {
            env->balls_nb = 2;
            env->AI_handler = *AI_easy;
        } else if (sgu_get_level() == 2) {
            env->balls_nb = 3;
            env->AI_handler = *AI_medium;
        } else if (sgu_get_level() == 3) {
            env->balls_nb = 4;
            env->AI_handler = *AI_hard;
        } else if (sgu_get_level() == 4) {
            /* Mode 2 joueurs pas d'IA */
            env->balls_nb = 1;
            env->AI_handler = (void*) 0;
        }

        env->mouse_motion_x = 0;
        env->mouse_motion_y = 0;

        /*   Mise en place des balles    */
        nbcols = (int) sqrt(env->balls_nb);
        for (i = 0; i < env->balls_nb; i++) {
            env->ball[i].radius = 0.5f;
            env->ball[i].position.x = (i % nbcols - nbcols / 2)*(env->ball[i].radius * 2.5f);
            env->ball[i].position.y = (i / nbcols - nbcols / 2)*(env->ball[i].radius * 2.5f);
            env->ball[i].position.z = 0.5f;
            env->ball[i].speed.x = (float) (rand() % 50 + 50) / 1000.0f;
            if (rand() % 2) {
                env->ball[i].speed.x *= -1;
            }
            env->ball[i].speed.y = (float) (rand() % 50 + 50) / 1000.0f;
            if (env->ball[i].speed.y < BALL_MIN_SPEED) {
                env->ball[i].speed.y = BALL_MIN_SPEED;
            }
            if (rand() % 2) {
                env->ball[i].speed.y *= -1;
            }
            particles_init(&env->ball[i].particles, &env->ball[i].position);
        }
    }
    sgu_set_pause(1);

    sgo_init();

}

void state_game_draw(State_Game_Env* env) {

    int i;

    sgo_draw();

    /* Dessin des reflets des balles et des particules */
    if (env->config[CONFIG_REFLECTION]) {
        for (i = 0; i < env->balls_nb; i++) {
            if (env->config[CONFIG_PARTICLES])
                util_reflection_particles(&(env->ball[i].particles), &(env->ground));

            util_reflection_ball(&(env->ball[i]), &(env->ground));
        }
    }

    /* Dessin du reflet de la raquette sur le plateau */
    if (env->config[CONFIG_REFLECTION]) {
        util_reflection_racket(&(env->racket[RACKET_TOP]), &(env->ground));
    }

    /* Dessin du reflet la raquette sur le plateau */
    if (env->config[CONFIG_REFLECTION]) {
        util_reflection_racket(&(env->racket[RACKET_BOTTOM]), &(env->ground));
    }

    /* Dessin du terrain */
    ground_draw(&(env->ground));

    /* Dessin de la balle et de ses particules */
    for (i = 0; i < env->balls_nb; i++) {
        if (env->config[CONFIG_PARTICLES])
            particles_draw(&(env->ball[i].particles));
        ball_draw(&(env->ball[i]));
    }

    util_score_display(env->heart_texture, env->racket[RACKET_TOP].lifes, -env->ground.width / 2 + 1.0f, env->ground.length / 2 - 2.0f);
    util_score_display(env->heart_texture, env->racket[RACKET_BOTTOM].lifes, -env->ground.width / 2 + 1.0f, -env->ground.length / 2 + 1.0f);

    /* Dessin des deux raquettes */
    racket_draw(&(env->racket[RACKET_TOP]));
    racket_draw(&(env->racket[RACKET_BOTTOM]));

}

int state_game_events(State_Game_Env* env) {

    /* Variable de gestion des evenements */
    SDL_Event event;

    env->mouse_motion_x = env->mouse_motion_y = 0;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                return 0;
                break;

            case SDL_MOUSEMOTION:
                if (sgu_get_pause() == 2) {
                    env->mouse_motion_x += event.motion.xrel;
                    env->mouse_motion_y += event.motion.yrel;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                sgu_set_pause(2);
                break;
        }
    }

    env->keystates = SDL_GetKeyState(NULL);

    if (env->keystates[ SDLK_ESCAPE ]) {
        state_set_current(state_get_menu());
    }
    if (env->keystates[ SDLK_SPACE ]) {
        sgu_set_pause(2);
    }

    return 1;

}

void state_game_main(State_Game_Env* env, Uint32 e_time) {

    int i;

    env->ellapsed_time = e_time;

    sgu_destroy_balls_out(env);

    /* On n'utilise pas l'IA dans le mode 2 joueurs */
    if (sgu_get_level() != 4) {
        env->AI_handler(env, RACKET_TOP);
    }

    if (sgu_get_pause() != 1) {

        /* Gestion de la raquette du haut avec le clavier dans le cas ou pas d'IA */
        if (sgu_get_level() == 4) {
            racket_keyboard_move(env, RACKET_TOP);
            racket_keyboard_move(env, RACKET_BOTTOM);
        } else {
            /* Gestion de la raquette du bas avec la souris */
            racket_mouse_move(env, RACKET_BOTTOM);
        }

        /* On bouge les raquettes */
        for (i = 0; i < 2; i++) {
            racket_move(&env->racket[i]);
        }

        /* Gestion des collisions */
        collision_state_game(env);

        /* Mouvement des balles et de leurs particules */
        for (i = 0; i < env->balls_nb; i++) {
            if (env->config[CONFIG_PARTICLES])
                particles_add_position(&env->ball[i].particles, &env->ball[i].position);
            ball_move(&env->ball[i], e_time);
        }
    }

    /* Cas ou il n'y a pas de vie d'un cote ou de l'autre */
    if (env->racket[RACKET_TOP].lifes <= 0 || env->racket[RACKET_BOTTOM].lifes <= 0) {
        sgu_set_pause(1);
    } else {
        /* Aucune balle sur le terrain
         * Le Niveau 1 est actif ou bien le mode 2 joueurs
         * Il y a des vies des 2 cotes
         */
        if (env->balls_nb == 0 && (sgu_get_level() == 1 || sgu_get_level() == 4)) {
            sgu_set_pause(1);

            /* On repositionne la balle au centre */
            env->balls_nb = 1;
            env->ball[0].position.x = 0;
            env->ball[0].position.y = 0;

            /* On repositionne les raquettes au centre */
            env->racket[RACKET_TOP].position.x = 0;
            env->racket[RACKET_BOTTOM].position.x = 0;

            /* On reinitialise les particules derriere la balle */
            particles_init(&env->ball[i].particles, &env->ball[i].position);
        }
    }

    state_game_draw(env);
}
