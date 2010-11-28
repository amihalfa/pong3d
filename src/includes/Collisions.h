/**
 *	@author		Antoine HEZARD
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

	#define COLLISION_LEFT		0
	#define COLLISION_RIGHT		1

	/**
	 *	Gestion generale des collisions de l'etat Jeu
	 *	@param	env			Envirronement du jeu 
	 *	@return				Nul si pas de collision, un entier sinon
	 */
	int collision_state_game( State_Game_Env* env );

	int collision_racket_ground( Racket* racket , Ground* ground, int position);

	int collision_ball_ground( Ball* ball, Ground* ground );

	int collision_ball_racket( Ball* ball, Racket* racket );
	
	int collision_ball_ball( Ball* ball_a, Ball* ball_b );
	
#endif
