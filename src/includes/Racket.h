/**
 *	@author		Amirouche HALFAOUI
 *	@date		17.06.2010
 *
 *	Gestion de la raquette
 */

#ifndef RACKET_H
#define RACKET_H

	#define RACKET_SPEED_MAX 1.0f
   /**
	*	Structure permettant de gerer une raquette
	*/

	struct Racket{
		
		/* Position */
		Coord3d position;
		
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
	 * @param num_racket	numero de la raquette a bouger
	 */
	void racket_mouse_move(void* v_env, char num_racket );

	/**
	 * Faire bouger la raquette
	 */
	void racket_move(Racket* racket);
#endif

