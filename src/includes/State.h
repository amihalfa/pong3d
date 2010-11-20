#ifndef STATE_H
#define STATE_H

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
		void ( *main_handler )( void* );
		
		/** 
		 *	Fonction de gestion des événements de l'état courant 
		 *	@param	env		Environnement attache a l'etat
		 */
		int ( *events_handler )( void* );

	};

	typedef struct State State;


	/**
	 *	Fonction permettant de retrouver l'etat courant de l'application
	 *	@return 	Pointeur vers l'etat courant de l'application
	 */
	State* state_current_get();
	
	/**
	*	Fonction permettant de retrouver l'etat courant de l'application
	*	@return 	Pointeur vers l'etat courant de l'application
	*/
	State* state_current_set(State*);
	

#endif STATE_H

