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
#include "includes/State_Menu.h"
#include "includes/Collisions.h"
#include "includes/Util.h"
#include "includes/Animation.h"
#include "includes/AI.h"
#include "includes/State_Game_OpenGL.h"
#include "includes/State_Game_Util.h"

State* state_game(int action) {
    static State* state_game = (State*)0;

    if ( action == STATE_CREATE && !state_game ) {

        state_game = ( State* ) malloc( sizeof(State) );
        state_game->env = ( State_Game_Env* ) malloc( sizeof(State_Game_Env) );
        state_game->init_handler = &state_game_init;
        state_game->main_handler = &state_game_main;
        state_game->events_handler = &state_game_events;

        SDL_Rect **modes = SDL_ListModes(NULL, SDL_FULLSCREEN|SDL_OPENGL);
        (( State_Game_Env* )state_game->env)->w_height = modes[0]->h;
        (( State_Game_Env* )state_game->env)->w_width = modes[0]->w;

	}
    else if ( action == STATE_DESTROY && state_game ) {

        free(state_game->env);
        free(state_game);
        state_game = (State*)0;
    }
    return state_game;
}


void state_game_create() {
    State* state = state_game( STATE_CREATE );
}

State* state_game_get() {
    return state_game( STATE_GET );
}

void state_game_destroy() {
    state_game( STATE_DESTROY );
}


void state_game_init(State_Game_Env* env) {

    int i, j, nbcols;

    /* Initialisation du gen. de nbrs aleatoires, positions et vitesses des balles */
    srand(time(NULL));

	config_load_state_game(env);
	
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

        /* ... Raquette du bas ... */
        env->racket[RACKET_BOTTOM] = env->racket[RACKET_TOP];
        env->racket[RACKET_BOTTOM].position.y = -18.0f;

        /* ... Donnees de l'env ... */
		
		/* Nombre de balles suivant le niveau */
		if(sgu_get_level() == 1){
			env->balls_nb = 1;
			env->AI_handler = *AI_easy;
		} 
		else if(sgu_get_level() == 2){
			env->balls_nb = 5;
			env->AI_handler = *AI_easy;
		}
		else if(sgu_get_level() == 3){
			env->balls_nb = 10;
			env->AI_handler = *AI_easy;
		}
        
		env->mouse_motion_x = 0;
        env->mouse_motion_y = 0;

        /*   Mise en place des balles    */
        nbcols = (int) sqrt(env->balls_nb);
        for (i = 0; i < env->balls_nb; i++) {
            env->ball[i].radius = 0.5f;
            env->ball[i].position.x = (i%nbcols - nbcols/2)*(env->ball[i].radius * 2.5f);
            env->ball[i].position.y = (i/nbcols - nbcols/2)*(env->ball[i].radius * 2.5f);
            env->ball[i].position.z = 0.5f;
            env->ball[i].speed.x = (float) (rand()%50 + 50) / 1000.0f;
			if(rand()%2){
				env->ball[i].speed.x *= -1;
			}
            env->ball[i].speed.y = (float) (rand()%50 + 50) / 1000.0f;
            if(rand()%2){
				env->ball[i].speed.y *= -1;
			}
			particles_init( &env->ball[i].particles, &env->ball[i].position);
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
        for (i = 0 ; i< env->balls_nb ; i++) {
            if (env->config[CONFIG_PARTICLES])
                util_reflection_particles( &(env->ball[i].particles), &(env->ground) );

            util_reflection_ball( &(env->ball[i]), &(env->ground) );
        }
    }

    /* Dessin du reflet de la raquette sur le plateau */
    if (env->config[CONFIG_REFLECTION]) {
        util_reflection_racket( &(env->racket[RACKET_TOP]), &(env->ground) );
    }

    /* Dessin du reflet la raquette sur le plateau */
    if (env->config[CONFIG_REFLECTION]) {
        util_reflection_racket( &(env->racket[RACKET_BOTTOM]), &(env->ground) );
    }

    /* Dessin du terrain */
    ground_draw( &(env->ground) );

    /* Dessin de la balle et de ses particules */
    for (i = 0 ; i< env->balls_nb ; i++) {
        if (env->config[CONFIG_PARTICLES])
            particles_draw( &(env->ball[i].particles) );
        ball_draw( &(env->ball[i]) );
    }

    /* Dessin des deux raquettes */
    racket_draw( &(env->racket[RACKET_TOP]) );
    racket_draw( &(env->racket[RACKET_BOTTOM]) );

}

int state_game_events(State_Game_Env* env) {

    /* Variable de gestion des evenements */
    SDL_Event event;

    env->mouse_motion_x = env->mouse_motion_y = 0;

    while ( SDL_PollEvent(&event) ) {
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
    env->keystates = SDL_GetKeyState( NULL );

    if ( env->keystates[ SDLK_ESCAPE ] ) {
        state_set_current(state_get_menu());
    }

    return 1;

}


void state_game_main(State_Game_Env* env, Uint32 e_time) {

    int i;
    env->ellapsed_time = e_time;

	env->AI_handler(env, RACKET_TOP);
	
	if (sgu_get_pause() != 1){   
		racket_mouse_move(env, RACKET_BOTTOM);
		for(i=0; i<2; i++){
			racket_move(&env->racket[i]);
		}
		collision_state_game(env);
        for (i = 0 ; i< env->balls_nb ; i++) {
            if (env->config[CONFIG_PARTICLES])
                particles_add_position(&env->ball[i].particles, &env->ball[i].position);
            ball_move(&env->ball[i], e_time );
        }
	}
	
    state_game_draw(env);
}
