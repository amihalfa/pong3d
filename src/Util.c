#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "includes/Coords.h"
#include "includes/Particles.h"
#include "includes/State.h"
#include "includes/Racket.h"
#include "includes/Ball.h"
#include "includes/Ground.h"
#include "includes/Config.h"
#include "includes/State_Game.h"
#include "includes/Menu_Item.h"
#include "includes/State_Menu.h"
#include "includes/Util.h"
#include "includes/Animation.h"

/**
 *	Fonction de chargement de la texture en memoire graphique
 */
GLuint util_texture_load(char * path) {

    GLuint texture_name;
    SDL_Surface * texture;

    glGenTextures(1, &texture_name);
    glBindTexture(GL_TEXTURE_2D, texture_name);

    texture = IMG_Load(path);

    if (!texture) {
        fprintf(stderr, "Erreur :: Impossible d'ouvrir le fichier '%s' \n", path);
        exit(10);
    }

    glTexImage2D(GL_TEXTURE_2D, 0, texture->format->BytesPerPixel, texture->w, texture->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture-> pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    SDL_FreeSurface(texture);

    return texture_name;

}

/**
 * Affichage d'une texture en position (x,y) avec les dimensions w x h
 * Utile pour le menu
 * @param	texture_id		Identifiant OpenGL de la texture a afficher
 * @param 	x				Position en x de l'endroit ou afficher
 * @param	y				Position en y de l'endroit ou afficher
 * @param	w				Largeur de l'affichage
 * @param	h				Hauteur de l'affichage
 */
void util_texture_display(GLuint texture_id, GLfloat x, GLfloat y, GLfloat w, GLfloat h) {

    /* Accepter la transparence sur les textures */
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    /* Active et applique la texture */
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    /* On met en pile la matrice telle qu'elle est au depart */
    glPushMatrix();

    /* Changement de repere pour positionner au bon endroit */
    glTranslated(x, y, 0);

    /* Dessin */
    glBegin(GL_QUADS);

    glColor4ub(255, 255, 255, 255);
    glTexCoord2i(0, 1);
    glVertex2f(0.0f, 0.0f);
    glTexCoord2i(0, 0);
    glVertex2f(0.0f, h);
    glTexCoord2i(1, 0);
    glVertex2f(w, h);
    glTexCoord2i(1, 1);
    glVertex2f(w, 0.0f);

    glEnd();

    /* On remet la matrice mise en pile au depart */
    glPopMatrix();

    /* On desactive texturing et transparence */
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
}

void util_reflection_ball(Ball* ball, Ground* ground) {

    glColorMask(0, 0, 0, 0);
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_ALWAYS, 1, 1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glDisable(GL_DEPTH_TEST);

    ground_draw(ground);

    glEnable(GL_DEPTH_TEST);

    glColorMask(1, 1, 1, 1);
    glStencilFunc(GL_EQUAL, 1, 1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

    glPushMatrix();
    glScalef(1.0f, 1.0f, -1.0f);
    glTranslatef(0.0f, 0.0f, 0.5f);
    ball_draw(ball);
    glPopMatrix();

    glDisable(GL_STENCIL_TEST);
}

void util_reflection_racket(Racket* racket, Ground* ground) {

    glColorMask(0, 0, 0, 0);
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_ALWAYS, 1, 1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glDisable(GL_DEPTH_TEST);

    ground_draw(ground);

    glEnable(GL_DEPTH_TEST);

    glColorMask(1, 1, 1, 1);
    glStencilFunc(GL_EQUAL, 1, 1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

    glPushMatrix();
    glScalef(1.0f, 1.0f, -1.0f);
    glTranslatef(0.0f, 0.0f, 0.5f);
    racket_draw(racket);
    glPopMatrix();

    glDisable(GL_STENCIL_TEST);
}

void util_reflection_particles(Particles* particles, Ground* ground) {

    glColorMask(0, 0, 0, 0);
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_ALWAYS, 1, 1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glDisable(GL_DEPTH_TEST);

    ground_draw(ground);

    glEnable(GL_DEPTH_TEST);

    glColorMask(1, 1, 1, 1);
    glStencilFunc(GL_EQUAL, 1, 1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

    glPushMatrix();
    glScalef(1.0f, 1.0f, -1.0f);
    glTranslatef(0.0f, 0.0f, 0.5f);
    particles_draw(particles);
    glPopMatrix();

    glDisable(GL_STENCIL_TEST);
}

