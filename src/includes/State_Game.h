#ifndef STATE_GAME
#define	STATE_GAME

#define STATE_GAME_BALLS	10

#define RACKET_BOTTOM 0
#define RACKET_TOP 1

struct State_Game_Env;

/**
 * Structure de l'environnement de jeu
 */
typedef struct State_Game_Env {
    /** Le terrain */
    Ground ground;

    /** Les rackettes */
    Racket racket[2];

    /** Les ball */
    Ball ball[STATE_GAME_BALLS];

    /** Nombre de balles */
    int balls_nb;

    /** Taille de la fenetre */
    Uint16 w_height, w_width;

    /** Deplacement de la souris en x et y */
    Sint16 mouse_motion_x, mouse_motion_y;

    /** Etat des touches du clavier */
    Uint8 *keystates;

    /** Temps de la frame */
    Uint32 ellapsed_time;

    /** Configurations */
    float config[CONFIG_NB];

    /** Texture pour le score */
	GLuint heart_texture;

	/** Son pour une collision */
	Mix_Chunk* sound;

	/** Texture pour la victoire */
	GLuint bottom_victory_texture, top_victory_texture;

    /** Fonction de gestion de l'IA */
    void (*AI_handler)(struct State_Game_Env* env, int racket_id);

} State_Game_Env;

/**
 *  Fonction contenant l'etat de jeux
 *  @param action   L'action a effectuer
 *  @return         L'etat de jeux
 */
State* state_game(int);

/**
 *  Fonction creant l'etat de jeux
 */
void state_game_create();

/**
 *  Fonction recuperant m'etat de jeux
 *  @return L'etat de jeux
 */
State* state_game_get();

/**
 *  Fonction detruisant l'etat de jeux
 */
void state_game_destroy();

/**
 *  Fonction principale de l'etat de jeux
 *  @param env      L'environement de jeux
 *  @param e_time   Le temps de la frame
 */
void state_game_main(State_Game_Env* env, Uint32 e_time);

/**
 *	Initialisation de l'etat de jeu
 *  @param env      L'environement de jeux
 */
void state_game_init(State_Game_Env* env);

/**
 *	Dessin de l'etat de jeu
 *  @param env      L'environement de jeux
 */
void state_game_draw(State_Game_Env* env);

/**
 *	Gestionnaire des evenements de l'etat de jeu
 *  @param env      L'environement de jeux
 */
int state_game_events(State_Game_Env* env);

#endif

