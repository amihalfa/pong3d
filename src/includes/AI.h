#ifndef AI_H
#define AI_H

/**
 * Fontion qui bouge un raquette selon le mode facile de l'IA
 * @param env       L'environement de jeux
 * @param racket_id L'id de la raquette a bouger (RACKET_TOP/RACKET_BOTTOM)
 */
void AI_easy(State_Game_Env* env, int racket_id);

/**
 * Fontion qui bouge un raquette selon le mode moyen de l'IA
 * @param env       L'environement de jeux
 * @param racket_id L'id de la raquette a bouger (RACKET_TOP/RACKET_BOTTOM)
 */
void AI_medium(State_Game_Env* env, int racket_id);

/**
 * Fontion qui bouge un raquette selon le mode difficile de l'IA
 * @param env       L'environement de jeux
 * @param racket_id L'id de la raquette a bouger (RACKET_TOP/RACKET_BOTTOM)
 */
void AI_hard(State_Game_Env* env, int racket_id);

#endif
