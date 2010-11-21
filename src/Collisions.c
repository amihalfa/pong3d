#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <math.h>
#include "includes/State_Game.h"
#include "includes/Collisions.h" 


int collision_state_game(State_Game_Env* env, Uint32 e_time){
	/* Il faudra faire une boucle pour toutes les balles */

	int i,j;
	for(i = 0 ; i< 2 ; i++){
	
		if(collision_ball_racket(&env->ball[i], &env->racket_bottom) == 2){
			ball_move(&env->ball[i], e_time);
			ball_move(&env->ball[i], e_time);
		}
		if(collision_ball_racket(&env->ball[i], &env->racket_top) == 2){
			ball_move(&env->ball[i], e_time);
			ball_move(&env->ball[i], e_time);
		}
		collision_ball_ground(&env->ball[i], &env->ground);
		
		for(j = 0 ; j < 2 ; j++){
			if(j != i){
				if(collision_ball_ball( &env->ball[i], &env->ball[j] )){
					ball_move(&env->ball[i], e_time);
					ball_move(&env->ball[j], e_time);
					ball_move(&env->ball[i], e_time);
					ball_move(&env->ball[j], e_time);
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
		ball->speed_x *= -1;
		ball->x = ball->radius -ground->width / 2;
		
		return 1;
	} 
	
	/* Collision a droite du terrain */
	else if( ball->x + ball->radius > ground->width / 2 ){
		ball->speed_x *= -1;
		ball->x = ground->width / 2 - ball->radius;
		
		return 1;
	} 
	
	/* Collision par le haut ... C'est temporaire ... */
	else if( ball->y + ball->radius > ground->length / 2 ){
		
		ball->speed_y *= -1;
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
				ball->speed_y *= -1;
				return 1;
		}
		
		/* Arrivee de la balle par le bas */
		else if(ball->y + ball->radius >= racket->y - racket->radius && ball->y + ball->radius < racket->y){
				/* On renvoie la balle vers le bas */
				ball->speed_y *= -1;
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
				
				float d_x = ball->speed_x;
				float d_y = ball->speed_y;
				
				float o_x = u_x * (u_x*d_x + u_y*d_y) / (u_x*u_x + u_y*u_y);
				float o_y = u_y * (u_x*d_x + u_y*d_y) / (u_x*u_x + u_y*u_y);
				
				float d_o = sqrt(o_x*o_x + o_y*o_y);
				
				ball->speed_x += 2 * d_o * u_x;
				ball->speed_y += 2 * d_o * u_y;
				return 2;
			}
			
			/* La raquette a ete cognee par la droite */
			else if(dist_right <= ball->radius + racket->radius){
				
				float u_x = dist_x_r / dist_right;
				float u_y = dist_y / dist_right;
				
				float d_x = ball->speed_x;
				float d_y = ball->speed_y;
				
				float o_x = u_x * (u_x*d_x + u_y*d_y) / (u_x*u_x + u_y*u_y);
				float o_y = u_y * (u_x*d_x + u_y*d_y) / (u_x*u_x + u_y*u_y);
				
				float d_o = sqrt(o_x*o_x + o_y*o_y);
				
				ball->speed_x += 2 * d_o * u_x;
				ball->speed_y += 2 * d_o * u_y;
				return 2;
			}
			
		}
	}
	return 0;
	
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