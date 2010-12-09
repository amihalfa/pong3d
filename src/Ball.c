#include "includes/Ball.h"
#include <GL/gl.h>
#include <GL/glu.h>

/**
 *	Dessin de la balle en OpenGL
 *	@param	ball		Pointeur vers la structure a utiliser pour le dessin
 */
void ball_draw( Ball* ball ){
	
	/* On met la matrice actuelle dans la pile avant modif. */
	glPushMatrix();
	
	/* On change le repere */
	glTranslatef( ball->x , ball->y, ball->z );
	
	/* On applique la couleur */
	glColor3ub( 10 , 10 , 100 );
	
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

	ball->x += ball->speed.x + (ball->speed.x / 10) * e_time ;
	ball->y += ball->speed.y + (ball->speed.y / 10) * e_time;
	
}