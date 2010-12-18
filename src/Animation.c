#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <time.h>
#include "includes/Coords.h"
#include "includes/Particles.h"
#include "includes/State.h"
#include "includes/Ball.h"
#include "includes/Menu_Item.h"
#include "includes/State_Menu.h"
#include "includes/Animation.h"

void animation_state_menu(State_Menu_Env* env, Uint32 e_time){

	int i;
	
	/* On remet les elements du menu non selectionnes a 0 */
	for(i = 0; i < STATE_MENU_ITEMSNB; i++){
		if(i != env->selected_item ){
			menu_item_animate_to_0(&env->menu_item[i], e_time);
		}
	}
	
	/* On anime l'element selectionne */
	menu_item_animate(&env->menu_item[env->selected_item], e_time);
	
}

/**void animation_particules( Ball* b ){
	
	int i,j;
	float alea, x,y,z;
	for( i = 0 ; i < BALL_HISTO ; i++ ){
	
		/* On met la matrice actuelle dans la pile avant modif. *-/
		glPushMatrix();

	/*
	glTranslatef( b->pos_histo[i].x , b->pos_histo[i].y, b->pos_histo[i].z );
	glEnable(GL_BLEND);
	glColor4ub(10, 10, 255, i*3);					
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);	
	GLUquadric* params = gluNewQuadric();
	float size = b->radius * ((float)sqrt(i)/sqrt(BALL_HISTO));
	gluSphere( params , size , 10 , 10 );
	gluCylinder( params , size , size  , 1 , 20 , 1 );
	glDisable(GL_BLEND);
	gluDeleteQuadric(params);*-/
	
		for( j = 0; j < 10; j++){
			
			alea = b->radius/2.5* ((float)(rand()%2000)/1000.0 - 1.0);
			x = b->pos_histo[i].x + alea;
			alea = b->radius/2.5* ((float)(rand()%2000)/1000.0 - 1.0);
			y = b->pos_histo[i].y + alea;
			alea = b->radius/2.5* ((float)(rand()%2000)/1000.0 - 1.0);
			z = b->pos_histo[i].z + alea;
			
			glEnable(GL_BLEND);
			glColor4ub(0, 0, 255, i*2);					
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			
			glBegin( GL_QUADS );
	
			/* Particule *-/
			glNormal3f( 0.0f , 0.0f , 1.0f );
			glTexCoord2i(0,1); glVertex3d( x - 0.1 , y - 0.1 , z + 0.1 );
			glTexCoord2i(1,1); glVertex3d( x + 0.1, y - 0.1 , z + 0.1 );
			glTexCoord2i(1,0); glVertex3d( x + 0.4 , y + 0.1 , z + 0.1 );
			glTexCoord2i(0,0); glVertex3d( x - 0.1 , y + 0.1 , z + 0.1 );
		
			glEnd();
			glDisable(GL_BLEND);
		}
		
		/* On remet la matrice mise en pile au depart *-/
		glPopMatrix();
		
	}
}*/