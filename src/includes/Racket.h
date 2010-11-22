/**
 *	@author		Amirouche HALFAOUI
 *	@date		17.06.2010
 *
 *	Gestion de la raquette
 */

#ifndef RACKET_H
#define RACKET_H

	#include <GL/gl.h>
	#include "Util.h"
	#include "Ground.h"

	#define RACKET_ACCELERATION 1
	#define RACKET_BREAK 5
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
	 * @param racket		Pointeur vers la rackette à bouger
	 * @param mouse_pos		Coordonnées de la souris
	 * @param e_time		Temps de la frame
	 */
	void racket_move( Racket* racket, Ground* ground, Coord2d mouse_position, Uint32 e_time );

#endif

