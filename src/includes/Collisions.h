/**
 *	@author		Antoine HEZARD
 *	@author		Amirouche HALFAOUI
 *	@date		29.10.2010
 *
 *	Gestion des collisions entre les differents objets
 */

#ifndef COLLISIONS_H
#define COLLISIONS_H

/**
 *	Gestion generale des collisions de l'etat Jeu
 *	@param	env			Envirronement du jeu
 *	@return				Nul si pas de collision, un entier sinon
 */
int collision_state_game(State_Game_Env* env);

/**
 *	Gestion des collisions de la rackette sur les bords du terrain
 *	@param	racket		La rackette
 *  @param  ground      Le terrain
 *	@return				Nul si pas de collision, un entier sinon
 */
int collision_racket_ground(Racket* racket, Ground* ground);

/**
 *	Gestion des collisions de la balle sur les bords du terrain
 *	@param	ball		La balle
 *  @param  ground      Le terrain
 *	@return				Nul si pas de collision, un entier sinon
 */
int collision_ball_ground(Ball* ball, Ground* ground);

/**
 *	Gestion des collisions de la balle sur une rackette
 *	@param	ball		La balle
 *  @param  racket      La rackette
 *	@return				Nul si pas de collision, un entier sinon
 */
int collision_ball_racket(Ball* ball, Racket* racket);

/**
 *	Gestion des collisions entre deux balle
 *	@param	ball_a		La balle
*	@param	ball_b		L'autre balle
 *	@return				Nul si pas de collision, un entier sinon
 */
int collision_ball_ball(Ball* ball_a, Ball* ball_b);

#endif
