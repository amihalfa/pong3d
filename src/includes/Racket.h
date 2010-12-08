/**
 *	@author		Amirouche HALFAOUI
 *	@date		17.06.2010
 *
 *	Gestion de la raquette
 */

#ifndef RACKET_H
#define RACKET_H

	#include <GL/gl.h>
	#include <GL/glu.h>
	#include <SDL/SDL.h>
	#include "Ground.h"

	#define RACKET_SPEED 0.05
   /**
	*	Structure permettant de gerer une raquette
	*/

	struct Racket{
		
		/* Position */
		float x;
		float y;
		float z;
		
		/* Dimensions de la raquette */
		float width;
		float radius;

		/* Vitesse de la raquette */
		float speed;
		
		GLuint texture;
	};

	/* Definition du type Racket */
	typedef struct Racket Racket;

	/**
	 *	Dessin de la raquette en OpenGL
	 *	@param	racket		Pointeur vers la structure a utiliser pour le dessin
	 */
	void racket_draw( Racket* racket );

	/**
	 * Actualise la vitesse de la rackette et la bouge
	 * @param env			Environement
	 * @param num_racket	numero de la rackette a bouger
	 */
	void racket_move(void* v_env, char num_racket );

#endif

