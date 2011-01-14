#ifndef PARTICLES_H
#define PARTICLES_H

#define PARTICLES_NB			2500
#define PARTICLES_PPP			50
#define PARTICLES_ALPHA_SUB		0.02	/* PARTICLES_PPP / PARTICLES_NB */

/**
 * Structure representant un nuage de particules
 */
typedef struct Particles {
    /** Ensemble de particules */
    GLfloat elements[PARTICLES_NB][7];

    /** Curseur indiquant la prochaine particule a effacer */
    int cursor;

} Particles;

/**
 * Initialisation du dessin de particules
 * @param	particles	Structure designant un nuage de particules
 */
void particles_init_draw(Particles* particles);

/**
 * Initialisation de la position et de la couleur des particules
 * @param	particles	Structure designant un nuage de particules
 */
void particles_init(Particles* particles, Coord3d* position);

/**
 * Dessin de particules
 * @param	particles	Structure designant un nuage de particules
 */
void particles_draw(Particles* particles);

/**
 * Ajoute des particule a une position
 * @param particles	    Structure designant un nuage de particules
 * @param position      La position cible
 */
void particles_add_position(Particles* particles, Coord3d* position);

#endif
