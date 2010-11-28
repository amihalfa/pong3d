#ifndef UTIL_H
#define UTIL_H
	
	#include <GL/gl.h>
	
	#define MIN(a,b) ((a)<(b))?(a):(b)
	#define MAX(a,b) ((a)>(b))?(a):(b)
	#define ABS(a) ((a)>0)?(a):(-a)

	struct Coord2d {
		float x, y;
	};

	typedef struct Coord2d Coord2d;

	/**
	 *	Fonction de chargement d'une texture
	 *	@param path		Chemin vers le fichier image a charger en tant que texture
	 *	@return			Entier designant l'identifiant de la texture en memoire video
	 */
	GLuint util_texture_load(char * path);
	
#endif
