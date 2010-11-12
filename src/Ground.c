#include <stdio.h>
#include "includes/Ground.h"
#include <GL/gl.h>
#include <GL/glu.h>

/**
 *	Dessin du terrain en OpenGL
 *	@param	ground		Pointeur vers la structure a utiliser pour le dessin
 */
void ground_draw( Ground* ground ){
	
	int i , j;
	float length_mi , width_mi;
	
	/* Pour centrer le terrain, on divise les tailles par 2 */
	length_mi = ground->length / 2;
	width_mi = ground->width / 2;
	
	/* Début de dessin */
	glBegin( GL_QUADS );
	
	/* Couleur pour le sol */
	glColor3ub( 210 , 200 , 200 );
	
	glNormal3f( 0.0f , 0.0f , 1.0f );
	
	/* Dessin du sol */
	for(i = -width_mi; i < width_mi; i+=1){
		for(j = -length_mi; j < length_mi; j+=1){
			glVertex3d( i , j , 0 );
			glVertex3d( i+1 , j, 0 );
			glVertex3d( i+1 , j+1, 0 );
			glVertex3d( i , j+1 , 0 );
		}
	}
	
	/* Couleur des faces */
	glColor3ub( 150 , 100 , 100 );
	
	/* Dessin de la face arriere */
	glNormal3f( 0.0f , -1.0f , 0.0f );
	for(i = -width_mi; i < width_mi; i++){
		glVertex3d( i+1 , length_mi , 0 );
		glVertex3d( i+1 , length_mi , ground->height );
		glVertex3d( i, length_mi , ground->height );
		glVertex3d( i , length_mi , 0 );
	}
		
	/* Dessin de la face avant */
	glNormal3f( 0.0f , 1.0f , 0.0f );
	glVertex3d( width_mi , -length_mi , 0 );
	glVertex3d( width_mi , -length_mi , ground->height );
	glVertex3d( -width_mi , -length_mi , ground->height );
	glVertex3d( -width_mi , -length_mi , 0 );
	
	/* Dessin de la face droite */
	glNormal3f( -1.0f , 0.0f , 0.0f );
	glVertex3d( -width_mi , length_mi , 0 );
	glVertex3d( -width_mi , length_mi , ground->height );
	glVertex3d( -width_mi , -length_mi , ground->height );
	glVertex3d( -width_mi , -length_mi , 0 );
	
	/* Dessin de la face gauche */
	glNormal3f( 1.0f , 0.0f , 0.0f );
	glVertex3d( width_mi , length_mi , 0 );
	glVertex3d( width_mi , length_mi , ground->height );
	glVertex3d( width_mi , -length_mi , ground->height );
	glVertex3d( width_mi , -length_mi , 0 );
	
	glEnd();
	
}