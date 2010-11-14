/**
 *	@author		Amirouche HALFAOUI
 *	@date		29.10.2010
 *
 *	Gestion des collisions entre les differents objets
 */

#ifndef COLLISIONS_H
#define COLLISIONS_H
	
	#define COLLISION_LEFT		1
	#define COLLISION_RIGHT		2

	int collision_racket_ground( Racket* racket , Ground* ground, int position);

	void collision_ball_ground( Ball* ball, Ground* ground );

	void collision_ball_racket( Ball* ball, Racket* racket );
	
#endif COLLISIONS_H