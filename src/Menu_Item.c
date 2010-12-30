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
	glTranslated( menu_item->position.x, menu_item->position.y , 0 );
	
	glColor4f(1.0f, 1.0f, 1.0f, 0.10f + menu_item->anim_step);
	
	/* Debut de dessin */
	glBegin( GL_QUADS );
		glTexCoord2i(0,1);
		glVertex2f(0.0f, -128.0f);
		glTexCoord2i(0,0);
		glVertex2f(0.0f, 128.0f);
		glTexCoord2i(1,0);
		glVertex2f(128.0f, 128.0f);
		glTexCoord2i(1,1);
		glVertex2f(128.0f, -128.0f);
	glEnd();
	
	glDisable (GL_TEXTURE_2D);
	
	if(menu_item->type == MENU_ITEM_CHECKBOX){	
		menu_item_draw_checkbox(menu_item);
	}
	
	/* On remet la matrice mise en pile au depart */
	glPopMatrix();
	
	/* On desactive texturing et transparence */
	glDisable(GL_BLEND);

}

void menu_item_draw_checkbox(Menu_Item* menu_item){
	/* Debut de dessin */
		glBegin( GL_QUADS );
			glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
			glVertex2f(96.0f, 28.0f);
			glVertex2f(96.0, 60.0f);
			glVertex2f(128.0f, 60.0f);
			glVertex2f(128.0f, 28.0f);
			
			glColor4f(1.0f, 1.0f, 1.0f, 0.10f + menu_item->anim_step);
			glVertex2f(97.0f, 29.0f);
			glVertex2f(97.0, 59.0f);
			glVertex2f(127.0f, 59.0f);
			glVertex2f(127.0f, 29.0f);
			
			glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
			glVertex2f(101.0f, 33.0f);
			glVertex2f(101.0, 55.0f);
			glVertex2f(123.0f, 55.0f);
			glVertex2f(123.0f, 33.0f);
			
		glEnd();
}

void menu_item_animate(Menu_Item * menu_item, Uint32 e_time){
	
	float d_step = e_time / 800.0f * menu_item->anim_dir;
	
	if(menu_item->anim_step >= 0.80 || menu_item->anim_step <= 0.0){
		menu_item->anim_step = 0.40*menu_item->anim_dir+0.40;
		menu_item->anim_dir *= -1;
		d_step *= -1;
	}
	menu_item->anim_step += d_step;
	
}

void menu_item_animate_to_0(Menu_Item * menu_item, Uint32 e_time){

	if( menu_item->anim_step >= 0.0 ){

		if(menu_item->anim_step <= 0.01){
			menu_item->anim_step = 0.0f;
		} else {
			menu_item->anim_step -= e_time / 200.0f;
		}
	}
}

int menu_item_mouse_over(Menu_Item* menu_item, Coord2d* mouse){
	
	/* Si la souris est sur l'item en x */
	if(mouse->x > menu_item->position.x && mouse->x < menu_item->position.x + 128.0f){
		/* Si la souris est sur l'item en y */
		if(mouse->y > menu_item->position.y && mouse->y < menu_item->position.y + 128.0f){
			return 1;
		}
	}
	return 0;
}
