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

	Ball* ball = &env->ball[0];
	Racket* racket = &env->racket[racket_id];
	GLfloat dist;
	if( (ball->speed.y > 0 && racket->position.y < ball->position.y) || (ball->speed.y < 0 && racket->position.y > ball->position.y)  ){
		racket->speed = 0.0f;	
	}
	else {
		if(fabs(ball->position.y-racket->position.y) < env->ground.length/2.0f ){
			
			dist = racket->position.x - ball->position.x;
			
			if( dist > racket->width/4.0f){
				if(racket->speed > -RACKET_SPEED_MAX){
					racket->speed -= fabs(ball->speed.x)/20.0f + fabs(ball->speed.y)/20.0f;
				}
				else {
					racket->speed = -RACKET_SPEED_MAX;
				}
			}
			else if( dist < -racket->width/4.0f){
				if(racket->speed < RACKET_SPEED_MAX){
					racket->speed += fabs(ball->speed.x)/20.0f + fabs(ball->speed.y)/20.0f;
				}
				else{
					racket->speed = RACKET_SPEED_MAX;
				}
			}
			else {
					racket->speed /=  fabs(env->ground.length/(3*dist));
			}
		}
	}
}