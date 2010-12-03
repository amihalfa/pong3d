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
	
		collision_ball_racket(&env->ball[i], &env->racket_bottom);
		collision_ball_racket(&env->ball[i], &env->racket_top);
		collision_ball_ground(&env->ball[i], &env->ground);
		
		for(j = env->balls_nb - 1; j > i ; j--){
			collision_ball_ball( &env->ball[i], &env->ball[j] ); 
			
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
		if(ball->y - ball->radius > racket->y && ball->y - ball->radius < racket->y + racket->radius){
				
			ball->y = racket->y + racket->radius + ball->radius;
			/* On renvoie la balle vers le haut */
			ball->speed.y = fabs(ball->speed.y);
			return 1;
		}
		
		/* Arrivee de la balle par le bas */
		else if(ball->y + ball->radius < racket->y && ball->y + ball->radius > racket->y - racket->radius){
			
			ball->y = racket->y - racket->radius - ball->radius;
			/* On renvoie la balle vers le bas */
			ball->speed.y = -fabs(ball->speed.y);

			return 1;
		}
	}
	else if(ball->y - ball->radius < racket->y + racket->radius){ 
		if(ball->y + ball->radius > racket->y - racket->radius){

			
			float dist_x_r, dist_x_l =  ball->x - (racket->x - rckt_width_mi);
			float dist_y = - racket->y + ball->y;
			
			float dist_left = sqrt( dist_x_l*dist_x_l + dist_y*dist_y );
			float dist_right = 0; 
			
			dist_x_r = - racket->x - rckt_width_mi + ball->x;
			
			dist_right = sqrt( dist_x_r*dist_x_r + dist_y*dist_y );
			
			float dist = ball->radius + racket->radius;
			

			Coord2d axe, speed_col;
			float norm, tmp, rack_x;
			char there_is_a_collision = 0;

			/* La raquette a ete cognee par la gauche */
			if(dist_left < dist){
				tmp = dist / dist_left;
				rack_x = racket->x - rckt_width_mi;
				there_is_a_collision = 1;
			}
			/* La raquette a ete cognee par la droite */
			else if(dist_right < dist){
				tmp = dist / dist_right;
				rack_x = racket->x + rckt_width_mi;
				there_is_a_collision = 1;
			}

			if (there_is_a_collision)
			{
				/* place la balle b a la bonne distance de a */
				ball->x = (ball->x - rack_x) * tmp + rack_x;
				ball->y = (ball->y - racket->y) * tmp + racket->y;

				/* on recupere l'axe de coball_allision sous forme de vecteur unitaire */
				axe.x = (ball->x - rack_x) / dist;
				axe.y = (ball->y - racket->y) / dist;

				/* on recupere la compasante de la vitesse de la balle selon l'xe de collision */
				norm = ball->speed.x * axe.x + ball->speed.y * axe.y;
				speed_col.x = norm * axe.x;
				speed_col.y = norm * axe.y;

				/* enfin on met a jour la vitesse en inversant sa composante selon l'axe de collision et en eventuellement en augementant la vitesse selon y en fonction de la vitesse de la rackette */
				ball->speed.x -= 2*speed_col.x;
				ball->speed.y -= 2*speed_col.y;
			}
			/* On evite que la balle aille trop vite */
			/*if (fabs(ball->speed.y) > BALL_MAX_SPEED)
				ball->speed.y = FSIGNE(ball->speed.y)*BALL_MAX_SPEED;

			if (fabs(ball->speed.x) > BALL_MAX_SPEED)
				ball->speed.x = FSIGNE(ball->speed.x)*BALL_MAX_SPEED;*/
		}
	}
	return 0;
	
}

int collision_ball_ball( Ball* ball_a, Ball* ball_b ){

	float dist_x = ball_b->x - ball_a->x;
	float dist_y = ball_b->y - ball_a->y;
	float dist = ball_a->radius + ball_b->radius;
	
	/* Distance entre les deux balles */
	float dist_bb = sqrt( dist_x*dist_x + dist_y*dist_y );
	
	/* Cas ou il y a collision */
	if(dist_bb < dist ){

		Coord2d axe, speed_col_a, speed_col_b, speed_nor_a, speed_nor_b;
		float norm, tmp;
	
		/* place la balle b a la bonne distance de a */
		tmp = dist / dist_bb;
		ball_b->x = (ball_b->x - ball_a->x) * tmp + ball_a->x;
		ball_b->y = (ball_b->y - ball_a->y) * tmp + ball_a->y;
		
		/* on recupere l'axe de collision sous forme de vecteur unitaire */
		axe.x = (ball_b->x - ball_a->x) / dist;
		axe.y = (ball_b->y - ball_a->y) / dist;

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


