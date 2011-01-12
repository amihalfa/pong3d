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
#include "includes/State_Menu.h"
#include "includes/State_Menu_Util.h"

/**
 * Fait bouger le curseur dans l'etat menu
 * @param env		Environnement du menu
 */
void smu_move_cursor(State_Menu_Env* env) {

    Coord2d move;

    /* S'il ya eu reellement un mouvement */
    if (env->mouse_motion.x != 0 && env->mouse_motion.y != 0) {

        /* Si la souris ne sort pas de l'ecran */
        move.x = env->mouse.x + (GLfloat) env->ellapsed_time / 10.0 * env->mouse_motion.x;
        move.y = env->mouse.y + (GLfloat) env->ellapsed_time / 10.0 * env->mouse_motion.y;

        /* A l'horizontale */
        if (move.x >= 0 && move.x <= env->w_width)
            env->mouse.x = move.x;

        /* A la verticale */
        if (move.y > 0 && move.y <= env->w_height)
            env->mouse.y = move.y;
    }
}

/**
 * Gestionnaire du curseur de souris
 * S'occupe des mouvement et du survol d'elements
 * @param env		Environnement du menu
 */
void smu_cursor_handler(State_Menu_Env* env) {

    int rel_x, rel_y, i;

    /* Recuperation de la position relative de la souris */
    SDL_GetRelativeMouseState(&rel_x, &rel_y);

    /* Deduction du mouvement a faire a la souris */
    env->mouse_motion.y = -(GLfloat) rel_y;
    env->mouse_motion.x = (GLfloat) rel_x;

    /* On fait bouger le curseur */
    smu_move_cursor(env);

    /* On retrouve l'item sur lequel se trouve le curseur, -1 si aucun */
    env->selected_item = -1;
    for (i = 0; i < env->itemsnb[env->selected_page]; i++) {
        if (menu_item_mouse_over(&(env->menu_item[env->selected_page][i]), &env->mouse)) {
            env->selected_item = i;
        }
    }
}

/**
 * Actionne la sauvegarde de la config du menu config vers le fichier de config
 * @param env		Environnement du menu
 */
void smu_save_config_items(State_Menu_Env* env) {

    /* On repasse à l'envirronement les valeurs des items de config */
    env->config[CONFIG_MOUSE_SENSIBILITY] = env->menu_item[STATE_MENU_CONFIG][CONFIG_MOUSE_SENSIBILITY].value;
    env->config[CONFIG_REFLECTION] = env->menu_item[STATE_MENU_CONFIG][CONFIG_REFLECTION].value;
    env->config[CONFIG_PARTICLES] = env->menu_item[STATE_MENU_CONFIG][CONFIG_PARTICLES].value;

    /* On lance la sauvegarde dans le fichier de config */
    config_save_state_menu(env->config);

}