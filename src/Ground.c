/**
 * Fonctions d'intervention sur le Terrain - Dessin OpenGL notamment
 * @author	Amirouche HALFAOUI
 */

#include <GL/gl.h>
#include <GL/glu.h>
#include "includes/Ground.h"

/**
 *	Dessin du terrain en OpenGL
 *	@param	ground		Pointeur vers la structure a utiliser pour le dessin
 */
void ground_draw(Ground* ground) {

    GLfloat l = ground->length / 2.0;
    GLfloat w = ground->width / 2.0;
    GLfloat h = ground->height;

    /* Coordonnees des points permettant de dessiner le terrain */
    GLfloat ground_array[] = {
        -w, -l, 0.0f, 0.15f, 0.15f, 0.15f, 0.9f,
        -w, l, 0.0f, 0.05f, 0.05f, 0.05f, 0.9f,
        w, l, 0.0f, 0.15f, 0.15f, 0.15f, 0.9f,
        w, -l, 0.0f, 0.05f, 0.05f, 0.05f, 0.9f,
        w, -l, h, 0.15f, 0.15f, 0.15f, 1.0f,
        w, l, h, 0.02f, 0.02f, 0.02f, 1.0f,
        w + 0.2f, l, h, 1.0f, 0.1f, 0.1f, 1.0f,
        w + 0.2f, -l, h, 1.0f, 0.1f, 0.1f, 1.0f,
        w + 0.2f, -l, -0.2f, 1.0f, 0.1f, 0.1f, 1.0f,
        w + 0.2f, l, -0.2f, 1.0f, 0.1f, 0.1f, 1.0f,
        -w - 0.2f, l, -0.2f, 1.0f, 0.1f, 0.1f, 1.0f,
        -w - 0.2f, -l, -0.2f, 1.0f, 0.1f, 0.1f, 1.0f,
        -w - 0.2f, -l, h, 1.0f, 0.1f, 0.1f, 1.0f,
        -w - 0.2f, l, h, 1.0f, 0.1f, 0.1f, 1.0f,
        -w, l, h, 0.15f, 0.15f, 0.15f, 1.0f,
        -w, -l, h, 0.05f, 0.05f, 0.05f, 1.0f
    };


    /* Organisation des indices des points pour dessiner le terrain  */
    GLuint ground_i_array[32] = {
        0, 1, 2, 3,
        2, 3, 4, 5,
        4, 5, 6, 7,
        6, 7, 8, 9,
        8, 9, 10, 11,
        10, 11, 12, 13,
        12, 13, 14, 15,
        14, 15, 0, 1
    };

    /* Activation des tableaux de vertices */
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnable(GL_BLEND);

    /* Coordonnees sur 3 floats separes */
    glVertexPointer(3, GL_FLOAT, 7 * sizeof (GLfloat), ground_array);
    glColorPointer(4, GL_FLOAT, 7 * sizeof (GLfloat), ground_array + 3);

    /* Lancement du dessin */
    glDrawElements(GL_QUADS, 32, GL_UNSIGNED_INT, ground_i_array);

    /* Désactivation des options precedemment activees */
    glDisable(GL_BLEND);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

}
