#include "includes/State.h" 


State* current_state_get(){	
	return current_state_set( (State*) 0 );
}


State* current_state_set(State* s){
	
	/* Pointeur statique vers l'etat courant */
	static State* state_cur;
	if(s){
		state_cur = s;
		state_cur->init_handler( state_cur->env );
	}
		
	return state_cur;
}

int current_state_events(Uint32 e_time){
	return current_state_get()->events_handler( current_state_env(), e_time );
}

void current_state_main(Uint32 e_time){
	current_state_get()->main_handler( current_state_env() , e_time );
}

void* current_state_env(){
	return current_state_get()->env;
}