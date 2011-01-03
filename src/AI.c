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

#define AI_EASY_SPEED	RACKET_SPEED_MAX/6.0f
#define AI_MEDIUM_SPEED	RACKET_SPEED_MAX/3.0f
#define AI_HARD_SPEED	RACKET_SPEED_MAX



void AI_medium(State_Game_Env* env, int racket_id){

}


void AI_easy(State_Game_Env* env, int racket_id){

	int i;
	Ball* ball = NULL;
	Racket* racket = &env->racket[racket_id];
	GLfloat dist, b_s = 1000000.0f, b_s_temp;
	
	/* Choix de la balle a intercepter */
	for(i = 0; i < env->balls_nb; i++){
		
		/* Si la balle va dans le bon sens */
		if((env->ball[i].speed.y > 0 && racket->position.y > env->ball[i].position.y) || (env->ball[i].speed.y < 0 && racket->position.y < env->ball[i].position.y)){
			
			b_s_temp = (env->ball[i].position.y - racket->position.y) / env->ball[i].speed.y;
			if(b_s_temp < b_s){
				b_s = b_s_temp;
				ball = &env->ball[i];
			}
		}
	}
	
	/* Poursuite de la balle */
	if (ball != NULL) {
		float dist = fabs(ball->position.x - racket->position.x);
		float dir = (ball->position.x > racket->position.x)? 1.0 : -1.0;

		if (dist > racket->width/4.0)
		{
			if (dist > AI_EASY_SPEED)
				racket->speed = dir * AI_EASY_SPEED;
			else
				racket->speed = dir * dist;
		}
		else
			racket->speed = 0.0f;
	}
	else
		racket->speed = 0.0f;
}
