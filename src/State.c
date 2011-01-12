#include <SDL/SDL.h>
#include "includes/State.h" 

State* state_get_current() {
    return state_set_current((State*) 0);
}

State* state_set_current(State* s) {

    /* Pointeur statique vers l'etat courant */
    static State* state_cur;
    if (s) {
        state_cur = s;
        state_cur->init_handler(state_cur->env);
    }

    return state_cur;
}

int current_state_events(Uint32 e_time) {
    return state_get_current()->events_handler(current_state_env(), e_time);
}

void current_state_main(Uint32 e_time) {
    state_get_current()->main_handler(current_state_env(), e_time);
}

void* current_state_env() {
    return state_get_current()->env;
}