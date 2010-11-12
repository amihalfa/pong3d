#include "includes/State.h" 


State* state_current_get(){
	
	return state_current_change( (State*) 0 );
}


State* state_current_change(State* s){
	
	/* Pointeur statique vers l'etat courant */
	static State* state_cur;
	if(s){
		state_cur = s;
		state_cur->init_handler( state_cur->env );
	}
		
	return state_cur;
}
