#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
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
	
	glTexImage2D (GL_TEXTURE_2D, 0, texture->format->BytesPerPixel, texture->w, texture->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture-> pixels);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	SDL_FreeSurface(texture);
	
	return texture_name;
	
}


int load_configuration(State_Game_Env* env_game){
	char* vars[NB_CONFIG] = {"mouse_sensibility=%f\n"};
	int i;
	FILE* config = fopen("config/config.cfg", "r+");
	if (!config) {
		return 0;
	}
	for (i = 0; i < NB_CONFIG; i++) {
		fscanf(config, vars[i], &env_game->config[i]);
	}
	return 1;
}


void util_reflection_ball(Ball* ball, Ground* ground){
	
	glColorMask(0,0,0,0);
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glDisable(GL_DEPTH_TEST);
	
	ground_draw(ground);
	
	glEnable(GL_DEPTH_TEST);
	
	glColorMask(1,1,1,1);
	glStencilFunc(GL_EQUAL, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
		
	glPushMatrix();					
		glScalef(1.0f, 1.0f, -1.0f);
		glTranslatef(0.0f, 0.0f, 0.5f);
		ball_draw(ball);	
	glPopMatrix();
				
	glDisable(GL_STENCIL_TEST);							
}

void util_reflection_racket(Racket* racket, Ground* ground){
	
	glColorMask(0,0,0,0);
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glDisable(GL_DEPTH_TEST);
	
	ground_draw(ground);
	
	glEnable(GL_DEPTH_TEST);
	
	glColorMask(1,1,1,1);
	glStencilFunc(GL_EQUAL, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
		
	glPushMatrix();					
		glScalef(1.0f, 1.0f, -1.0f);
		glTranslatef(0.0f, 0.0f, 0.5f);
		racket_draw(racket);	
	glPopMatrix();
				
	glDisable(GL_STENCIL_TEST);							
}