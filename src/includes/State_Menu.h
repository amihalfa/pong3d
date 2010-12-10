#ifndef STATE_MENU
#define	STATE_MENU

	
	/* Nombre d'elements du menu */
	#define STATE_MENU_ITEMSNB		2
	
	struct State;

	/**
	 *	Environnement pour l'etat menu
	 */
	struct State_Menu_Env{
		
		Menu_Item menu_item[STATE_MENU_ITEMSNB];
		
		int selected_item;
		Uint32 ellapsed_time;
		
	};
	typedef struct State_Menu_Env State_Menu_Env;
	
	/**
	 *	Fonction generique permettant d'instancier le singleton etat_menu
	 *	@param	flag	Drapeau pour savoir on cree, on recupere ou on detruit l'etat
	 *	@return 		Pointeur vers l'etat de menu
	 */
	struct State* state_menu(int flag);
	
	/**
	 *	Fonction permettant d'instancier l'etat menu
	 */
	void state_menu_create();
	
	/**
	 *	Recuperation du pointeur vers l'etat menu
	 *	@return			Pointeur vers l'instance de l'etat menu en cours
	 */
	struct State* state_get_menu();
	
	/**
	 *	Destruction de l'etat menu
	 */
	void state_menu_destroy();
	
	/**
	 *	Initialisation de l'etat de jeu
	 *	@param	env		Environnement du jeu
	 */
	void state_menu_init(State_Menu_Env* env);
	
	/**
	 *	Dessin de l'etat de jeu
	 */
	void state_menu_draw(State_Menu_Env* env);
	
	/**
	 *	Gestionnaire des evenements de l'etat de jeu
	 */
	int state_menu_events(State_Menu_Env* env);
	
	void state_menu_main(State_Menu_Env* env, Uint32 e_time);
	
	
#endif
