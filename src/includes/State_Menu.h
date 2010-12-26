#ifndef STATE_MENU
#define	STATE_MENU

	/* Nombre d'elements du menu */
	#define STATE_MENU_ITEMSNB_MAX	5
	
	#define STATE_MENU_PAGES		3
	#define STATE_MENU_HOME			0
	#define STATE_MENU_CONTINUE		1
	#define STATE_MENU_CONFIG		2
	
	struct State;

	/**
	 *	Environnement pour l'etat menu
	 */
	struct State_Menu_Env{
		
		/** Tableau des elements du menu */
		Menu_Item menu_item[STATE_MENU_PAGES][STATE_MENU_ITEMSNB_MAX];
		
		/** Nombre d'elements des pages, home, reprendre, reglages */
		int itemsnb[STATE_MENU_PAGES];
		
		/** Page du menu selectionnee */
		int selected_page;
		
		/** Element du menu selectionne */
		int selected_item;
		
		/** Temps de latence */
		Uint32 ellapsed_time;
		
		/** Identifiant de la texture de logo */
		GLuint logo_texture;
		
		/** Identifiant de la texture du haut */
		GLuint top_texture;
		
		/** Identidiant de la texture pied de page */
		GLuint footer_texture;
		
		/** Identidiant de la texture du bas */
		GLuint bottom_texture;
		
		/** Largeur/Hauteur de fenetre utilisee */
		GLfloat w_width, w_height;
		
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
	
	int state_menu_select_item(int page, int item);
	
	void state_menu_main(State_Menu_Env* env, Uint32 e_time);
	
	
#endif
