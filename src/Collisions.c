#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <math.h>
#include "includes/State_Game.h"
#include "includes/Collisions.h" 
#include "includes/Racket.h"


int collision_state_game(State_Game_Env* env){

	int i,j;
	for(i = 0 ; i< env->balls_nb ; i++){
	
		if(collision_ball_racket(&env->ball[i], &env->racket_bottom) == 2){
			ball_move(&env->ball[i], env->ellapsed_time);
			ball_move(&env->ball[i], env->ellapsed_time);
		}
		if(collision_ball_racket(&env->ball[i], &env->racket_top) == 2){
			ball_move(&env->ball[i], env->ellapsed_time);
			ball_move(&env->ball[i], env->ellapsed_time);
		}
		collision_ball_ground(&env->ball[i], &env->ground);
		
		for(j = 0 ; j < env->balls_nb ; j++){
			if(j != i){
				if(collision_ball_ball( &env->ball[i], &env->ball[j] )){
					ball_move(&env->ball[i], env->ellapsed_time);
					ball_move(&env->ball[j], env->ellapsed_time);
					ball_move(&env->ball[i], env->ellapsed_time);
					ball_move(&env->ball[j], env->ellapsed_time);
				}
			}
		}
		
	}

	return 0;
}

int collision_racket_ground( Racket* racket, Ground* ground, int position ){

	float rckt_width_mi = racket->width / 2;
	float grnd_width_mi = ground->width / 2;
	if(position == COLLISION_LEFT){
		if( racket->x - rckt_width_mi <= -grnd_width_mi ){
			return 1;
		}
	} else if(position == COLLISION_RIGHT){
		if( racket->x + rckt_width_mi >= grnd_width_mi ){
			return 1;
		}
	}
	return 0;

}

int collision_ball_ground( Ball* ball, Ground* ground ){

	/* Collision a gauche du terrain */
	if( ball->x - ball->radius < -ground->width / 2 ){
		ball->speed.x *= -1;
		ball->x = ball->radius -ground->width / 2;
		
		return 1;
	} 
	
	/* Collision a droite du terrain */
	else if( ball->x + ball->radius > ground->width / 2 ){
		ball->speed.x *= -1;
		ball->x = ground->width / 2 - ball->radius;
		
		return 1;
	} 
	
	/* Collision par le haut ... C'est temporaire ... */
	else if( ball->y + ball->radius > ground->length / 2 ){
		
		ball->speed.y *= -1;
		ball->y = ground->length / 2 - ball->radius;
		
		return 2;
	}
	return 0;
	
}

int collision_ball_racket( Ball* ball, Racket* racket ){

	
	float rckt_width_mi = racket->width/2 - racket->radius;
	
	/* Collision parfaitement au centre */
	if(ball->x > racket->x -rckt_width_mi && ball->x < racket->x + rckt_width_mi ){
		
		/* Arrivee de la balle par le haut */
		if(ball->y - ball->radius <= racket->y + racket->radius && ball->y - ball->radius > racket->y){
				/* On renvoie la balle vers le haut */
				ball->speed.y *= -1;
				return 1;
		}
		
		/* Arrivee de la balle par le bas */
		else if(ball->y + ball->radius >= racket->y - racket->radius && ball->y + ball->radius < racket->y){
				/* On renvoie la balle vers le bas */
				ball->speed.y *= -1;
				return 1;
		}
	}
	else if(ball->y - ball->radius <= racket->y + racket->radius){ 
		if(ball->y + ball->radius >= racket->y - racket->radius){
	
			float dist_x_r, dist_x_l =  ball->x - (racket->x - rckt_width_mi);
			float dist_y = - racket->y + ball->y;
			
			float dist_left = sqrt( dist_x_l*dist_x_l + dist_y*dist_y );
			float dist_right = 0; 
			
			dist_x_r = - racket->x - rckt_width_mi + ball->x;
			
			dist_right = sqrt( dist_x_r*dist_x_r + dist_y*dist_y );
			
			/* La raquette a ete cognee par la gauche */
			if(dist_left <= ball->radius + racket->radius){
			
				float u_x = dist_x_l / dist_left;
				float u_y = dist_y / dist_left;
				
				float d_x = ball->speed.x;
				float d_y = ball->speed.y;
				
				float o_x = u_x * (u_x*d_x + u_y*d_y) / (u_x*u_x + u_y*u_y);
				float o_y = u_y * (u_x*d_x + u_y*d_y) / (u_x*u_x + u_y*u_y);
				
				float d_o = sqrt(o_x*o_x + o_y*o_y);
				
				ball->speed.x += 2 * d_o * u_x;
				ball->speed.y += 2 * d_o * u_y;
				return 2;
			}
			
			/* La raquette a ete cognee par la droite */
			else if(dist_right <= ball->radius + racket->radius){
				
				float u_x = dist_x_r / dist_right;
				float u_y = dist_y / dist_right;
				
				float d_x = ball->speed.x;
				float d_y = ball->speed.y;
				
				float o_x = u_x * (u_x*d_x + u_y*d_y) / (u_x*u_x + u_y*u_y);
				float o_y = u_y * (u_x*d_x + u_y*d_y) / (u_x*u_x + u_y*u_y);
				
				float d_o = sqrt(o_x*o_x + o_y*o_y);
				
				ball->speed.x += 2 * d_o * u_x;
				ball->speed.y += 2 * d_o * u_y;
				return 2;
			}
		}
	}
	return 0;
	
}

