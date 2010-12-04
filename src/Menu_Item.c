#include <GL/gl.h>
#include <GL/glu.h>
#include "includes/Menu_Item.h"

void menu_item_draw(Menu_Item * menu_item){

	/* On met en pile la matrice telle qu'elle est au depart */
	glPushMatrix();
	
	/* Changement de repere pour positionner au bon endroit */
	glTranslated( menu_item->x + menu_item->anim_step , menu_item->y , menu_item->z );
	
	glEnable (GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, menu_item->texture);
	
	/* Debut de dessin */
	glBegin( GL_QUADS );
	
		glColor3ub( 250 , 250 , 250 );
		
		/* Dessin face du bas */
		glNormal3f( 0.0f , 0.0f , -1.0f );
		glVertex3d( 0 , 0 , 0 );
		glVertex3d( menu_item->width , 0 , 0 );
		glVertex3d( menu_item->width , menu_item->length, 0 );
		glVertex3d( 0 , menu_item->length , 0 );
			
		/* Dessin face du haut */
		glNormal3f( 0.0f , 0.0f , 1.0f );
		glTexCoord2i(0,1);
		glVertex3d( 0 , 0 , menu_item->height );
		glTexCoord2i(1,1);
		glVertex3d( menu_item->width , 0 , menu_item->height );
		glTexCoord2i(1,0);
		glVertex3d( menu_item->width , menu_item->length, menu_item->height );
		glTexCoord2i(0,0);
		glVertex3d( 0 , menu_item->length , menu_item->height );
		
		/* Dessin de la face avant */
		glNormal3f( 0.0f , -1.0f , 0.0f );
		glVertex3d( 0 , 0 , 0 );
		glVertex3d( 0 , 0 , menu_item->height );
		glVertex3d( menu_item->width , 0 , menu_item->height );
		glVertex3d( menu_item->width , 0 , 0 );

		/* Dessin de la face arriere */
		glNormal3f( 0.0f , 1.0f , 0.0f );
		glVertex3d( 0 , menu_item->length , 0 );
		glVertex3d( 0 , menu_item->length , menu_item->height );
		glVertex3d( menu_item->width , menu_item->length , menu_item->height );
		glVertex3d( menu_item->width , menu_item->length , 0 );
		
		/* Dessin de la face gauche */
		glNormal3f( -1.0f , 0.0f , 0.0f );
		glVertex3d( 0 , 0 , 0 );
		glVertex3d( 0 , 0 , menu_item->height );
		glVertex3d( 0 , menu_item->length , menu_item->height );
		glVertex3d( 0 , menu_item->length , 0 );

		/* Dessin de la face droite */
		glNormal3f( 1.0f , 0.0f , 0.0f );
		glVertex3d( menu_item->width , 0 , 0 );
		glVertex3d( menu_item->width , 0 , menu_item->height );
		glVertex3d( menu_item->width , menu_item->length , menu_item->height );
		glVertex3d( menu_item->width , menu_item->length , 0 );
	
	glEnd();
	
	/* On remet la matrice mise en pile au depart */
	glPopMatrix();

}

void menu_item_animate(Menu_Item * menu_item, Uint32 e_time){
	
	float d_step = e_time / 300.0f * menu_item->anim_dir;
	
	if(menu_item->anim_step >= 1 || menu_item->anim_step <= -1){
		menu_item->anim_step = menu_item->anim_dir;
		menu_item->anim_dir *= -1;
		d_step *= -1;
	}
	menu_item->anim_step += d_step;
	
}

void menu_item_animate_to_0(Menu_Item * menu_item, Uint32 e_time){

	if( menu_item->anim_step != 0.0 ){

		if(menu_item->anim_step > -0.1 && menu_item->anim_step < 0.1 ){
			menu_item->anim_step = 0;
		} else {
			menu_item_animate(menu_item,e_time);
		}
	}
}
