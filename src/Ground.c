/**
 * Fonctions d'intervention sur le Terrain - Dessin OpenGL notamment
 * @author	Amirouche HALFAOUI
 */

#include <GL/gl.h>
#include <GL/glu.h>
#include "includes/Ground.h"

/**
 * Initialisation du dessin du terrain en OpenGL
 * On prepare les donnees a envoyer a la carte graphique
 * @param	ground	Pointeur vers la structure a utiliser designant le terrain
 */
void ground_init_draw ( Ground* ground ) {

    GLfloat l = ground->length / 2.0;
    GLfloat w = ground->width / 2.0;
    GLfloat h = ground->height;
	
	/* Coordonnees des points permettant de dessiner le terrain */
	GLfloat ground_array[48] = {
        -w, -l, 0.0f, -w, l, 0.0f,
        w, l, 0.0f, w, -l, 0.0f,
        w, -l, h, w, l, h,
        w+0.2f, l, h, w+0.2f, -l, h,
        w+0.2f, -l, -0.2f, w+0.2f, l, -0.2f,
        -w-0.2f, l, -0.2f, -w-0.2f, -l, -0.2f,
		-w-0.2f, -l, h, -w-0.2f, l, h,
		-w, l, h, -w, -l, h
    };
	
	/* Organisation des indices des points pour dessiner le terrain  */
    GLuint ground_i_array[32] = {
		0, 1, 2, 3,
		2,3,4,5,
		4,5,6,7,
		6,7,8,9,
		8,9,10,11,
		10,11,12,13,
		12,13,14,15,
		14,15,0,1
    };

	/* Generation des buffers pour stocker les 2 tableau en memoire graphique */
	glGenBuffers( 2, ground->buffer );
	
	/* On attache le buffer de points au tableau ci-dessus */
	glBindBuffer(GL_ARRAY_BUFFER, ground->buffer[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(ground_array), ground_array, GL_DYNAMIC_DRAW);
	
	/* Idem pour le tableau d'indices */
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ground->buffer[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ground_i_array), ground_i_array, GL_DYNAMIC_DRAW);
	
}

/**
 *	Dessin du terrain en OpenGL
 *	@param	ground		Pointeur vers la structure a utiliser pour le dessin
 */
void ground_draw ( Ground* ground ) {

	/* Couleur du terrain, gris transparent */
	glColor4f( 0.2f, 0.2f, 0.2f, 0.8f);
	
	/* On recupere les buffers pour le dessin du terrain */
    glBindBuffer(GL_ARRAY_BUFFER, ground->buffer[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ground->buffer[1]);
	
	/* Coordonnees sur 3 float non separes (consecutifs) */
	glVertexPointer( 3, GL_FLOAT, 3 * sizeof(GLfloat), (float*)0 );
	
	/* Activation de la transparence et des tableaux de vertices */
	glEnable(GL_BLEND);	
	glEnableClientState( GL_VERTEX_ARRAY );
	
	glDrawElements(GL_QUADS, 32, GL_UNSIGNED_INT, 0);
	
	/* Désactivation des options precedemment activees */
	glDisable(GL_BLEND);	
	glDisableClientState( GL_VERTEX_ARRAY );
}
