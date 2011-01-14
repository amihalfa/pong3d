#ifndef MENU_ITEM_H
#define MENU_ITEM_H

#define MENU_ITEM_DEFAULT	0
#define MENU_ITEM_CHECKBOX	1
#define MENU_ITEM_SLIDER	2

#define MENU_ITEM_ALPHA_MIN		0.5f

/**
 * Structure d'un item de menu
 */
typedef struct Menu_Item {
    /** Position */
    Coord2d position;

    /** Id de l'image affichee dessus */
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

/**
 *	Dessin de la checkbox d'un item de menu (dans la configuration)
 *	@param menu_item	Reference vers l'item a dessinner
 */
void menu_item_draw_checkbox(Menu_Item* menu_item);

/**
 *	Dessin du slider d'un item de menu (dans la configuration pour la souris)
 *	@param menu_item	Reference vers l'item a dessinner
 */
void menu_item_draw_slider(Menu_Item* menu_item);

/**
 *	Animation d'un item de menu
 *	@param menu_item	Reference vers l'item a annimer
 */
void menu_item_animate(Menu_Item* menu_item, Uint32 e_time);

/**
 *	Remise a la normale d'un item de menu
 *	@param menu_item	Reference vers l'item a normaliser
 */
void menu_item_animate_to_0(Menu_Item * menu_item, Uint32 e_time);

/**
 * Teste si la souris survole un item de menu
 * @param menu_item	    L'item a tester
 * @param mouse         Les coordonnées de la souris
 * @return              0 si la souris ne survole pas, un entier sinon
 */
int menu_item_mouse_over(Menu_Item* menu_item, Coord2d* mouse);

#endif
