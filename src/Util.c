#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "includes/Util.h"

GLuint util_texture_load(char * path){

	GLuint texture_id;
	SDL_Surface* texture;
	
	/* Generation d'un id pour la texture */
	glGenTextures (1, & texture_id);
	
	/* Chargement en memoire avec la SDL */
	texture = SDL_LoadBMP(path);
	
	/* Passage de la SDL a OpenGL */
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA8, texture->w, texture->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->pixels);
	
	/* Liberation de la memoire */
	SDL_FreeSurface(texture);
	
	return texture_id;
}