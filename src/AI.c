#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "includes/Coords.h"
#include "includes/Particles.h"
#include "includes/State.h"
#include "includes/Racket.h"
#include "includes/Ball.h"
#include "includes/Ground.h"
#include "includes/Config.h"
#include "includes/State_Game.h"
#include "includes/Collisions.h"
#include "includes/AI.h"

void AI_easy(State_Game_Env* env, int racket_id){

	int i;
	Ball* ball= &env->ball[0];
	Racket* racket = &env->racket[racket_id];
	GLfloat dist, b_s = 1000.0f, b_s_temp;
	
	/* Choix de la balle a intercepter */
	for(i = 0; i < env->balls_nb; i++){
		
		/* Si la balle va dans le bon sens */
		if((ball->speed.y > 0 && racket->position.y < ball->position.y) || (ball->speed.y < 0 && racket->position.y > ball->position.y)){
			
			b_s_temp = (ball->position.y - racket->position.y) / ball->speed.y;
			if(b_s_temp <= b_s){
				b_s = b_s_temp;
				ball = &env->ball[i];
			}
		}
	}
	
	/* Poursuite de la balle */
	if( (ball->speed.y > 0 && racket->position.y < ball->position.y) || (ball->speed.y < 0 && racket->position.y > ball->position.y)  ){
		racket->speed = 0.0f;	
	}
	else {
		if(fabs(ball->position.y-racket->position.y) < env->ground.length/2.0f ){
			
			dist = racket->position.x - ball->position.x;
			
			if( dist > racket->width/8.0f){
				if(racket->speed > -RACKET_SPEED_MAX){
					racket->speed -= (float)(rand()%100 + 100)/10000.0;
				}
				else {
					racket->speed = -RACKET_SPEED_MAX;
				}
			}
			else if( dist < -racket->width/8.0f){
				if(racket->speed < RACKET_SPEED_MAX){
					racket->speed += (float)(rand()%100+ 100)/10000.0;
				}
				else{
					racket->speed = RACKET_SPEED_MAX;
				}
			}
			else {
				if(racket->speed > 0){
					racket->speed -= (float)(rand()%100 + 100)/1000.0;
				}
				else {
					racket->speed += (float)(rand()%100 +100)/1000.0;
				}
			}
		}
	}
}