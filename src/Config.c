#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <GL/gl.h>
#include "includes/Coords.h"
#include "includes/Particles.h"
#include "includes/State.h"
#include "includes/Racket.h"
#include "includes/Ball.h"
#include "includes/Ground.h"
#include "includes/Config.h"
#include "includes/State_Game.h"
#include "includes/Menu_Item.h"
#include "includes/State_Menu.h"

int config_load(float* config) {
    char* vars[CONFIG_NB] = {
        "mouse_sensibility=%f\n",
        "reflection=%f\n",
        "particles=%f\n"
    };
    int i;
    FILE* file_config = fopen("config/config.cfg", "r+");
    if (!file_config) {
        fprintf(stderr, "Erreur :: Impossible d'ouvrir le fichier de config 'config/config.cfg' \n");
        exit(11);
    }
    for (i = 0; i < CONFIG_NB; i++) {
        fscanf(file_config, vars[i], &config[i]);
    }
    fclose(file_config);
    return 1;
}

int config_load_state_game(void* game_env) {
    State_Game_Env* env = (State_Game_Env*) game_env;
    float config[CONFIG_NB];
    int i;
    if (config_load(config)) {
        for (i = 0; i < CONFIG_NB; i++) {
            env->config[i] = config[i];
        }
        return 1;
    } else {
        fprintf(stderr, "Erreur :: Impossible d'ouvrir le fichier de config 'config/config.cfg' \n");
        exit(11);
    }
    return 0;
}

int config_load_state_menu(void* menu_env) {
    State_Menu_Env* env = (State_Menu_Env*) menu_env;
    float config[CONFIG_NB];
    int i;
    if (config_load(config)) {

        env->config[CONFIG_MOUSE_SENSIBILITY] = (int) (80.0f * config[CONFIG_MOUSE_SENSIBILITY]);
        env->config[CONFIG_REFLECTION] = (int) config[CONFIG_REFLECTION];
        env->config[CONFIG_PARTICLES] = (int) config[CONFIG_PARTICLES];

        return 1;
    } else {
        fprintf(stderr, "Erreur :: Impossible d'ouvrir le fichier de config 'config/config.cfg' \n");
        exit(11);
    }
    return 0;
}

int config_save_state_menu(int* config) {
    char* vars[CONFIG_NB] = {
        "mouse_sensibility=%f\n",
        "reflection=%f\n",
        "particles=%f\n"
    };
    FILE* file_config = fopen("config/config.cfg", "w");
    if (!file_config) {
        fprintf(stderr, "Erreur :: Impossible d'ouvrir le fichier de config 'config/config.cfg' \n");
        exit(11);
    }

    fprintf(file_config, vars[CONFIG_MOUSE_SENSIBILITY], (float) config[CONFIG_MOUSE_SENSIBILITY] / 80.0f);
    fprintf(file_config, vars[CONFIG_REFLECTION], (float) config[CONFIG_REFLECTION]);
    fprintf(file_config, vars[CONFIG_PARTICLES], (float) config[CONFIG_PARTICLES]);

    fclose(file_config);
    return 1;
}
