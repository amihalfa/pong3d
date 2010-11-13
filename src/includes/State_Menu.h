#ifndef STATE_MENU
#define	STATE_MENU

	#define STATE_MENU_ITEMSNB		2
	struct State_Menu_Env{
		
		Menu_Item menu_item[STATE_MENU_ITEMSNB];
		
	};
	
	typedef struct State_Menu_Env State_Menu_Env;
	
	State* state_menu(int);
	
	void state_menu_create();
	
	State* state_menu_get();
	
	void state_menu_destroy();
	
	/**
	*	Initialisation de l'etat de jeu
	*	@param	env		Environnement du jeu
	*/
	void state_menu_init(State_Menu_Env* env);
	
	/**
	*	Dessin de l'état de jeu
	*/
	void state_menu_draw(State_Menu_Env* env);
	
	/**
	*	Gestionnaire des evenements de l'etat de jeu
	*/
	int state_menu_events(State_Menu_Env* env);
	
	
#endif STATE_MENU