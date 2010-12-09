#include <SDL/SDL.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <stdlib.h>
#include <time.h>
#include "includes/Util.h"
#include "includes/Racket.h"
#include "includes/Ball.h"
#include "includes/Ground.h"
#include "includes/Menu_Item.h"
#include "includes/State_Game.h"
#include "includes/State_Menu.h"
#include "includes/Collisions.h"

State* state_game(int action){
	static State* state_game = (State*)0;
	
	if( action == STATE_CREATE && !state_game ){
	
		state_game = ( State* ) malloc( sizeof(State) );
		state_game->env = ( State_Game_Env* ) malloc( sizeof(State_Game_Env) );
		state_game->init_handler = &state_game_init;
		state_game->main_handler = &state_game_main;
		state_game->events_handler = &state_game_events;
		
		SDL_Rect **modes = SDL_ListModes(NULL, SDL_FULLSCREEN|SDL_OPENGL);
		(( State_Game_Env* )state_game->env)->w_height = modes[0]->h;
		(( State_Game_Env* )state_game->env)->w_width = modes[0]->w;
		
		load_configuration(( State_Game_Env* ) state_game->env);
	}
	else if( action == STATE_DESTROY && state_game ){
	
		free(state_game->env);
		free(state_game);
		
		state_game = (State*)0;
	}
	return state_game;
}


void state_game_create(){
	State* state = state_game( STATE_CREATE );
}

State* state_game_get(){
	return state_game( STATE_GET );
}

void state_game_destroy(){
	state_game( STATE_DESTROY );
}


void state_game_init(State_Game_Env* env){

	int i;
	
	/* Initialisation des objets de la scene */
	Ground g = { 2.0f , 40.0f , 30.0f , 0 };
	g.texture = 0;
	
	Racket r = { 0.0f , 18.0f , 1.0f , 5.0f , 1.0f , 0.01f , 0 };
	r.texture = 0;
	
	/* Proprietes du spot d'eclairage */
	GLfloat spotDif[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat spotSpec[] = {0.2f, 0.2f, 0.2f, 1.0f};
	GLfloat spotAmb[] = {0.2f, 0.2f, 0.2f, 1.0f}; 
	
	/* Mise en place des eleme,ts dans la scene */
	env->ground = g;
	env->racket_top = r;
	r.y = -18.0f;
	env->racket_bottom = r;
	env->balls_nb = 10;
	env->mouse_motion_x = 0;
	env->mouse_motion_y = 0;

	/* initialisation de balles */
	srand(time(NULL));
	Ball b = { 0.0f , 0.0f , 0.25f , 0.0f, 0.0f , 0.5f };
	int nbcol = (int) sqrt(env->balls_nb); 
	for (i = 0; i < env->balls_nb; i++){
		b.x = (i%nbcol - nbcol/2)*(b.radius * 2.5f);
		b.y = (i/nbcol - nbcol/2)*(b.radius * 2.5f);
		b.speed.x = (float) (rand()%200 - 100) / 1000.0f;
		b.speed.y = (float) (rand()%200 - 100) / 1000.0f;
		env->ball[i] = b;
	}
	
	/* Activation de la lumiere */
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, spotDif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, spotSpec);
	glLightfv(GL_LIGHT0, GL_AMBIENT, spotAmb);
}

void state_game_draw(State_Game_Env* env){
	
	int i;
	
	/* Position du spot d'eclairage */
	GLfloat spotPosition[] = {0.0 , -30.0 , 40.0 , 1.0};
	
	/* Direction du spot d'eclairage */
	GLfloat spotDirection[]={0.0 , 1.0 , -1.0};
	
	/* On vide le buffer d'affichage */
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );
	
	/* Matrice de manipulation des objets */
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	
	/* Changement de position de la camera */
	gluLookAt(0,-40.0,30,0,-5,0,0,0,1);
	
	/* On place la lumiere dans la scene */
	glLightfv(GL_LIGHT0,GL_POSITION,spotPosition);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 45.0);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDirection);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 5);
	
	/* Dessin des elements de la scene */
	
	for(i = 0 ; i< env->balls_nb ; i++){
		util_reflection_ball( &(env->ball[i]), &(env->ground) );
		ball_draw( &(env->ball[i]) );
	}
	
	util_reflection_racket( &(env->racket_top), &(env->ground) );
	racket_draw( &(env->racket_top) );
	
	util_reflection_racket( &(env->racket_bottom), &(env->ground) );
	racket_draw( &(env->racket_bottom) );
	
	ground_draw( &(env->ground) );
	
	/* On s'assure que le dessin est termine */
	glFlush();
	
	/* On affiche */
	SDL_GL_SwapBuffers();
}

int state_game_events(State_Game_Env* env){
	
	/* Variable de gestion des evenements */
	SDL_Event event;
	
	env->mouse_motion_x = env->mouse_motion_y = 0;

	while( SDL_PollEvent(&event) ){ 	
		if( event.type == SDL_QUIT ){ 
			state_set_current(state_get_menu());
		}
		else if (event.type == SDL_MOUSEMOTION)
		{
			env->mouse_motion_x += event.motion.xrel;
			env->mouse_motion_y += event.motion.yrel;
		}
	}

	/* on replace la souris au centre et on enleve l'evenement ainsi genere */
	SDL_WarpMouse(env->w_width/2, env->w_height/2);
	while( SDL_PollEvent(&event) );

	env->keystates = SDL_GetKeyState( NULL );
	
	if( env->keystates[ SDLK_ESCAPE ] ) {
		state_set_current(state_get_menu());
	}
	
	racket_move(env, RACKET_BOTTOM);
	
	return 1;

}


void state_game_main(State_Game_Env* env, Uint32 e_time){
	
	int i;
	env->ellapsed_time = e_time;
	
	collision_state_game(env);
	
	for(i = 0 ; i< env->balls_nb ; i++)
		ball_move(&env->ball[i], e_time );
	
	state_game_draw(env);
}

