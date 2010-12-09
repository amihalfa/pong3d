/**
 *	@author		Amirouche HALFAOUI
 *	@author		Antoine HEZARD
 *	@date		17.06.2010
 *
 *	Gestion du terrain
 */

#ifndef GROUND_H
#define GROUND_H

	/**
	*	Structure permettant de gerer le terrain
	*/
	typedef struct Ground{
		
		/** Hauteur du terrain */
		float height;
		
		/** Longueur du terrain */
		float length;
		
		/** Largeur du terrain */
		float width;
		
		/** Identifiant de la texture a appliquer au terrain */
		GLuint texture;
		
	} Ground;
	
	/**
	 *	Dessin du terrain en OpenGL
	 *	@param	ground		Pointeur vers la structure a utiliser pour le dessin
	 */
	void ground_draw( Ground* ground );
	

#endif

