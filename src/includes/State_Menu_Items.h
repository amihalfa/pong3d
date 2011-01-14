#ifndef STATE_MENU_IETMS_H
#define STATE_MENU_IETMS_H

/**
 * Initialise les items du menu
 * @param env       L'environement de menu
 */
void smi_init(State_Menu_Env* env);

/**
 * Initialise les textures des items du menu
 * @param env       L'environement de menu
 */
void smi_init_textures(State_Menu_Env* env);

/**
 * Initialise les items du menu
 * @param env       L'environement de menu
 */
int smi_select(State_Menu_Env* env);

/**
 * Change les checkbox et slider selon la config
 * @param env       L'environement de menu
 */
void smi_select_config(State_Menu_Env* env);

#endif
