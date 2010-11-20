#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <math.h>
#include "includes/State_Game.h"
#include "includes/Collisions.h" 


int collision_state_game(State_Game_Env* env){
	/* Il faudra faire une boucle pour toutes les balles */

	collision_ball_racket(&env->ball, &env->racket_bottom);
	collision_ball_racket(&env->ball, &env->racket_top);
	collision_ball_ground(&env->ball, &env->ground);

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

void collision_ball_ground( Ball* ball, Ground* ground ){

	if( ball->x - ball->radius < -ground->width / 2 ){
		
		ball->speed_x *= -1;
		ball->x = ball->radius -ground->width / 2;
	
	} else if( ball->x + ball->radius > ground->width / 2 ){
	
		ball->speed_x *= -1;
		ball->x = ground->width / 2 - ball->radius;
		
	} else if( ball->y + ball->radius > ground->length / 2 ){
		
		ball->speed_y *= -1;
		ball->y = ground->length / 2 - ball->radius;
		
	}
	
}

void collision_ball_racket( Ball* ball, Racket* racket ){

	
	float rckt_width_mi = racket->width/2 - racket->radius;
	
	/* Collision parfaitement au centre */
	if(ball->x > racket->x -rckt_width_mi && ball->x < racket->x + rckt_width_mi ){
		
		/* Arrivee de la balle par le haut */
		if(ball->y - ball->radius <= racket->y + racket->radius && ball->y - ball->radius > racket->y){
				/* On renvoie la balle vers le haut */
				ball->speed_y *= -1;
		}
		
		/* Arrivee de la balle par le bas */
		else if(ball->y + ball->radius >= racket->y - racket->radius && ball->y + ball->radius < racket->y){
				/* On renvoie la balle vers le bas */
				ball->speed_y *= -1;
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
			
			}
			
		}
	}

	
}
