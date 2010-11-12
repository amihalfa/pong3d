#include "includes/Racket.h" 
#include <GL/gl.h>
#include <GL/glu.h>

/**
 *	Dessin de la raquette en OpenGL
 *	@param	racket		Pointeur vers la structure a utiliser pour le dessin
 */ 
void racket_draw( Racket* racket ){

	/* On met en pile la matrice telle qu'elle est au depart */
	glPushMatrix();
	
	/* Changement de repere pour positionner au bon endroit */
	glTranslated( racket->x , racket->y , racket->z );
	glRotated( 90 , 0 , 1 , 0);
	
	/* Choix de la couleur */
	glColor3ub( 255 , 0 , 0 );
	
	/* On alloue dynamiquement les parametres pour notre quadrique */
	GLUquadric* params = gluNewQuadric();
	
	/* Dessin de la raquette */
	gluCylinder( params , racket->radius , racket->radius  , racket->width , 20 , 1 );
	
	/* Libération des ressources car fin du dessin */
	gluDeleteQuadric( params );
	
	/* On remet la matrice de projection telle qu'elle était au départ */
	glPopMatrix();
	
}