#ifndef STATE_GAME
#define	STATE_GAME

	#define STATE_GAME_BALLS	10
	#include <SDL/SDL.h>
	#include "State.h"
	#include "Ground.h"
	#include "Racket.h"
	#include "Ball.h"


	#define RACKET_BOTTOM 0
	#define RACKET_TOP 1

	struct State_Game_Env{
		Ground ground;
		Racket racket_top;
		Racket racket_bottom;
		Ball ball[STATE_GAME_BALLS];
		int balls_nb;
		Coord2d mouse_motion;
		Uint8 *keystates;
		Uint32 ellapsed_time;
	};

	typedef struct State_Game_Env State_Game_Env;


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
	 *	Dessin de l'état de jeu
	 */
	void state_game_draw(State_Game_Env* env);

	/**
	 *	Gestionnaire des evenements de l'etat de jeu
	 */
	int state_game_events(State_Game_Env* env);
	


#endif

