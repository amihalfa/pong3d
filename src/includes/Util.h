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
	
	void util_reflection_ball(Ball* ball, Ground* ground);

	void util_reflection_racket(Racket* racket, Ground* ground);

	
#endif
