#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include "includes/Coords.h"
#include "includes/Menu_Item.h"

void menu_item_draw(Menu_Item * menu_item){

	/* Accepter la transparence sur les textures */
	glEnable(GL_BLEND);    
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	/* Active et applique la texture */
	glEnable (GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, menu_item->texture);
	
	/* On met en pile la matrice telle qu'elle est au depart */
	glPushMatrix();
	
	/* Changement de repere pour positionner au bon endroit */
	glTranslated( menu_item->position.x + menu_item->anim_step , menu_item->position.y , 0 );
	
	/* Debut de dessin */
	glBegin( GL_QUADS );
	
		glColor4ub(255, 255, 255, 255);
		glTexCoord2i(0,1);
		glVertex2f(0.0f, 0.0f);
		glTexCoord2i(0,0);
		glVertex2f(0.0f, 100.0f);
		glTexCoord2i(1,0);
		glVertex2f(400.0f, 100.0f);
		glTexCoord2i(1,1);
		glVertex2f(400.0f, 0.0f);
	
	glEnd();
	
	/* On remet la matrice mise en pile au depart */
	glPopMatrix();
	
	/* On desactive texturing et transparence */
	glDisable (GL_TEXTURE_2D);
	glDisable(GL_BLEND);

}

void menu_item_animate(Menu_Item * menu_item, Uint32 e_time){
	
	float d_step = e_time / 50.0f * menu_item->anim_dir;
	
	if(menu_item->anim_step >= 5.0 || menu_item->anim_step <= -5.0){
		menu_item->anim_step = menu_item->anim_dir * 5.0;
		menu_item->anim_dir *= -1;
		d_step *= -1;
	}
	menu_item->anim_step += d_step;
	
}

void menu_item_animate_to_0(Menu_Item * menu_item, Uint32 e_time){

	if( menu_item->anim_step != 0.0 ){

		if(menu_item->anim_step > -1.0 && menu_item->anim_step < 1.0 ){
			menu_item->anim_step = 0.0f;
		} else {
			menu_item_animate(menu_item,e_time);
		}
	}
}
