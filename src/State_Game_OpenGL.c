#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "includes/Coords.h"
#include "includes/Particles.h"
#include "includes/State.h"
#include "includes/Racket.h"
#include "includes/Ball.h"
#include "includes/Ground.h"
#include "includes/Config.h"
#include "includes/State_Game.h"
#include "includes/State_Game_OpenGL.h"


void sgo_init(){
	
	float ratio;
   
	/* Resolutions possibles sous la config actuelle */
	SDL_Rect **modes;
	
	/* Proprietes du spot d'eclairage */
	GLfloat spotDif[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat spotSpec[] = {0.2f, 0.2f, 0.2f, 1.0f};
	GLfloat spotAmb[] = {0.2f, 0.2f, 0.2f, 1.0f};
	
	/* Activation de la lumiere */
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, spotDif);
    glLightfv(GL_LIGHT0, GL_SPECULAR, spotSpec);
    glLightfv(GL_LIGHT0, GL_AMBIENT, spotAmb);

    /* Pour gerer les zIndex */
    glEnable(GL_DEPTH_TEST);

    /* Mise en place des spots d'eclairage */
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);

    /* Recuperation des resolutions possibles */
    modes = SDL_ListModes(NULL, SDL_FULLSCREEN|SDL_OPENGL);

    /* Calcul du ratio de la resolution */
    ratio = (float) modes[0]->w / modes[0]->h;

    /* Mise en place de la projection en perspective */
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 40 , ratio , 1 , 1000);

	
}

void sgo_draw(){
	
	/* On s'assure que le dessin est termine */
    glFlush();

    /* On affiche */
	SDL_GL_SwapBuffers();
    
	/* Position du spot d'eclairage */
    GLfloat spotPosition[] = {0.0 , -30.0 , 40.0 , 1.0};

    /* Direction du spot d'eclairage */
    GLfloat spotDirection[]={0.0 , 1.0 , -1.0};

    /* On vide le buffer d'affichage */
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );

    /* Matrice de manipulation des objets */
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    /* Changement de position de la camera */
    gluLookAt(0,-40.0,30,0,-5,0,0,0,1);

    /* On place la lumiere dans la scene */
    glLightfv(GL_LIGHT0,GL_POSITION,spotPosition);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 45.0);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDirection);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 5);

}