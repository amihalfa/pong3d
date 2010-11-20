#include <SDL/SDL.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include "includes/Racket.h"
#include "includes/Ball.h"
#include "includes/Ground.h"
#include "includes/Menu_Item.h"
#include "includes/State_Game.h"
#include "includes/State_Menu.h"
#include "includes/Collisions.h"
#include <stdio.h>

State* state_game(int action){
	static State* state_game = (State*)0;
	
	if( action == STATE_CREATE && !state_game ){
	
		state_game = ( State* ) malloc( sizeof(State) );
		state_game->env = ( State_Game_Env* ) malloc( sizeof(State_Game_Env) );
		state_game->init_handler = &state_game_init;
		state_game->main_handler = &state_game_main;
		state_game->events_handler = &state_game_events;
	
	}
	else if( action == STATE_DESTROY && state_game ){
	
		free(state_game->env);
		free(state_game);
		
		state_game = (State*)0;
	}
	return state_game;
}


void state_game_create(){
	state_game( STATE_CREATE );
}

State* state_game_get(){
	return state_game( STATE_GET );
}

void state_game_destroy(){
	state_game( STATE_DESTROY );
}



void state_game_init(State_Game_Env* env){

	
	/* Initialisation des objets de la scene */
	Ground g = { 2.0f , 40.0f , 30.0f , 0 };
	g.texture = util_texture_load ("images/game/wood.jpg");
	
	Racket r = { 0.0f , 18.0f , 1.0f , 5.0f , 1.0f , 0.01f , 0 };
	r.texture = util_texture_load ("images/game/steel.jpg");
	
	Ball b = { 0.0f , 0.0f , 0.5f , 0.1f, 0.2f , 0.5f };
	
	/* Proprietes du spot d'eclairage */
	GLfloat spotDif[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat spotSpec[] = {0.2f, 0.2f, 0.2f, 1.0f};
	GLfloat spotAmb[] = {0.2f, 0.2f, 0.2f, 1.0f}; 
	
	/* Mise en place des eleme,ts dans la scene */
	env->ground = g;
	env->racket_top = r;
	r.y = -18.0f;
	env->racket_bottom = r;
	env->ball = b;
	
	/* Activation de la lumiere */
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, spotDif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, spotSpec);
	glLightfv(GL_LIGHT0, GL_AMBIENT, spotAmb);
}

void state_game_draw(State_Game_Env* env){
	
	/* Position du spot d'eclairage */
	GLfloat spotPosition[] = {0.0 , -30.0 , 40.0 , 1.0};
	
	/* Direction du spot d'eclairage */
	GLfloat spotDirection[]={0.0 , 1.0 , -1.0};
	
	/* On vide le buffer d'affichage */
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	/* Matrice de manipulation des objets */
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	
	/* Changement de position de la camera */
	gluLookAt(0,-40.0,40,0,-5,0,0,0,1);
	
	/* On place la lumiere dans la scene */
	glLightfv(GL_LIGHT0,GL_POSITION,spotPosition);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 45.0);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDirection);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 5);
	
	/* Dessin des elements de la scene */
	ball_draw( &(env->ball) );
	ground_draw( &(env->ground) );
	racket_draw( &(env->racket_top) );
	racket_draw( &(env->racket_bottom) );
	
	/* On s'assure que le dessin est terminé */
	glFlush();
	
	/* On affiche */
	SDL_GL_SwapBuffers();
}

int state_game_events(State_Game_Env* env){
	
	/* Variable de gestion des evenements */
	SDL_Event event;
	
	/* Etat des touches */
	Uint8 *keystates;
	
	while( SDL_PollEvent(&event) ){ 	
		if( event.type == SDL_QUIT ){ 
			current_state_set(state_menu_get());
		}
	}

	keystates = SDL_GetKeyState( NULL );
	
	if( keystates[ SDLK_ESCAPE ] ) { 
		current_state_set(state_menu_get());
	}
	
	if( keystates[ SDLK_LEFT ] ) { 
		if( !collision_racket_ground( &(env->racket_bottom) , &(env->ground), COLLISION_LEFT) )
			(env->racket_bottom).x -= 0.25;
	}
	
	if( keystates[ SDLK_RIGHT ] ) { 
		if( !collision_racket_ground( &(env->racket_bottom) , &(env->ground), COLLISION_RIGHT) )
			(env->racket_bottom).x += 0.25;
	}
	
	return 1;

}


void state_game_main(State_Game_Env* env, Uint32 e_time){
	collision_state_game(env, e_time);
	ball_move(&env->ball, e_time);
	state_game_draw(env);
}

