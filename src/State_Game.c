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
		
		config_load(( State_Game_Env* ) state_game->env);
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

	float ratio;
	int i, j, nbcols;
	
	/* Resolutions possibles sous la config actuelle */
	SDL_Rect **modes;
	
	/* Initialisation du gen. de nbrs aleatoires, positions et vitesses des balles */
	srand(time(NULL));
	
	/* Proprietes du spot d'eclairage */
	GLfloat spotDif[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat spotSpec[] = {0.2f, 0.2f, 0.2f, 1.0f};
	GLfloat spotAmb[] = {0.2f, 0.2f, 0.2f, 1.0f}; 
	
	if(state_game_get_pause() == 0){
		
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
		env->racket[RACKET_TOP].speed = 0.01f;

		/* ... Raquette du bas ... */
		env->racket[RACKET_BOTTOM] = env->racket[RACKET_TOP];
		env->racket[RACKET_BOTTOM].position.y = -18.0f;
		
		/* ... Donnees de l'env ... */
		env->balls_nb = 10;
		env->mouse_motion_x = 0;
		env->mouse_motion_y = 0;
		
		/*   Mise en place des balles    */
		nbcols = (int) sqrt(env->balls_nb); 
		for (i = 0; i < env->balls_nb; i++){	
			env->ball[i].radius = 0.5f;
			env->ball[i].position.x = (i%nbcols - nbcols/2)*(env->ball[i].radius * 2.5f);
			env->ball[i].position.y = (i/nbcols - nbcols/2)*(env->ball[i].radius * 2.5f);
			env->ball[i].position.z = 0.5f;
			env->ball[i].speed.x = (float) (rand()%200 - 100) / 1000.0f;
			env->ball[i].speed.y = (float) (rand()%200 - 100) / 1000.0f;
			particles_init( &env->ball[i].particles, &env->ball[i].position);
		}
	}
	state_game_set_pause(1);
		
	/* Activation de la lumiere */
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, spotDif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, spotSpec);
	glLightfv(GL_LIGHT0, GL_AMBIENT, spotAmb);
	
	/* Pour gerer les zIndex */
	glEnable(GL_DEPTH_TEST);
	
	/* Mise en place des spots d'eclairage */
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	
	/* Recuperation des resolutions possibles */
	modes = SDL_ListModes(NULL, SDL_FULLSCREEN|SDL_OPENGL);

	/* Calcul du ratio de la resolution */
	ratio = (float) modes[0]->w / modes[0]->h;
	
	/* Mise en place de la projection en perspective */
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective( 40 , ratio , 1 , 1000);
	
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
	
	/* Dessin des reflets des balles et des particules */
	if(env->config[CONFIG_REFLECTION]){
		for(i = 0 ; i< env->balls_nb ; i++){
			if(env->config[CONFIG_PARTICLES])
				util_reflection_particles( &(env->ball[i].particles), &(env->ground) );
			
				util_reflection_ball( &(env->ball[i]), &(env->ground) );
		}
	}
	
	/* Dessin du reflet de la raquette sur le plateau */
	if(env->config[CONFIG_REFLECTION]){
		util_reflection_racket( &(env->racket[RACKET_TOP]), &(env->ground) );
	}
	
	/* Dessin du reflet la raquette sur le plateau */
	if(env->config[CONFIG_REFLECTION]){
		util_reflection_racket( &(env->racket[RACKET_BOTTOM]), &(env->ground) );
	}
	
	/* Dessin du terrain */
	ground_draw( &(env->ground) );
	
	/* Dessin de la balle et de ses particules */
	for(i = 0 ; i< env->balls_nb ; i++){
		if(env->config[CONFIG_PARTICLES])
			particles_draw( &(env->ball[i].particles) );
		ball_draw( &(env->ball[i]) );
	}
	
	/* Dessin des deux raquettes */
	racket_draw( &(env->racket[RACKET_TOP]) );
	racket_draw( &(env->racket[RACKET_BOTTOM]) );
	
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
	
	if( env->keystates[ SDLK_SPACE ] ) {
		state_game_set_pause(2);
	}
	
	racket_move(env, RACKET_BOTTOM);
	
	return 1;

}


void state_game_main(State_Game_Env* env, Uint32 e_time){
	
	int i;
	env->ellapsed_time = e_time;
	
	collision_state_game(env);
	
	if(state_game_get_pause() != 1)
		for(i = 0 ; i< env->balls_nb ; i++){
			if(env->config[CONFIG_PARTICLES])
				particles_add_position(&env->ball[i].particles, &env->ball[i].position);
			ball_move(&env->ball[i], e_time );
		}
	
	
	state_game_draw(env);
}


int state_game_pause(int pause){
	static int p = 0;
	if(pause != -1){
		p = pause;
	}
	return p;
}

int state_game_get_pause(){
	return state_game_pause(-1);
}

void state_game_set_pause(int pause){
	state_game_pause(pause);
}
