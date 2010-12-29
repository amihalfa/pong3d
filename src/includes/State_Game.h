#ifndef STATE_GAME
#define	STATE_GAME

	#define STATE_GAME_BALLS	500

	#define RACKET_BOTTOM 0
	#define RACKET_TOP 1

	struct State_Game_Env;

	typedef struct State_Game_Env{
		Ground ground;
		Racket racket[2];
		Ball ball[STATE_GAME_BALLS];
		int balls_nb;
		Uint16 w_height, w_width;
		Sint16 mouse_motion_x, mouse_motion_y;
		Uint8 *keystates;
		Uint32 ellapsed_time;
		float config[CONFIG_NB];
		
		/** Fonction de gestion de l'IA */
		void (*AI_handler)(struct State_Game_Env* env, int racket_id);
		
	} State_Game_Env;

	


	State* state_game(int);

	void state_game_create();

	State* state_game_get();

	void state_game_destroy();


	void state_game_main(State_Game_Env* env, Uint32 e_time);

	/**
	 *	Initialisation de l'etat de jeu
	 *	@param	env		Environnement du jeu
	 */
	void state_game_init(State_Game_Env* env);

	/**
	 *	Dessin de l'etat de jeu
	 */
	void state_game_draw(State_Game_Env* env);

	/**
	 *	Gestionnaire des evenements de l'etat de jeu
	 */
	int state_game_events(State_Game_Env* env);
	
	int state_game_pause(int pause);
	int state_game_get_pause();
	void state_game_set_pause(int pause);
	
	int state_game_level(int level);
	int state_game_get_level();
	void state_game_set_level(int level);

#endif

