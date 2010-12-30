#ifndef MENU_ITEM_H
#define MENU_ITEM_H

#define MENU_ITEM_DEFAULT	0
#define MENU_ITEM_CHECKBOX	1
#define MENU_ITEM_SLIDER	2

	typedef struct Menu_Item {

		/* Position */
		Coord2d position;
		
		/* Id de l'image affichee dessus */
		GLuint texture;
		
		GLfloat anim_step;
		
		int anim_dir;
		
		int type;
		
		int value;

	} Menu_Item;

	/**
	 *	Dessin d'un item de menu
	 *	@param menu_item	Reference vers l'item a dessinner	
	 */
	void menu_item_draw(Menu_Item * menu_item);
	
	void menu_item_draw_checkbox(Menu_Item* menu_item);
	
	void menu_item_animate(Menu_Item* menu_item, Uint32 e_time);
	
	void menu_item_animate_to_0(Menu_Item * menu_item, Uint32 e_time);
	
	int menu_item_mouse_over(Menu_Item* menu_item, Coord2d* mouse);

#endif
