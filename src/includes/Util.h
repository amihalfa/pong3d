#ifndef UTIL_H
#define UTIL_H

	#define MIN(a,b)	((a)<(b))?(a):(b)
	#define MAX(a,b)	((a)>(b))?(a):(b)
	#define ABS(a)		((a)>0)?(a):(-a)


	/**
	 *	Fonction de chargement d'une texture
	 *	@param path		Chemin vers le fichier image a charger en tant que texture
	 *	@return			Entier designant l'identifiant de la texture en memoire video
	 */
	GLuint util_texture_load(char * path);
	
	int util_load_configuration(State_Game_Env* env_game);
	
	/**
	 * Relechit une balle sur le terrain
	 * @param	ball	Balle a reflechir
	 * @param	ground	Terrain sur lequel se fait la reflection
	 */ 
	void util_reflection_ball(Ball* ball, Ground* ground);

	/**
	 * Relechit une raquette sur le terrain
	 * @param	racket	Raquette a reflechir
	 * @param	ground	Terrain sur lequel se fait la reflection
	 */ 
	void util_reflection_racket(Racket* racket, Ground* ground);
	
	/**
	 * Relechit les particules sur le terrain
	 * @param	particles	Particules a reflechir
	 * @param	ground		Terrain sur lequel se fait la reflection
	 */ 
	void util_reflection_particles(Particles* particles, Ground* ground);
	
#endif
