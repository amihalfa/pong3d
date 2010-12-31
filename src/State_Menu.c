#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
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
#include "includes/State_Menu_Items.h"
#include "includes/Animation.h"

/**
 *	Fonction generique permettant d'instancier le singleton etat_menu
 *	@param	flag	Drapeau pour savoir si on cree, on recupere ou on detruit l'etat
 *	@return 		Pointeur vers l'etat de menu
 */
State* state_menu(int action){

	/* Pointeur vers l'etat menu */
	static State* state_menu = (State*)0;

	/* Creation si l'etat n'existe pas */
	if( action == STATE_CREATE && !state_menu ){
		
		state_menu = ( State* ) malloc( sizeof(State) );
		state_menu->env = (State_Menu_Env*) malloc( sizeof(State_Menu_Env) );
		state_menu->init_handler = &state_menu_init;
		state_menu->main_handler = &state_menu_main;
		state_menu->events_handler = &state_menu_events;

		State_Menu_Env* e = (State_Menu_Env*)(state_menu->env);
		
		/* Gestion de la taille de l'ecran */
		SDL_Rect **modes = SDL_ListModes(NULL, SDL_FULLSCREEN|SDL_OPENGL);
		GLfloat ratio = (GLfloat)modes[0]->w/(GLfloat)modes[0]->h;
 		
		/* Au dessus ou en dessous des 4/3 */
		if(ratio >= 1.33){
			e->w_width = 600.0f * ratio;
			e->w_height = 600.0f;
		} else {
			e->w_width = 800.0f;
			e->w_height = 800.0f * ratio;
		}
		
		/* Mise en position du curseur de souris */
		e->mouse.x = ((State_Menu_Env*)(state_menu->env))->w_width / 2.0f;
		e->mouse.y = ((State_Menu_Env*)(state_menu->env))->w_height / 2.0f;
		
		/* Recuperation du fichier de config */
		config_load_state_menu((State_Menu_Env*)(state_menu->env));
	}
	
	/* Destruction de l'etat menu */
	else if( action == STATE_DESTROY && state_menu ){
		free(state_menu->env);
		free(state_menu);
		state_menu = (State*)0;
	}
	
	/* Retour du pointeur vers l'etat menu */
	return state_menu;
}

/**
 *	Fonction permettant d'instancier l'etat menu
 */
void state_menu_create(){
	state_menu( STATE_CREATE );
}

/**
 *	Recuperation du pointeur vers l'etat menu
 *	@return			Pointeur vers l'instance de l'etat menu en cours
 */
State* state_get_menu(){
	return state_menu( STATE_GET );
}

/**
 *	Destruction de l'etat menu
 */
void state_menu_destroy(){
	state_menu( STATE_DESTROY );
}

/**
 * Fonction maitresse de l'etat menu, appelee a chaque tour de boucle,
 * elle s'occupe de coordonner moteur physique et moteur graphique
 * @param env		Environnement de menu
 * @param e_time	Temps de latence donne par la boucle principale
 */
void state_menu_main(State_Menu_Env* env, Uint32 e_time){

	/* Recuperation du temps de latence */
	env->ellapsed_time = e_time;
	
	/* Animation du menu */
	animation_state_menu(env, e_time);
	
	/* Dessin du menu */
	state_menu_draw(env);

}

/**
 *	Initialisation de l'etat menu
 *	@param	env		Environnement de l'etat menu
 */
void state_menu_init(State_Menu_Env* env){

	int i, j;
	
	/* Enregistrements des nombres d'elements par menu */
	env->itemsnb[STATE_MENU_HOME] = 3;
	env->itemsnb[STATE_MENU_CONTINUE] = 4;
	env->itemsnb[STATE_MENU_PLAY] = 4;
	env->itemsnb[STATE_MENU_CONFIG] = 5;

	/* Initialisation des items du menu */
	for(i = 0; i < STATE_MENU_PAGES; i++){
		
		/* Position en x du premier item pour la page en cours */
		GLfloat first_item_x = env->w_width / 2 - 150.0 * (GLfloat)(env->itemsnb[i]) / 2.0;
		
		/* Proprietes de chaque item de la page */
		for(j = 0; j < env->itemsnb[i]; j++){
			env->menu_item[i][j].position.x = first_item_x + j * 150;
			env->menu_item[i][j].position.y = 250.0f;
			env->menu_item[i][j].anim_step = 0.0f;
			env->menu_item[i][j].anim_dir = 1;
			env->menu_item[i][j].type = MENU_ITEM_DEFAULT;
			env->menu_item[i][j].value = 0;
		}
	}
	
	/* Types d'items particuliers pour la config */
	env->menu_item[STATE_MENU_CONFIG][0].type = MENU_ITEM_SLIDER;
	env->menu_item[STATE_MENU_CONFIG][1].type = MENU_ITEM_CHECKBOX;
	env->menu_item[STATE_MENU_CONFIG][2].type = MENU_ITEM_CHECKBOX;

	/* Chargement des textures des items */
	state_menu_items_init_textures(env);

	/* Valeur des configs */
	for(i = 0; i < CONFIG_NB; i++){
		env->menu_item[STATE_MENU_CONFIG][i].value = env->config[i];
	}
	
	/* Aucun item selectionne au depart */
	env->selected_item = -1;
	
	/* A l'acces au menu, soit l'accueil si pas encore joue, soit la page 'continuer' */
	if(state_game_get_pause() == 0)
		env->selected_page = STATE_MENU_HOME;
	else
		env->selected_page = STATE_MENU_CONTINUE;

	/* Chargement des textures des autres parties de l'ecran */
	env->logo_texture = util_texture_load("images/menu/logo.png");
	env->top_texture = util_texture_load("images/menu/haut.png");
	env->bottom_texture = util_texture_load("images/menu/bas_fond.png");
	env->footer_texture = util_texture_load("images/menu/bas.png");
	env->mouse_texture = util_texture_load("images/menu/curseur.png");

	/* On enleve les params de la 3D */
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_COLOR_MATERIAL);

	/* On dimensionne le point de vue */
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	gluOrtho2D(0.0f, env->w_width, 0.0f, env->w_height);
}

