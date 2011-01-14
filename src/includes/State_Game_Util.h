#ifndef STATE_MENU_UTIL_H
#define STATE_MENU_UTIL_H

/**
 * Contient l'etat de pause courant
 * @param pause     le nouvel etat ou -1 pour obtenir l'etat courant
 * @return          l'etat courant
 */
int sgu_pause(int pause);

/**
 * Recupere l'etat de pause courant
 * @return          l'etat courant
 */
int sgu_get_pause();

/**
 * Change l'etat de pause courant
 * @param pause     0 pour tout détruire, 1 pour mettre en pause  et 2 pour jouer normalemnt
 */
void sgu_set_pause(int pause);

/**
 * Contient le numero du niveau courant courant
 * @param level     le nouveau niveau ou -1 pour obtenir le numero du niveau courant
 * @return          le numero du niveau courant
 */

int sgu_level(int level);
/**
 * Contient l'etat de pause courant
 * @return          le numero du niveau courant
 */

int sgu_get_level();
/**
 * Contient l'etat de pause courant
 * @param level     le nouveau numero du niveau
 */
void sgu_set_level(int level);

/**
 * Gere la sortie des balles
 * @param env       L'environement de jeux
 */
void sgu_handle_balls_out(State_Game_Env* env);

#endif
