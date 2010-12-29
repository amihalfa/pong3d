/**
 *	@author		Antoine HEZARD
 *	@author		Amirouche HALFAOUI
 *	@date		17.06.2010
 *
 *	Gestion de la balle
 */

#ifndef BALL_H
#define BALL_H

	typedef struct Ball{
		
		/** Position de la balle */
		Coord3d position;
		
		/** Vitesse de la balle */
		Coord2d speed;

		/** Rayon de la balle */
		float radius;
		
		Particles particles;
		
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

