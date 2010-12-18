#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "includes/Config.h"
#include "includes/Coords.h"
#include "includes/Particles.h"
#include "includes/State.h"
#include "includes/Ground.h"
#include "includes/Racket.h"
#include "includes/Ball.h"
#include "includes/State_Game.h"
#include "includes/Util.h"


/**
 *	Dessin de la balle en OpenGL
 *	@param	ball		Pointeur vers la structure a utiliser pour le dessin
 */
void ball_draw( Ball* ball ){
	
	/* On met la matrice actuelle dans la pile avant modif. */
	glPushMatrix();
	
	/* On change le repere */
	glTranslatef( ball->position.x , ball->position.y, ball->position.z );
	
	/* On applique la couleur */
	glColor3ub( 10 , 10 , 200 );
	
	/* On alloue dynamiquement les parametres pour notre quadrique */
	GLUquadric* params = gluNewQuadric();
	
	/* On dessine la balle */
	gluSphere( params , ball->radius , 10 , 10 );
	
	/* Liberation des ressources car fin du dessin */
	gluDeleteQuadric(params);
	
	/* On remet la matrice mise en pile au depart */
	glPopMatrix();
	

}
/**
 *	Mouvement de la balle en tenant compte de la vitesse
 *	@param ball			Pointeur vers la structure de balle
 */
void ball_move( Ball* ball, Uint32 e_time ){

	int i;
	
	/* Sauvegarde des anciennes positions pour faire les particules 
	for( i = 0; i < BALL_HISTO-1; i++ ){
		/* Decalage *
		ball->pos_histo[i].x = ball->pos_histo[i+1].x;
		ball->pos_histo[i].y = ball->pos_histo[i+1].y;
	}
	ball->pos_histo[BALL_HISTO-1].x = ball->position.x;
	ball->pos_histo[BALL_HISTO-1].y = ball->position.y;
	
	/* Nouvelle position */
	ball->position.x += ball->speed.x + (ball->speed.x / 10) * e_time ;
	ball->position.y += ball->speed.y + (ball->speed.y / 10) * e_time;
}