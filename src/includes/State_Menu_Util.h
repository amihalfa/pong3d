#ifndef STATE_MENU_UTIL_H
#define STATE_MENU_UTIL_H
 
 /**
 * Fait bouger le curseur dans l'etat menu
 * @param env		Environnement du menu
 */
void smu_move_cursor(State_Menu_Env* env);

/**
 * Gestionnaire du curseur de souris
 * S'occupe des mouvement et du survol d'elements
 * @param env		Environnement du menu
 */
void smu_cursor_handler(State_Menu_Env* env);

/**
 * Actionne la sauvegarde de la config du menu config vers le fichier de config
 * @param env		Environnement du menu
 */
void smu_save_config_items(State_Menu_Env* env);

#endif
