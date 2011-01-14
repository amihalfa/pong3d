#ifndef STATE_MENU_UTIL_H
#define STATE_MENU_UTIL_H

int sgu_pause(int pause);
int sgu_get_pause();
void sgu_set_pause(int pause);

int sgu_level(int level);
int sgu_get_level();
void sgu_set_level(int level);

void sgu_handle_balls_out(State_Game_Env* env);

#endif