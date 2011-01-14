#ifndef CONFIG_H
#define CONFIG_H

#define CONFIG_NB                   3

#define CONFIG_MOUSE_SENSIBILITY    0
#define CONFIG_REFLECTION           1
#define CONFIG_PARTICLES            2

/**
 *	Chargement de la configuration
 *	@param	config      Tableau qui contiendra la configuration lue dans le fichier
 */
int config_load(float* config);

/**
 *	Chargement de la configuration
 *	@param	game_env    L'environnment de jeux
 */
int config_load_state_game(void* game_env);

/**
 *	Chargement de la configuration
 *	@param	menu_env    L'environnment de menu
 */
int config_load_state_menu(void* menu_env);

/**
 *	Sauvegarde de la configuration
 *	@param	config      Tableau qui contient la configuration a sauvegarder
 */
int config_save_state_menu(int* config);

#endif
