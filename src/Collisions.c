#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <math.h>
#include "includes/Coords.h"
#include "includes/Particles.h"
#include "includes/State.h"
#include "includes/Ground.h"
#include "includes/Ball.h"
#include "includes/Racket.h"
#include "includes/Config.h"
#include "includes/State_Game.h"
#include "includes/Collisions.h" 
#include "includes/Racket.h"


int collision_state_game(State_Game_Env* env){

	int i,j;
	for(i = 0 ; i< env->balls_nb ; i++){
	
		collision_ball_racket(&env->ball[i], &env->racket[RACKET_BOTTOM]);
		collision_ball_racket(&env->ball[i], &env->racket[RACKET_TOP]);
		collision_ball_ground(&env->ball[i], &env->ground);
		
		for(j = env->balls_nb - 1; j > i ; j--){
			collision_ball_ball( &env->ball[i], &env->ball[j] ); 
			
		}
	}
	for(i = 0; i < 2; i++)
		collision_racket_ground(&env->racket[i], &env->ground);

	return 0;
}

int collision_racket_ground( Racket* racket, Ground* ground){

	float rckt_width_mi = racket->width / 2;
	float grnd_width_mi = ground->width / 2;
	if( racket->position.x - rckt_width_mi <= -grnd_width_mi ){
		racket->position.x = -grnd_width_mi + rckt_width_mi;
		return 1;
	}
	if( racket->position.x + rckt_width_mi >= grnd_width_mi ){
		racket->position.x = - rckt_width_mi + grnd_width_mi;
		return 1;
	}
	return 0;

}

int collision_ball_ground( Ball* ball, Ground* ground ){

	/* Collision a gauche du terrain */
	if( ball->position.x - ball->radius < -ground->width / 2 ){
		ball->speed.x *= -1;
		ball->position.x = ball->radius -ground->width / 2;
		
		return 1;
	} 
	
	/* Collision a droite du terrain */
	else if( ball->position.x + ball->radius > ground->width / 2 ){
		ball->speed.x *= -1;
		ball->position.x = ground->width / 2 - ball->radius;
		
		return 1;
	} 
	
	/* Collision par le haut ... C'est temporaire ... */
	else if( ball->position.y + ball->radius > ground->length / 2 ){
		
		ball->speed.y *= -1;
		ball->position.y = ground->length / 2 - ball->radius;
		
		return 2;
	}
	return 0;
	
}

