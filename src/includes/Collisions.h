/**
 *	@author		Amirouche HALFAOUI
 *	@date		29.10.2010
 *
 *	Gestion des collisions entre les differents objets
 */

#ifndef COLLISIONS_H
#define COLLISIONS_H

	#include "Racket.h"
	#include "Ball.h"
	#include "Ground.h"
	#include "State_Game.h"

	#define COLLISION_LEFT		1
	#define COLLISION_RIGHT		2

	int collision_state_game(State_Game_Env* env);

	int collision_racket_ground( Racket* racket , Ground* ground, int position);

	void collision_ball_ground( Ball* ball, Ground* ground );

	void collision_ball_racket( Ball* ball, Racket* racket );
	
#endif
