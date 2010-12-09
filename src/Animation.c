#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <time.h>
#include "includes/Coords.h"
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

void animation_particules( Ball* b ){
	
	int i,j;
	float alea;
	srand(time(NULL));
	for( i = 0 ; i < BALL_HISTO ; i++ ){
	
		/* On met la matrice actuelle dans la pile avant modif. */
		glPushMatrix();
		
		for( j = 0; j < 5; j++){
			
			alea = (float)(rand()%200)/100.0 - 1.0;
			
			glTranslatef( b->radius*alea , 0 , 0 );
			
			alea = (float)(rand()%360);
			glRotatef(alea, 1.0f , 0.0f , 0.0f );
			
			/* On change le repere */
			glTranslatef( b->pos_histo[i].x , b->pos_histo[i].y , b->pos_histo[i].z );
			
			/* On applique la couleur */
			glColor3ub( 10 , 10 , 200 );
			
			glBegin( GL_QUADS );
		
			/* Particule */
			glNormal3f( 0.0f , 0.0f , 1.0f );
			glTexCoord2i(0,1); glVertex3d( 0 , 0 , 0 );
			glTexCoord2i(1,1); glVertex3d( 0.2 , 0, 0 );
			glTexCoord2i(1,0); glVertex3d( 0.2 , 0.2 , 0 );
			glTexCoord2i(0,0); glVertex3d( 0 , 0.2 , 0 );
		
			glEnd();
		
		}
		
		/* On remet la matrice mise en pile au depart */
		glPopMatrix();
		
	}
}