#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "includes/Coords.h"
#include "includes/Particles.h"
#include "includes/Window.h"
#include "includes/State.h"
#include "includes/Racket.h"
#include "includes/Ball.h"
#include "includes/Ground.h"
#include "includes/Config.h"
#include "includes/State_Game.h"
#include "includes/Menu_Item.h"
#include "includes/State_Menu.h"
#include "includes/Util.h"

#define FRAME_DURATION	10

/**
 *	Programme principal Pong
 *	Creation de la fenetre
 *	Permet le basculement entre les differents etats de l'application
 */
int main(int argc, char **argv) {

    Uint32 s_time, e_time = 0;

    /* Mise en place du fenetrage */
    window_create();

    /* Creation des differents etats de l'application */
    state_menu_create();
    state_game_create();

    /* Mise en place de l'etat courant */
    state_set_current(state_get_menu());

    s_time = SDL_GetTicks();

    /* Boucle de gestion des evenements et de l'affichage */
    while (current_state_events(e_time)) {

        /* Fonction principale de l'etat courant */
        current_state_main(e_time);

        /* on recupere le temps que la fonction principale a dure */
        e_time = SDL_GetTicks() - s_time;

        /* et on fait un delai si ce temps est inferieur au temps d'une frame */
        if (e_time < FRAME_DURATION) {
            SDL_Delay(FRAME_DURATION - e_time);
        }

        /* on recupere le temps ecoule effectif */
        e_time = SDL_GetTicks() - s_time;

        /* et le temps de fin de boucle */
        s_time = SDL_GetTicks();
    }

    /* Destruction de la fenetre et des etats */
    window_destroy();
    state_menu_destroy();
    state_game_destroy();

    return 0;
}
