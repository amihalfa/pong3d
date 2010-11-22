#include <GL/gl.h>
#include <GL/glu.h>
#include "includes/Ground.h"

/**
 *	Dessin du terrain en OpenGL
 *	@param	ground		Pointeur vers la structure a utiliser pour le dessin
 */
void ground_draw( Ground* ground ){
	
	int i , j;
	float length_mi , width_mi;
	float text_i=0, text_j=0;
	
	/* Pour centrer le terrain, on divise les tailles par 2 */
	length_mi = ground->length / 2;
	width_mi = ground->width / 2;
	
	glEnable (GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	glBindTexture(GL_TEXTURE_2D, ground->texture);
	
	/* Début de dessin */
	glBegin( GL_QUADS );
	
	/* Couleur generale */
	glColor3ub( 255 , 255 , 255 );
	
	/* Bas du terrain (visible) */
	glNormal3f( 0.0f , 0.0f , 1.0f );
	glTexCoord2i(0,1); glVertex3d( -width_mi , -length_mi , 0 );
	glTexCoord2i(1,1); glVertex3d( width_mi , -length_mi, 0 );
	glTexCoord2i(1,0); glVertex3d( width_mi , length_mi , 0 );
	glTexCoord2i(0,0); glVertex3d( -width_mi , length_mi , 0 );
	
	/* Bas du terrain (non visible) */
	glNormal3f( 0.0f , 0.0f , -1.0f );
	glTexCoord2i(0,1); glVertex3d( -width_mi - 0.5 , -length_mi , -1.0 );
	glTexCoord2i(1,1); glVertex3d( width_mi + 0.5 , -length_mi, -1.0 );
	glTexCoord2i(1,0); glVertex3d( width_mi + 0.5 , length_mi , -1.0 );
	glTexCoord2i(0,0); glVertex3d( -width_mi - 0.5 , length_mi , -1.0 );
	
	
	/* Dessin de la face arriere 
	glNormal3f( 0.0f , -1.0f , 0.0f );
	for(i = -width_mi; i < width_mi; i++){
		glVertex3d( i+1 , length_mi , 0 );
		glVertex3d( i+1 , length_mi , ground->height );
		glVertex3d( i, length_mi , ground->height );
		glVertex3d( i , length_mi , 0 );
	}
		
	/* Dessin de la face avant 
	glNormal3f( 0.0f , 1.0f , 0.0f );
	for(i = -width_mi; i < width_mi; i++){
		glVertex3d( i+1 , -length_mi , 0 );
		glVertex3d( i+1 , -length_mi , ground->height );
		glVertex3d( i , -length_mi , ground->height );
		glVertex3d( i , -length_mi , 0 );
	}
	
	/* Dessin de la face gauche interieure */
	glNormal3f( 1.0f , 0.0f , 0.0f );
	glTexCoord2i(0,1); glVertex3d( -width_mi , length_mi , 0 );
	glTexCoord2i(1,1); glVertex3d( -width_mi , length_mi , ground->height );
	glTexCoord2i(1,0); glVertex3d( -width_mi , -length_mi , ground->height );
	glTexCoord2i(0,0); glVertex3d( -width_mi , -length_mi , 0 );
	
	/* Dessin de la face gauche exterieure */
	glNormal3f( -1.0f , 0.0f , 0.0f );
	glVertex3d( -width_mi - 0.5 , length_mi , -1.0 );
	glVertex3d( -width_mi - 0.5 , length_mi , ground->height );
	glVertex3d( -width_mi - 0.5 , -length_mi , ground->height );
	glVertex3d( -width_mi - 0.5 , -length_mi , -1.0 );
	
	
	/* Dessin de la face droite interieure */
	glNormal3f( -1.0f , 0.0f , 0.0f );
	glTexCoord2i(0,1); glVertex3d( width_mi , length_mi , 0 );
	glTexCoord2i(1,1); glVertex3d( width_mi , length_mi , ground->height );
	glTexCoord2i(1,0); glVertex3d( width_mi , -length_mi , ground->height );
	glTexCoord2i(0,0); glVertex3d( width_mi , -length_mi , 0 );
	
	/* Dessin de la face droite exterieure */
	glNormal3f( 1.0f , 0.0f , 0.0f );
	glTexCoord2i(0,1); glVertex3d( width_mi + 0.5 , length_mi , -1.0 );
	glTexCoord2i(1,1); glVertex3d( width_mi + 0.5 , length_mi , ground->height );
	glTexCoord2i(1,0); glVertex3d( width_mi + 0.5 , -length_mi , ground->height );
	glTexCoord2i(0,0); glVertex3d( width_mi + 0.5 , -length_mi , -1.0 );
	
	/* Haut du terrain gauche */
	glNormal3f( 0.0f , 0.0f , 1.0f );
	glTexCoord2i(0,1); glVertex3d( -width_mi - 0.5 , -length_mi , ground->height );
	glTexCoord2i(1,1); glVertex3d( -width_mi , -length_mi, ground->height );
	glTexCoord2i(1,0); glVertex3d( -width_mi , length_mi , ground->height );
	glTexCoord2i(0,0); glVertex3d( -width_mi - 0.5 , length_mi , ground->height );
	
	/* Haut du terrain a droite */
	glNormal3f( 0.0f , 0.0f , 1.0f );
	glTexCoord2i(0,1); glVertex3d( width_mi , -length_mi , ground->height );
	glTexCoord2i(1,1); glVertex3d( width_mi + 0.5 , -length_mi, ground->height );
	glTexCoord2i(1,0); glVertex3d( width_mi + 0.5 , length_mi , ground->height );
	glTexCoord2i(0,0); glVertex3d( width_mi , length_mi , ground->height );
	
	
	glEnd();
	glDisable (GL_TEXTURE_2D);
}
