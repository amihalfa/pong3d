#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "includes/Config.h"
#include "includes/Coords.h"
#include "includes/Particles.h"
#include "includes/State.h"
#include "includes/Ground.h"
#include "includes/Racket.h"
#include "includes/Ball.h"
#include "includes/State_Game.h"
#include "includes/Util.h"


void ball_draw(Ball* ball) {

	GLUquadric* params;
	
    /* On met la matrice actuelle dans la pile avant modif. */
    glPushMatrix();

    /* On change le repere */
    glTranslatef(ball->position.x, ball->position.y, ball->position.z);

    /* On applique la couleur */
    glColor3f(0.04f, 0.04f, 0.9f);

    /* On alloue dynamiquement les parametres pour notre quadrique */
    params = gluNewQuadric();

    /* On dessine la balle */
    gluSphere(params, ball->radius, 10, 10);

    /* Liberation des ressources car fin du dessin */
    gluDeleteQuadric(params);

    /* On remet la matrice mise en pile au depart */
    glPopMatrix();


}


void ball_move(Ball* ball, Uint32 e_time) {

    /* Nouvelle position */
    ball->position.x += ball->speed.x + (ball->speed.x / 10) * e_time;
    ball->position.y += ball->speed.y + (ball->speed.y / 10) * e_time;
}
