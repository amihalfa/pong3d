/**
 *	@author		Amirouche HALFAOUI
 *	@date		17.06.2010
 *
 *	Gestion du terrain
 */

#ifndef GROUND_H
#define GROUND_H

	/**
	*	Structure permettant de gerer le terrain
	*/
	struct Ground{
		
		/* Taille du terrain */
		float height;
		float length;
		float width;
	};

	/* Definition du type Ground */
	typedef struct Ground Ground;
	
	/**
	 *	Dessin du terrain en OpenGL
	 *	@param	ground		Pointeur vers la structure a utiliser pour le dessin
	 */
	void ground_draw( Ground* ground );
	

#endif GROUND_H