int collision_ball_ball2( Ball* ball_a, Ball* ball_b ){

	float dist_x = ball_b->x - ball_a->x;
	float dist_y = ball_b->y - ball_a->y;
	float dist = ball_a->radius + ball_b->radius;
	
	/* Distance entre les deux balles *
	float dist_bb = sqrt( dist_x*dist_x + dist_y*dist_y );
	
	/* Cas ou il y a collision */
	if(dist_bb <= dist ){

		Coord2d axe, speed_col_a, speed_col_b, speed_nor_a, speed_nor_b;
		float norm, tmp;
	
		/* place la balle b a la bonne distance de a */
		tmp = dist / dist_bb;
		ball_b->x *= tmp;
		ball_b->y *= tmp;
		
		/* on récupèrele l'axe de collision sous forme de vecteur unitaire */
		axe.x = (ball_b->x - ball_a->x) / dist;
		axe.y = (ball_b->y - ball_a->y) / dist;

		/* on sépare les vitesse en deux vecteurs : un selon l'axe de collision (col), et l'autre selon l'axe normal a la collision (nor) */
		norm = ball_a->speed.x * axe.x + ball_a->speed.y * axe.y;
		speed_col_a.x = norm * axe.x;
		speed_col_a.y = norm * axe.y;
		speed_nor_a.x = ball_a->speed.x - speed_col_a.x;
		speed_nor_a.y = ball_a->speed.y - speed_col_a.y;
		norm = ball_b->speed.x * axe.x + ball_b->speed.y * axe.y;
		speed_col_b.x = norm * axe.x;
		speed_col_b.y = norm * axe.y;
		speed_nor_b.x = ball_b->speed.x - speed_col_b.x;
		speed_nor_b.y = ball_b->speed.y - speed_col_b.y;

		/* on échange les veteurs selon l'axe de colision */
		tmp = speed_col_a.x;
		speed_col_a.x = speed_col_b.x;
		speed_col_b.x = tmp;
		tmp = speed_col_a.y;
		speed_col_a.y = speed_col_b.y;
		speed_col_b.y = tmp;

		/* enfin on met a jour les vitesses de a et b en sommant leurs composantes */
		ball_a->speed.x = speed_col_a.x + speed_nor_a.x;
		ball_b->speed.y = speed_col_a.y + speed_nor_a.y;
		ball_b->speed.x = speed_col_b.x + speed_nor_b.x;
		ball_b->speed.y = speed_col_b.y + speed_nor_b.y;

		return 1;
	}
	
	/* Pas de collision entre les balles */
	else {
		return 0;
	}
}


int collision_ball_ball( Ball* ball_a, Ball* ball_b ){

	float dist_x = ball_a->x - ball_b->x;
	float dist_y = ball_a->y - ball_b->y;

	/* Distance entre les deux balles */
	float dist_bb = sqrt( dist_x*dist_x + dist_y*dist_y );

	/* Cas ou il y a collision */
	if(dist_bb <= ball_a->radius + ball_b->radius ){

		/* On devie d'abord la balle A de sa trajectoire */
		float u_x = dist_x / dist_bb;
		float u_y = dist_y / dist_bb;

		float d_x = ball_a->speed_x;
		float d_y = ball_a->speed_y;

		float o_x = u_x * (u_x*d_x + u_y*d_y) / (u_x*u_x + u_y*u_y);
		float o_y = u_y * (u_x*d_x + u_y*d_y) / (u_x*u_x + u_y*u_y);

		float d_o = sqrt(o_x*o_x + o_y*o_y);

		ball_a->speed_x += 2 * d_o * u_x;
		ball_a->speed_y += 2 * d_o * u_y;

		/* On devie la balle B de sa trajectoire */
		u_x = -u_x;
		u_y = -u_y;

		d_x = ball_b->speed_x;
		d_y = ball_b->speed_y;

		o_x = u_x * (u_x*d_x + u_y*d_y) / (u_x*u_x + u_y*u_y);
		o_y = u_y * (u_x*d_x + u_y*d_y) / (u_x*u_x + u_y*u_y);

		d_o = sqrt(o_x*o_x + o_y*o_y);

		ball_b->speed_x += 2 * d_o * u_x;
		ball_b->speed_y += 2 * d_o * u_y;

		return 1;
	}

	/* Pas de collision entre les balles */
	else {
		return 0;
	}
}

