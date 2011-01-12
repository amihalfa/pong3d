#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "includes/State_Menu_OpenGL.h"

void smo_init(GLfloat width, GLfloat height) {

    /* On enleve les params de la 3D */
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glDisable(GL_COLOR_MATERIAL);

    /* On dimensionne le point de vue */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0f, width, 0.0f, height);

}

void smo_draw() {

    /* On s'assure que le dessin est termine */
    glFlush();

    /* On affiche */
    SDL_GL_SwapBuffers();

    /* On vide le buffer d'affichage */
    glClear(GL_COLOR_BUFFER_BIT);

    /* Matrice de manipulation des objets */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}