#ifndef STATE_MENU_IETMS_H
#define STATE_MENU_IETMS_H

/**
 * Initialise les items du menu
 * @param env       L'environement de menu
 */
void smi_init(void* env);

/**
 * Initialise les textures des items du menu
 * @param env       L'environement de menu
 */
void smi_init_textures(void* env);

/**
 * Initialise les items du menu
 * @param env       L'environement de menu
 */
int smi_select(void* env);

/**
 * Change les checkbox et slider selon la config
 * @param env       L'environement de menu
 */
void smi_select_config(void* env);

#endif
