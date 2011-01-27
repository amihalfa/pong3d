#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "includes/State_Menu_Util.h"
#include "includes/State_Game_Util.h"
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
#include "includes/State_Menu_Items.h"
#include "includes/State_Menu_OpenGL.h"


State* state_menu(int action) {

    /* Pointeur vers l'etat menu */
    static State* state_menu = (State*) 0;
	
	State_Menu_Env* e;
	SDL_Rect **modes;
	GLfloat ratio;

    /* Creation si l'etat n'existe pas */
    if (action == STATE_CREATE && !state_menu) {

        state_menu = (State*) malloc(sizeof (State));
        state_menu->env = (State_Menu_Env*) malloc(sizeof (State_Menu_Env));
        state_menu->init_handler = &state_menu_init;
        state_menu->main_handler = &state_menu_main;
        state_menu->events_handler = &state_menu_events;

        e = (State_Menu_Env*) (state_menu->env);

        /* Gestion de la taille de l'ecran */
        modes = SDL_ListModes(NULL, SDL_FULLSCREEN | SDL_OPENGL);
        ratio = (GLfloat) modes[0]->w / (GLfloat) modes[0]->h;

        /* Au dessus ou en dessous des 4/3 */
        if (ratio >= 4.0 / 3.0) {
            e->w_width = 600.0f * ratio;
            e->w_height = 600.0f;
        } else {
            e->w_width = 800.0f;
            e->w_height = 800.0f / ratio;
        }

        /* Mise en position du curseur de souris */
        e->mouse.x = ((State_Menu_Env*) (state_menu->env))->w_width / 2.0f;
        e->mouse.y = ((State_Menu_Env*) (state_menu->env))->w_height / 2.0f;

        /* Recuperation du fichier de config */
        config_load_state_menu((State_Menu_Env*) (state_menu->env));
    }
        /* Destruction de l'etat menu */
    else if (action == STATE_DESTROY && state_menu) {
        free(state_menu->env);
        free(state_menu);
        state_menu = (State*) 0;
    }

    /* Retour du pointeur vers l'etat menu */
    return state_menu;
}


void state_menu_create() {
    state_menu(STATE_CREATE);
}


State* state_get_menu() {
    return state_menu(STATE_GET);
}


void state_menu_destroy() {
    state_menu(STATE_DESTROY);
}

void state_menu_main(void* environement, Uint32 e_time) {

	State_Menu_Env* env;
	
	env = (State_Menu_Env*) environement;
	
    /* Recuperation du temps de latence */
    env->ellapsed_time = e_time;

    /* Animation du menu */
    animation_state_menu(env, e_time);

    /* Dessin du menu */
    state_menu_draw(env);
}

void state_menu_init(void* environement) {
	
	State_Menu_Env* env;
	
	env = (State_Menu_Env*) environement;

    smi_init(env);

    /* Chargement des textures des items */
    smi_init_textures(env);

    /* Aucun item selectionne au depart */
    env->selected_item = -1;

    /* A l'acces au menu, soit l'accueil si pas encore joue, soit la page 'continuer' */
    if (sgu_get_pause() == 0)
        env->selected_page = STATE_MENU_HOME;
    else
        env->selected_page = STATE_MENU_CONTINUE;

    /* Chargement des textures des autres parties de l'ecran */
    env->logo_texture = util_texture_load("images/menu/logo.png");
    env->top_texture = util_texture_load("images/menu/haut.png");
    env->bottom_texture = util_texture_load("images/menu/bas_fond.png");
    env->footer_texture = util_texture_load("images/menu/bas.png");
    env->mouse_texture = util_texture_load("images/menu/curseur.png");

    smo_init(env->w_width, env->w_height);
}

void state_menu_draw(void* environement) {

    int i;
	State_Menu_Env* env;
	
	env = (State_Menu_Env*) environement;

    smo_draw();

    /* On dessinne le panneau du haut */
    util_texture_display(env->top_texture, 0.0f, 500.0f, env->w_width, 100.0f);

    /* On dessinne le logo par dessus le panneau du haut */
    util_texture_display(env->logo_texture, env->w_width / 2.0f - 180.0f, 520.0f, 320.0f, 80.0f);

    /* On dessinne le bas de page */
    util_texture_display(env->bottom_texture, 0.0f, 0.0f, env->w_width, 16.0f);
    util_texture_display(env->footer_texture, env->w_width / 2.0f - 128.0f, 0, 256.0f, 32.0f);

    /* On dessinne les items de la page courante */
    for (i = 0; i < env->itemsnb[env->selected_page]; i++) {
        menu_item_draw(&(env->menu_item[env->selected_page][i]));
    }

    /* Dessin de la souris */
    util_texture_display(env->mouse_texture, env->mouse.x, env->mouse.y - 32.0f, 32.0f, 32.0f);

}

int state_menu_events(void* environement) {
	
	State_Menu_Env* env;
	
	env = (State_Menu_Env*) environement;

    /* Variable de gestion des evenements */
    SDL_Event event;

    smu_cursor_handler(environement);

    /* Recuperation des evenements */
    while (SDL_PollEvent(&event)) {

        /* Analyse de l'evenement */
        if (event.type == SDL_QUIT) {
            return 0;
        } else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
            if (smi_select(env) == 0) {
                return 0;
            }
        }
    }
    return 1;
}
