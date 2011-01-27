#ifndef STATE_MENU
#define	STATE_MENU

/** Nombre d'elements du menu */
#define STATE_MENU_ITEMSNB_MAX	5

/** Nombre de pages du menu */
#define STATE_MENU_PAGES		4

/** Page ACCUEIL */
#define STATE_MENU_HOME			0

/** Page CONTINUER */
#define STATE_MENU_CONTINUE		1

/** Page NIVEAUX */
#define STATE_MENU_PLAY			2

/** Page REGLAGES */
#define STATE_MENU_CONFIG		3

/**
 *	Environnement pour l'etat menu
 */
typedef struct State_Menu_Env {
    /** Tableau des elements du menu */
    Menu_Item menu_item[STATE_MENU_PAGES][STATE_MENU_ITEMSNB_MAX];

    /** Nombre d'elements des pages, home, reprendre, reglages */
    int itemsnb[STATE_MENU_PAGES];

    /** Page du menu selectionnee */
    int selected_page;

    /** Element du menu selectionne */
    int selected_item;

    /** Temps de latence */
    Uint32 ellapsed_time;

    /** Identifiant de la texture de logo */
    GLuint logo_texture;

    /** Identifiant de la texture du haut */
    GLuint top_texture;

    /** Identidiant de la texture pied de page */
    GLuint footer_texture;

    /** Identidiant de la texture du bas */
    GLuint bottom_texture;

    /** Largeur/Hauteur de fenetre utilisee */
    GLfloat w_width, w_height;

    /** Position de la souris */
    Coord2d mouse;

    /** Mouvement de la souris */
    Coord2d mouse_motion;

    /** Identidiant de la texture représentant le curseur */
    GLuint mouse_texture;

    /** Tableau contenant la configuration */
    int config[CONFIG_NB];

} State_Menu_Env;

/**
 *	Fonction generique permettant d'instancier le singleton etat_menu
 *	@param	flag	Drapeau pour savoir si on cree, on recupere ou on detruit l'etat
 *	@return 		Pointeur vers l'etat de menu
 */
struct State* state_menu(int flag);

/**
 *	Fonction permettant d'instancier l'etat menu
 */
void state_menu_create();

/**
 *	Recuperation du pointeur vers l'etat menu
 *	@return			Pointeur vers l'instance de l'etat menu en cours
 */
struct State* state_get_menu();

/**
 *	Destruction de l'etat menu
 */
void state_menu_destroy();

/**
 * Fonction maitresse de l'etat menu, appelee a chaque tour de boucle,
 * elle s'occupe de coordonner moteur physique et moteur graphique
 * @param env		Environnement de menu
 * @param e_time	Temps de latence donne par la boucle principale
 */
void state_menu_main(void* env, Uint32 e_time);

/**
 *	Initialisation de l'etat menu
 *	@param	env		Environnement du menu
 */
void state_menu_init(void* env);

/**
 * Affichage de l'etat menu
 * @param env		Environement du menu
 */
void state_menu_draw(void* env);

/**
 *	Gestionnaire des evenements de l'etat menu
 * @param env		Environnement du menu
 * @return			0 pour quitter l'appli et 1 sinon
 */
int state_menu_events(void* env);

#endif