/**
 *	Affichage de l'etat menu
 *	@param	env		Environnement de l'etat menu
 */
void state_menu_draw(State_Menu_Env* env){

	int i;

	/* On vide le buffer d'affichage */
	glClear( GL_COLOR_BUFFER_BIT );

	/* Matrice de manipulation des objets */
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	/* On dessinne le panneau du haut */
 	util_texture_display(env->top_texture, 0.0f, 500.0f, env->w_width, 100.0f);

	/* On dessinne le logo par dessus le panneau du haut */
 	util_texture_display(env->logo_texture, env->w_width/2.0f - 180.0f, 520.0f, 320.0f, 80.0f);

	/* On dessinne le bas de page */
 	util_texture_display(env->bottom_texture, 0.0f, 0.0f, env->w_width, 16.0f);
	util_texture_display(env->footer_texture, env->w_width/2.0f - 128.0f, 0, 256.0f, 32.0f);

	/* On dessinne les items de la page courante */
	for(i = 0; i < env->itemsnb[env->selected_page]; i++){
		menu_item_draw( &(env->menu_item[env->selected_page][i]) );
	}

	/* Dessin de la souris */
	util_texture_display(env->mouse_texture, env->mouse.x, env->mouse.y-32.0f, 32.0f, 32.0f);

	/* On s'assure que le dessin est termine */
	glFlush();

	/* On affiche */
	SDL_GL_SwapBuffers();

}

/**
 *	Gestionnaire des evenements de l'etat menu
 * @param env		Environnement du menu
 * @return			0 pour quitter l'appli et 1 sinon
 */
int state_menu_events(State_Menu_Env* env){

	/* Variable de gestion des evenements */
	SDL_Event event;

	/* Pour recuperer la touche pressee */
	int key_pressed;

    state_menu_cursor_handler(env);

	/* Recuperation d'un evenement */
	while(SDL_PollEvent(&event)){
		
		/* Analyse de l'evenement */
		switch(event.type){
			case SDL_QUIT:
				return 0;
			break;
			case SDL_MOUSEBUTTONDOWN:
				if(event.button.button == SDL_BUTTON_LEFT)
					if(state_menu_items_select(env) == 0){
						return 0;
					}
				break;
			default:
				break;
		}
	}
	return 1;
}

/**
 * Fait bouger le curseur dans l'etat menu
 * @param env		Environnement du menu
 */
void state_menu_move_cursor(State_Menu_Env* env){

    Coord2d move;
	
	/* S'il ya eu reellement un mouvement */
	if ( env->mouse_motion.x != 0 && env->mouse_motion.y != 0){
		
		/* Si la souris ne sort pas de l'ecran */
		move.x = env->mouse.x + (GLfloat)env->ellapsed_time/10.0 * env->mouse_motion.x;
		move.y = env->mouse.y + (GLfloat)env->ellapsed_time/10.0 * env->mouse_motion.y;

		/* A l'horizontale */
		if(move.x >= 0 && move.x <= env->w_width)
			env->mouse.x = move.x;

		/* A la verticale */
		if(move.y > 0 && move.y <= env->w_height)
			env->mouse.y = move.y;
	}
}

/**
 * Gestionnaire du curseur de souris
 * S'occupe des mouvement et du survol d'elements
 * @param env		Environnement du menu
 */
void state_menu_cursor_handler(State_Menu_Env* env){

	int rel_x, rel_y, i;

    /* Recuperation de la position relative de la souris */
	SDL_GetRelativeMouseState(&rel_x, &rel_y);
	
	/* Deduction du mouvement a faire a la souris */
	env->mouse_motion.y = -(GLfloat)rel_y;
	env->mouse_motion.x = (GLfloat)rel_x;
	
	/* On fait bouger le curseur */
	state_menu_move_cursor(env);
	
	/* On retrouve l'item sur lequel se trouve le curseur, -1 si aucun */
	env->selected_item = -1;
	for(i = 0; i < env->itemsnb[env->selected_page]; i++){
        if( menu_item_mouse_over(&(env->menu_item[env->selected_page][i]), &env->mouse) ){
            env->selected_item = i;
        }
    }
}

/**
 * Actionne la sauvegarde de la config du menu config vers le fichier de config
 * @param env		Environnement du menu
 */
void state_menu_save_config_items(State_Menu_Env* env){
	
	/* On repasse à l'envirronement les valeurs des items de config */
	env->config[CONFIG_MOUSE_SENSIBILITY] = env->menu_item[STATE_MENU_CONFIG][CONFIG_MOUSE_SENSIBILITY].value;
	env->config[CONFIG_REFLECTION] = env->menu_item[STATE_MENU_CONFIG][CONFIG_REFLECTION].value;
	env->config[CONFIG_PARTICLES] = env->menu_item[STATE_MENU_CONFIG][CONFIG_PARTICLES].value;
	
	/* On lance la sauvegarde dans le fichier de config */
	config_save_state_menu(env->config);
	
}
