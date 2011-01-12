#include <SDL/SDL.h>
#include <GL/gl.h>
#include "includes/Coords.h"
#include "includes/Particles.h"
#include "includes/State.h"
#include "includes/Racket.h"
#include "includes/Ball.h"
#include "includes/Ground.h"
#include "includes/Config.h"
#include "includes/State_Game.h"

/**
 * Initialisation du dessin de particules
 * @param	particles	Structure designant un nuage de particules
 */
void particles_init_draw(Particles* particles) {

    /*glGenBuffers( 1, particles->buffer );
    glBindBuffer(GL_ARRAY_BUFFER, particles->buffer[0]);
    glBufferData(GL_ARRAY_BUFFER, 7*PARTICLES_NB*sizeof(GLfloat), &(particles->elements[0][0]), GL_DYNAMIC_DRAW);*/
}

/**
 * Initialisation de la position et de la couleur des particules
 * @param	particles	Structure designant un nuage de particules
 */
void particles_init(Particles* particles, Coord3d* position) {

    int i;
    for (i = 0; i < PARTICLES_NB; i++) {
        particles->elements[i][0] = 0.2f;
        particles->elements[i][1] = 0.2f;
        particles->elements[i][2] = 1.0f;
        particles->elements[i][3] = 1.0f;
        particles->elements[i][4] = position->x;
        particles->elements[i][5] = position->y;
        particles->elements[i][6] = position->z;
    }
    particles->cursor = 0;
}

/**
 * Dessin de particules
 * @param	particles	Structure designant un nuage de particules
 */
void particles_draw(Particles* particles) {

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);

    glVertexPointer(3, GL_FLOAT, 7 * sizeof (float), &(particles->elements[0][0]) + 4);
    glColorPointer(4, GL_FLOAT, 7 * sizeof (float), &(particles->elements[0][0]));

    glPointSize(1);
    glDrawArrays(GL_POINTS, 0, PARTICLES_NB);

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

}

void particles_add_position(Particles* particles, Coord3d* position) {

    int i;
    for (i = 0; i < PARTICLES_NB; i++) {
        particles->elements[i][3] -= PARTICLES_ALPHA_SUB;
    }

    for (i = 0; i < PARTICLES_PPP; i++) {
        particles->elements[particles->cursor][3] = 0.75f;
        particles->elements[particles->cursor][4] = position->x + 0.30 * ((float) (rand() % 200 - 100) / 100.0);
        particles->elements[particles->cursor][5] = position->y + 0.30 * ((float) (rand() % 200 - 100) / 100.0);
        particles->elements[particles->cursor][6] = position->z + 0.30 * ((float) (rand() % 200 - 100) / 100.0);
        particles->cursor++;
        if (particles->cursor >= PARTICLES_NB) {
            particles->cursor = particles->cursor % PARTICLES_NB;
        }
    }

}



