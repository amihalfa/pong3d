#ifndef MENU_ITEM_H
#define MENU_ITEM_H

	struct Menu_Item {

		/* Position */
		float x;
		float y;
		float z;
		
		/* Dimensions */
		float height;
		float length;
		float width;
		
		/* Id de l'image affichee dessus */
		GLuint texture;
		
		float anim_step;
		int anim_dir;

	};

	typedef struct Menu_Item Menu_Item;

	/**
	 *	Dessin d'un item de menu
	 *	@param menu_item	Reference vers l'item a dessinner	
	 */
	void menu_item_draw(Menu_Item * menu_item);
	
	void menu_item_animate(Menu_Item* menu_item, Uint32 e_time);
	
	void menu_item_animate_to_0(Menu_Item * menu_item, Uint32 e_time);

#endif
