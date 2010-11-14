/**
 *	@author		Amirouche HALFAOUI
 *	@date		17.06.2010
 *
 *	Gestion de la raquette
 */

#ifndef RACKET_H
#define RACKET_H

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


#endif RACKET_H
