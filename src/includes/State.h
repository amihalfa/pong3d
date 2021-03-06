#ifndef STATE_H
#define STATE_H

#define STATE_CREATE	0
#define STATE_GET		1
#define STATE_DESTROY	2


/**
 * Structure de l'etat general
 */
typedef struct State {
    /**
     *	Environnement associe a l'etat en cours de l'application
     */
    void* env;

    /**
     *	Fonction d'initialisation de l'etat courant
     *	@param	env		Environnement attache a l'etat
     */
    void ( *init_handler)(void*);

    /**
     *	Fonction d'affichage de l'etat courant
     *	@param	env		Environnement attache a l'etat
     */
    void ( *main_handler)(void*, Uint32);

    /**
     *	Fonction de gestion des evenements de l'etat courant
     *	@param	env		Environnement attache a l'etat
     */
    int ( *events_handler)(void*);

} State;


/**
 *	Fonction permettant de retrouver l'etat courant de l'application
 *	@return 	Pointeur vers l'etat courant de l'application
 */
State* state_get_current();

/**
 *	Fonction permettant de retrouver l'etat courant de l'application
 *	@return 	Pointeur vers l'etat courant de l'application
 */
State* state_set_current(State*);

/**
 *	Gestionnaire d'evenements de l'etat courant
 */
int current_state_events();

/**
 * Appelle la focntion principale de l'etat courant
 */
void current_state_main(Uint32 e_time);

/**
 * Permet d'obtenir l'environement de l'etat courant
 * @return      L'environement
 */
void* current_state_env();

#endif

