#include "includes/Window.h"
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

void window_create(){
	
	/* Position des spots d'eclairage */
	GLfloat spotPosition[4] = {0.0,30.0,30.0,1.0};
	GLfloat spot2Position[4] = {20.0,-40.0,30.0,1.0};
	
	/* Direction du spot d'eclairage */
	GLfloat spotDirection[]={0.0, -1.0, -1.0};
	GLfloat spot2Direction[]={-0.5, 0.5, -1.0};
	
	/* Proprietes du spot d'eclairage */
	GLfloat spotDif[4] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat spotSpec[4] = {0.2f, 0.2f, 0.2f, 1.0f};
	GLfloat spotAmb[4] = {0.2f, 0.2f, 0.2f, 1.0f}; 
	
	GLfloat spot2Dif[4] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat spot2Spec[4] = {1.0f, 0.2f, 0.2f, 1.0f};
	GLfloat spot2Amb[4] = {0.2f, 0.2f, 0.2f, 1.0f}; 
	
	
	/* Surface principale */
	SDL_Surface* screen;
	
	/* initialisation de la video */
	SDL_Init( SDL_INIT_VIDEO );
	
	/* Initialisation de la fenetre */
	screen = SDL_SetVideoMode( WINDOW_WIDTH , WINDOW_HEIGHT , WINDOW_COLOR_DEPTH , SDL_OPENGL );
	
	/* Mise en place du titre de la fenetre */
	SDL_WM_SetCaption( WINDOW_TITLE , NULL);
	
	/* Pour gérer les zIndex */
	glEnable(GL_DEPTH_TEST);
	
	/* Mise en place de la projection en perspective */
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective(40,(double)4/3,1,1000);
	
	/* Mise en place des spots d'éclairage */
	
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, spotDif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, spotSpec);
	glLightfv(GL_LIGHT0, GL_AMBIENT, spotAmb);
	glLightfv(GL_LIGHT0,GL_POSITION,spotPosition);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 45.0);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDirection);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 5);
	
	
	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, spot2Dif);
	glLightfv(GL_LIGHT1, GL_SPECULAR, spot2Spec);
	glLightfv(GL_LIGHT1, GL_AMBIENT, spot2Amb);
	glLightfv(GL_LIGHT1,GL_POSITION,spot2Position);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 40.0);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot2Direction);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 40);
	
}

void window_destroy(){

	SDL_Quit();

}
