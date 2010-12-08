/**
 *	@author		Antoine HEZARD
 *	@author		Amirouche HALFAOUI
 *	@date		17.06.2010
 *
 *	Gestion de la balle
 */

#ifndef BALL_H
#define BALL_H

	#include <SDL/SDL.h>

	#define BALL_MAX_SPEED 0.06
	
	
	struct Coord2d {
		float x, y;
	};
	
	typedef struct Coord2d Coord2d;
	
	/**
	 *	Structure permettant de gerer la balle
	 */
	typedef struct Ball{
		
		/** Position de la balle en x */
		float x;
		
		/** Position de la balle en y */
		float y;
		
		/** Position de la balle en z
		*/
		float z;
		
		/** Vitesse de la balle */
		Coord2d speed;

		/** Rayon de la balle */
		float radius;
		
	} Ball;
	
	/**
	 *	Dessin de la balle en OpenGL
	 *	@param	ball		Pointeur vers la structure a utiliser pour le dessin
	 */
	void ball_draw( Ball* ball );
	
	/**
	 *	Mouvement de la balle en tenant compte de la vitesse
	 *	@param ball			Pointeur vers la structure de balle
	 */
	void ball_move( Ball* ball, Uint32 e_time );

#endif

