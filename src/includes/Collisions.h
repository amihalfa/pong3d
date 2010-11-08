/**
 *	@author		Amirouche HALFAOUI
 *	@date		29.10.2010
 *
 *	Gestion des collisions entre les differents objets
 */

#ifndef COLLISIONS_H
#define COLLISIONS_H


	/**
	 *	En cas de collision entre la balle et le terrain
	 *	retourne la partie du terrain touchee
	 *
	 *	@param	ball	Pointeur sur la tructure designant la balle
	 *	@param	ground	Pointeur sur la structure designant le terrain
	 *
	 *	@return			Entier designant la partie du terrain touchee
	 *
	int collision_ball_ground(Ball* ball, Ground* ground);

	*
	 *	En cas de collision entre la balle et une raquette
	 *	retourne la partie de la raquette touchee
	 *
	 *	@param	ball	Pointeur sur la tructure designant la balle
	 *	@param	racket	Pointeur sur la structure designant la raquette
	 *
	 *	@return			Entier designant la partie de la raquette touchee
	 *
	int collision_ball_racket(Ball* ball, Racket* racket);*/

#endif