#ifndef STATE_GAME
#define	STATE_GAME

struct State_Game_Env{
	Ground ground;
	Racket racket_top;
	Racket racket_bottom;
	Ball ball;
};

typedef struct State_Game_Env State_Game_Env;


State* state_game(int);

void state_game_create();

State* state_game_get();

void state_game_destroy();

/**
 *	Initialisation de l'etat de jeu
 *	@param	env		Environnement du jeu
 */
void state_game_init(State_Game_Env* env);

/**
 *	Dessin de l'état de jeu
 */
void state_game_draw(State_Game_Env* env);

/**
 *	Gestionnaire des evenements de l'etat de jeu
 */
int state_game_events(State_Game_Env* env);

#endif STATE_GAME