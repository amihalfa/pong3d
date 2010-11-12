#include "includes/Ball.h"
#include "includes/Racket.h"
#include "includes/Ground.h"
#include "includes/Collisions.h" 


int collision_racket_ground(Racket* racket, Ground* ground, int position){

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