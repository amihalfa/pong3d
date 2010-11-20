#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "includes/Util.h"

/**
 *	Fonction de chargement de la texture en memoire graphique
 */
GLuint util_texture_load(char * path){

	GLuint texture_name;
	SDL_Surface * texture;
	
	glGenTextures (1, &texture_name);
	glBindTexture(GL_TEXTURE_2D, texture_name);
	
	texture = IMG_Load(path);
	
	glTexImage2D (GL_TEXTURE_2D, 0, texture->format->BytesPerPixel, texture->w, texture->h, 0, GL_RGB, GL_UNSIGNED_BYTE, texture-> pixels);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	SDL_FreeSurface(texture);
	
	return texture_name;
}