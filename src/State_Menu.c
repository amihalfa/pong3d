#include <SDL/SDL.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include "includes/Racket.h"
#include "includes/Ball.h"
#include "includes/Ground.h"
#include "includes/State.h"
#include "includes/Menu_Item.h"
#include "includes/State_Menu.h"
#include "includes/State_Game.h"

State* state_menu(int action){
	
	static State* state_menu = (State*)0;
	
	if( action == STATE_CREATE && !state_menu ){
		
		state_menu = ( State* ) malloc( sizeof(State) );
		state_menu->env = ( State_Menu_Env* ) malloc( sizeof(State_Menu_Env) );
		state_menu->init_handler = &state_menu_init;
		state_menu->draw_handler = &state_menu_draw;
		state_menu->events_handler = &state_menu_events;
		
	}
	else if( action == STATE_DESTROY && state_menu ){
			
		free(state_menu->env);
		free(state_menu);
			
		state_menu = (State*)0;
	}
	
	return state_menu;
}


void state_menu_create(){
	state_menu( STATE_CREATE );
}

State* state_menu_get(){
	return state_menu( STATE_GET );
}

void state_menu_destroy(){
	state_menu( STATE_DESTROY );
}

void state_menu_init(State_Menu_Env* env){
		
	/* Proprietes du spot d'eclairage */
	GLfloat spotDif[] = {0.8f, 0.8f, 0.8f, 1.0f};
	GLfloat spotSpec[] = {0.2f, 0.2f, 0.2f, 1.0f};
	GLfloat spotAmb[] = {0.2f, 0.2f, 0.2f, 1.0f}; 
	
	Menu_Item menu_item = { 0.0 , 0.0 , 0.0 , 0.5 , 2.0 , 5.0 };
	
	env->menu_item[0] = menu_item;
	menu_item.y = -2.5;
	env->menu_item[1] = menu_item;
	
	/* Activation de la lumiere */
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, spotDif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, spotSpec);
	glLightfv(GL_LIGHT0, GL_AMBIENT, spotAmb);
	
}

void state_menu_draw(State_Menu_Env* env){
	
	Uint32 start_time, ellapsed_time;
	
	/* Position du spot d'eclairage */
	GLfloat spotPosition[] = {-20.0 , -30.0 , 40.0 , 1.0};
	
	/* Direction du spot d'eclairage */
	GLfloat spotDirection[]={0.8 , 1.2 , -1.0};
	
	/* On vide le buffer d'affichage */
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	/* Matrice de manipulation des objets */
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	
	/* Changement de position de la camera */
	gluLookAt(-5,-40.0,40,0,-5,0,0,0,1);
	
	/* On place la lumiere dans la scene */
	glLightfv(GL_LIGHT0,GL_POSITION,spotPosition);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 45.0);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDirection);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 5);
	
	/* On dessinne les objets de la scene */
	menu_item_draw( &(env->menu_item[0]) );
	menu_item_draw( &(env->menu_item[1]) );
	
	/* On s'assure que le dessin est terminé */
	glFlush();
	
	/* On affiche */
	SDL_GL_SwapBuffers();
	
	ellapsed_time = SDL_GetTicks() - start_time;
	if (ellapsed_time < 10){
		SDL_Delay(10 - ellapsed_time);
	}
}

int state_menu_events(State_Menu_Env* env){
	
	/* Variable de gestion des evenements */
	SDL_Event event;
	
	/* Etat des touches */
	Uint8 *keystates;
	
	while( SDL_PollEvent(&event) ){ 	
		if( event.type == SDL_QUIT ){ 
			return 0; 
		}
	}
	
	keystates = SDL_GetKeyState( NULL );
		
	if( keystates[ SDLK_q ] ) { 
		return 0;
	}
		
	if( keystates[ SDLK_SPACE ] ) { 
		state_current_change(state_game_get());
	}
				
	return 1;
}