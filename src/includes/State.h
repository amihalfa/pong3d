#ifndef STATE_H
#define STATE_H

	#include <SDL/SDL.h>

	#define STATE_CREATE	0
	#define STATE_GET		1
	#define STATE_DESTROY	2

	struct State{

		/** 
		 *	Environnement associé à l'état en cours de l'application 
		 */
		void* env;
		
		/**
		 *	Fonction d'initialisation de l'état courant 
		 *	@param	env		Environnement attache a l'etat
		 */
		void ( *init_handler )( void* );
		
		/** 
		 *	Fonction d'affichage de l'état courant 
		 *	@param	env		Environnement attache a l'etat
		 */
		void ( *main_handler )( void*, Uint32 );
		
		/** 
		 *	Fonction de gestion des événements de l'état courant 
		 *	@param	env		Environnement attache a l'etat
		 */
		int ( *events_handler )( void*, Uint32 );

	};

	typedef struct State State;


	/**
	 *	Fonction permettant de retrouver l'etat courant de l'application
	 *	@return 	Pointeur vers l'etat courant de l'application
	 */
	State* current_state_get();
	
	/**
	*	Fonction permettant de retrouver l'etat courant de l'application
	*	@return 	Pointeur vers l'etat courant de l'application
	*/
	State* current_state_set(State*);
	
	/**
	 *	Gestionnaire d'evenements de l'etat courant
	 */
	int current_state_events(Uint32 e_time);
	
	void current_state_main(Uint32 e_time);
	
	void* current_state_env();

#endif STATE_H

