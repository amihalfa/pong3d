#include <GL/glu.h>
#include "includes/Util.h"
#include "includes/State_Menu.h"
#include "includes/State_Game.h"
#include "includes/Animation.h"

/**
 *	Fonction generale de manipulation de l'etat menu
 */
State* state_menu(int action){
	
	static State* state_menu = (State*)0;
	
	if( action == STATE_CREATE && !state_menu ){
		
		state_menu = ( State* ) malloc( sizeof(State) );
		state_menu->env = ( State_Menu_Env* ) malloc( sizeof(State_Menu_Env) );
		state_menu->init_handler = &state_menu_init;
		state_menu->main_handler = &state_menu_main;
		state_menu->events_handler = &state_menu_events;
		
	}
	else if( action == STATE_DESTROY && state_menu ){
			
		free(state_menu->env);
		free(state_menu);
		state_menu = (State*)0;
	}
	
	return state_menu;
}

/**
 *	Creation de l'etat menu
 */
void state_menu_create(){
	state_menu( STATE_CREATE );
}

/**
 *	Recuperation de l'etat menu
 *	@return 	pointeur vers l'etat menu
 */
State* state_menu_get(){
	return state_menu( STATE_GET );
}

/**
 *	Liberation des ressources occupees par l'etat menu
 */
void state_menu_destroy(){
	state_menu( STATE_DESTROY );
}

/**
 *	Initialisation de l'etat menu
 *	@param	env		Envirronnement de l'etat menu
 */
void state_menu_init(State_Menu_Env* env){
		
	/* Proprietes du spot d'eclairage */
	GLfloat spotDif[] = {0.8f, 0.8f, 0.8f, 1.0f};
	GLfloat spotSpec[] = {0.2f, 0.2f, 0.2f, 1.0f};
	GLfloat spotAmb[] = {0.2f, 0.2f, 0.2f, 1.0f}; 
	
	Menu_Item menu_item = { 0.0 , 0.0 , 0.0 , 1.0 , 10.0 , 25.0 , 0 , 0.0 , 1 };
	
	menu_item.texture = util_texture_load ("images/menu/jouer.jpg");
	env->menu_item[0] = menu_item;
	
	menu_item.y = -10;
	menu_item.texture = util_texture_load("images/menu/quitter.jpg");
	env->menu_item[1] = menu_item;

	env->selected_item = 1;
	
	/* Activation de la lumiere */
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, spotDif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, spotSpec);
	glLightfv(GL_LIGHT0, GL_AMBIENT, spotAmb);
	
}

/**
 *	Affichage de l'etat menu
 *	@param	env		Envirronnement de l'etat menu
 */
void state_menu_draw(State_Menu_Env* env){
	
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
	gluLookAt(12.5,-40.0,40,12.5,-5,0,0,0,1);
	
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
	
}

/**
 *	Gestion des evenements de l'etat menu
 *	@param	env		Envirronnement de l'etat menu
 */
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
		
	if( keystates[ SDLK_RETURN ] ) { 
		switch(env->selected_item){
			case 0:
				current_state_set(state_game_get());
			break;
			default:
				return 0;
			break;	
		}
	}
		
	if( keystates[ SDLK_DOWN ] ) { 
		if(env->selected_item+1 < STATE_MENU_ITEMSNB)
			env->selected_item++;
	}
	
	if( keystates[ SDLK_UP ] ) { 
		if(env->selected_item > 0)
			env->selected_item--;
	}
				
	return 1;
}


void state_menu_main(State_Menu_Env* env, Uint32 e_time){
	
	animation_state_menu(env, e_time);
	state_menu_draw(env);
	
}