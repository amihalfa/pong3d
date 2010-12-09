/**
 *	@author		Antoine HEZARD
 *	@author		Amirouche HALFAOUI
 *	@date		17.06.2010
 *
 *	Gestion de la balle
 */

#ifndef BALL_H
#define BALL_H

	#define BALL_MAX_SPEED 0.06
	#define BALL_HISTO 40
	
	/**
	 *	Structure permettant de gerer la balle
	 */
	typedef struct Ball{
		
		/** Position de la balle */
		Coord3d position;
		
		/** Vitesse de la balle */
		Coord2d speed;

		/** Rayon de la balle */
		float radius;
		
		Coord3d pos_histo[BALL_HISTO];
		
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

