/**
 *	@author		Amirouche HALFAOUI
 *	@date		17.06.2010
 *
 *	Gestion de la balle
 */

#ifndef BALL_H
#define BALL_H

	#include <SDL/SDL.h>
	
	/**
	 *	Structure permettant de gerer la balle
	 */
	struct Ball{
		
		/* Position */
		float x;
		float y;
		float z;
		
		/* Vitesse de mouvement */
		float speed_x;
		float speed_y;
		
		/* Taille de la balle */
		float radius;
	};
	
	/* Definition du type Ball */
	typedef struct Ball Ball;
	
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

