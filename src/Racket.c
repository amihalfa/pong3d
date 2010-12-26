#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "includes/Coords.h"
#include "includes/Particles.h"
#include "includes/State.h"
#include "includes/Racket.h"
#include "includes/Ground.h"
#include "includes/Ball.h"
#include "includes/Config.h"
#include "includes/State_Game.h"

/**
 *	Dessin de la raquette en OpenGL
 *	@param	racket		Pointeur vers la structure a utiliser pour le dessin
 */ 
void racket_draw( Racket* racket ){
	
	GLdouble eqn[4] = {-1.0, 0.0, 0.0, 0.0};
		
	/* On met en pile la matrice telle qu'elle est au depart */
	glPushMatrix();
	
	/* Changement de repere pour positionner au bon endroit */
	glTranslatef( racket->position.x - racket->width / 2 + racket->radius , racket->position.y , racket->position.z );
	
	/* Choix de la couleur */
	glColor3ub( 255 , 0 , 0 );
	
	glEnable (GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, racket->texture);

	glClipPlane (GL_CLIP_PLANE0, eqn); 
	glEnable (GL_CLIP_PLANE0);
	
	/* On alloue dynamiquement les parametres pour notre quadrique */
	GLUquadric* params = gluNewQuadric();
	
	gluQuadricDrawStyle(params,GLU_FILL);
	gluQuadricTexture(params,GL_TRUE);
	
	/* On dessine la gauche */
	gluSphere( params , racket->radius , 15 , 15 );
	
 	glDisable (GL_CLIP_PLANE0); 
	
	glRotatef( 90 , 0 , 1 , 0);
	
	/* Dessin de la raquette */
	gluCylinder( params , racket->radius , racket->radius  , racket->width - 2 * racket->radius , 20 , 1 );
	
	glRotatef( -90 , 0 , 1 , 0);
	
	glTranslatef( racket->width - 2 * racket->radius , 0 , 0 );
	
	eqn[0] = 1.0;
	glClipPlane (GL_CLIP_PLANE0, eqn); 
	glEnable (GL_CLIP_PLANE0);
	
	gluSphere( params , racket->radius , 10 , 10 );
	
	glDisable (GL_CLIP_PLANE0); 
	
	/* Liberation des ressources car fin du dessin */
	gluDeleteQuadric( params );
	
	glDisable (GL_TEXTURE_2D);
	
	/* On remet la matrice de projection telle qu'elle etait au depart */
	glPopMatrix();
	
}

void racket_move(void* v_env, char num_racket ){

	State_Game_Env* env = (State_Game_Env*) v_env;

	Racket* racket;
	if ( num_racket == RACKET_BOTTOM){
		racket = &env->racket[RACKET_BOTTOM];
	} else if ( num_racket == RACKET_TOP ){
		racket = &env->racket[RACKET_TOP];
	}

	float rckt_width_mi = racket->width / 2;
	float grnd_width_mi = env->ground.width / 2;

	
	if ( env->mouse_motion_x != 0 ){
		racket->speed = RACKET_SPEED * env->ellapsed_time * env->mouse_motion_x * env->config[CONFIG_MOUSE_SENSIBILITY];
	}
	/*else if ( env->keystates[SDLK_RIGHT] ){
		racket->speed = RACKET_SPEED * env->ellapsed_time;
	}
	else if ( env->keystates[SDLK_LEFT] ){
		racket->speed = - RACKET_SPEED * env->ellapsed_time;
	}*/
	else{
		racket->speed = 0;
	}

	racket->position.x += racket->speed;

	if (racket->position.x < -grnd_width_mi + rckt_width_mi)
		racket->position.x = -grnd_width_mi + rckt_width_mi;
	else if (racket->position.x > grnd_width_mi - rckt_width_mi)
		racket->position.x = grnd_width_mi - rckt_width_mi;
}
