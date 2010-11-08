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
	glTranslated( ball->x , ball->y, ball->z );
	
	/* On applique la couleur */
	glColor3ub( 100 , 100 , 100 );
	
	/* On alloue dynamiquement les parametres pour notre quadrique */
	GLUquadric* params = gluNewQuadric();
	
	/* On dessine la balle */
	gluSphere( params , 2 * ball->radius , 10 , 10 );
	
	/* Liberation des ressources car fin du dessin */
	gluDeleteQuadric(params);
	
	/* On remet la matrice mise en pile au depart */
	glPopMatrix();
	

}