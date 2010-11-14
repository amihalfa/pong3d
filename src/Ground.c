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
	glBindTexture(GL_TEXTURE_2D, ground->texture);
	
	/* Début de dessin */
	glBegin( GL_QUADS );
	
	/* Couleur pour le sol */
	glColor3ub( 255 , 255 , 255 );
	
	glNormal3f( 0.0f , 0.0f , 1.0f );
	
	glTexCoord2i(0,1);
	glVertex3d( -width_mi , -length_mi , 0 );
	
	glTexCoord2i(1,1);
	glVertex3d( width_mi , -length_mi, 0 );
	
	glTexCoord2i(1,0);
	glVertex3d( width_mi , length_mi , 0 );
	
	glTexCoord2i(0,0);
	glVertex3d( -width_mi , length_mi , 0 );
	
	
	/* Dessin du sol 
	for(i = -width_mi; i < width_mi; i+=1){
		for(j = -length_mi; j < length_mi; j+=1){
			glTexCoord2i(i,j+1);
			glVertex3d( i , j , 0 );
			
			glTexCoord2i(i+1,j+1);
			glVertex3d( i+1 , j, 0 );
			
			glTexCoord2i(i+1,j);
			glVertex3d( i+1 , j+1, 0 );
			
			glTexCoord2i(i,j);
			glVertex3d( i , j+1 , 0 );
		}
	}
	
	/* Couleur des faces */
	glColor3ub( 155 , 155 , 155 );
	
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
	/* Dessin de la face gauche */
	glNormal3f( 1.0f , 0.0f , 0.0f );
	for(i = -length_mi; i < length_mi; i++){
		glVertex3d( -width_mi , i+1 , 0 );
		glVertex3d( -width_mi , i+1 , ground->height );
		glVertex3d( -width_mi , i , ground->height );
		glVertex3d( -width_mi , i , 0 );
	}
	
	/* Dessin de la face droite */
	glNormal3f( -1.0f , 0.0f , 0.0f );
	for(i = -length_mi; i < length_mi; i++){
		glVertex3d( width_mi , i+1 , 0 );
		glVertex3d( width_mi , i+1 , ground->height );
		glVertex3d( width_mi , i , ground->height );
		glVertex3d( width_mi , i , 0 );
	}
	glEnd();
	glDisable (GL_TEXTURE_2D);
}