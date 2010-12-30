#ifndef CONFIG_H
#define CONFIG_H

	#define CONFIG_NB					3
	
	#define CONFIG_MOUSE_SENSIBILITY	0
	#define CONFIG_REFLECTION 			1
	#define CONFIG_PARTICLES			2

	int config_load(float* config);

	int config_load_state_game(State_Game_Env* env);

	int config_load_state_menu(State_Menu_Env* env);

#endif