int collision_ball_racket( Ball* ball, Racket* racket ){

	
	float rckt_width_mi = racket->width/2 - racket->radius;
	
	/* Collision parfaitement au centre */
	if(ball->position.x > racket->position.x -rckt_width_mi && ball->position.x < racket->position.x + rckt_width_mi ){
		
		/* Arrivee de la balle par le haut */
		if(ball->position.y - ball->radius > racket->position.y && ball->position.y - ball->radius < racket->position.y + racket->radius){
				
			ball->position.y = racket->position.y + racket->radius + ball->radius;
			/* On renvoie la balle vers le haut */
			ball->speed.y = fabs(ball->speed.y);
			return 1;
		}
		
		/* Arrivee de la balle par le bas */
		else if(ball->position.y + ball->radius < racket->position.y && ball->position.y + ball->radius > racket->position.y - racket->radius){
			
			ball->position.y = racket->position.y - racket->radius - ball->radius;
			/* On renvoie la balle vers le bas */
			ball->speed.y = -fabs(ball->speed.y);

			return 1;
		}
	}
	else if(ball->position.y - ball->radius < racket->position.y + racket->radius){ 
		if(ball->position.y + ball->radius > racket->position.y - racket->radius){

			
			float dist_x_r, dist_x_l =  ball->position.x - (racket->position.x - rckt_width_mi);
			float dist_y = - racket->position.y + ball->position.y;
			
			float dist_left = sqrt( dist_x_l*dist_x_l + dist_y*dist_y );
			float dist_right = 0; 
			
			dist_x_r = - racket->position.x - rckt_width_mi + ball->position.x;
			
			dist_right = sqrt( dist_x_r*dist_x_r + dist_y*dist_y );
			
			float dist = ball->radius + racket->radius;
			

			Coord2d axe, speed_col;
			float norm, tmp, rack_x;
			char there_is_a_collision = 0;

			/* La raquette a ete cognee par la gauche */
			if(dist_left < dist){
				tmp = dist / dist_left;
				rack_x = racket->position.x - rckt_width_mi;
				there_is_a_collision = 1;
			}
			/* La raquette a ete cognee par la droite */
			else if(dist_right < dist){
				tmp = dist / dist_right;
				rack_x = racket->position.x + rckt_width_mi;
				there_is_a_collision = 1;
			}

			if (there_is_a_collision)
			{
				/* place la balle b a la bonne distance de a */
				ball->position.x = (ball->position.x - rack_x) * tmp + rack_x;
				ball->position.y = (ball->position.y - racket->position.y) * tmp + racket->position.y;

				/* on recupere l'axe de coball_allision sous forme de vecteur unitaire */
				axe.x = (ball->position.x - rack_x) / dist;
				axe.y = (ball->position.y - racket->position.y) / dist;

				/* on recupere la compasante de la vitesse de la balle selon l'xe de collision */
				norm = ball->speed.x * axe.x + ball->speed.y * axe.y;
				speed_col.x = norm * axe.x;
				speed_col.y = norm * axe.y;

				/* enfin on met a jour la vitesse en inversant sa composante selon l'axe de collision et en eventuellement en augementant la vitesse selon y en fonction de la vitesse de la rackette */
				ball->speed.x -= 2*speed_col.x;
				ball->speed.y -= 2*speed_col.y;
			}
		}
	}
	return 0;
	
}

int collision_ball_ball( Ball* ball_a, Ball* ball_b ){

	float dist_x = ball_b->position.x - ball_a->position.x;
	float dist_y = ball_b->position.y - ball_a->position.y;
	float dist = ball_a->radius + ball_b->radius;
	
	/* Distance entre les deux balles */
	float dist_bb = sqrt( dist_x*dist_x + dist_y*dist_y );
	
	/* Cas ou il y a collision */
	if(dist_bb < dist ){

		Coord2d axe, speed_col_a, speed_col_b, speed_nor_a, speed_nor_b;
		float norm, tmp;
	
		/* place la balle b a la bonne distance de a */
		tmp = dist / dist_bb;
		ball_b->position.x = (ball_b->position.x - ball_a->position.x) * tmp + ball_a->position.x;
		ball_b->position.y = (ball_b->position.y - ball_a->position.y) * tmp + ball_a->position.y;
		
		/* on recupere l'axe de collision sous forme de vecteur unitaire */
		axe.x = (ball_b->position.x - ball_a->position.x) / dist;
		axe.y = (ball_b->position.y - ball_a->position.y) / dist;

		/* on separe les vitesse en deux vecteurs : un selon l'axe de collision (col), et l'autre selon l'axe normal a la collision (nor) */
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

		/* on echange les veteurs selon l'axe de colision */
		tmp = speed_col_a.x;
		speed_col_a.x = speed_col_b.x;
		speed_col_b.x = tmp;
		tmp = speed_col_a.y;
		speed_col_a.y = speed_col_b.y;
		speed_col_b.y = tmp;

		/* enfin on met a jour les vitesses de a et b en sommant leurs composantes */
		ball_a->speed.x = speed_col_a.x + speed_nor_a.x;
		ball_a->speed.y = speed_col_a.y + speed_nor_a.y;
		ball_b->speed.x = speed_col_b.x + speed_nor_b.x;
		ball_b->speed.y = speed_col_b.y + speed_nor_b.y;

		return 1;
	}
	
	/* Pas de collision entre les balles */
	else {
		return 0;
	}
}


