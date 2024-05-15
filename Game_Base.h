
#ifndef GAME_BASE_
#define GAME_BASE_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>

#define SDL_ERROR 1
#define IMG_ERROR 2
#define MIX_ERROR 3
#define TTF_ERROR 4

#define MIX_CHANNEL -1

#define TIME_MAX 1000
#define GROUND 430
#define MAX_HEIGHT 225

#define BASE_OFFSET_SPEED 0

#define SPEED_INCREASEMENT 2
#define SCORE_INCREASEMENT 1
#define TIME_INCREASEMENT 1
#define FRAME_INCREASEMENT 1

#define GROUND_SPEED 5
#define ENEMY_SPEED 5
#define MAX_ENEMY_WIDTH 100

#define JUMP 1
#define FALL 2
#define RUN	0
#define FAST 3
#define FIGHT 4
#define BLAST 5

#define IN_AIR_ENEMY 1
#define ON_GROUND_ENEMY 0
#define BEAR_ENEMY 2

#define ENEMY_MAX_HEIGHT 300
#define ENEMY_MIN_HEIGHT 330

#define ENEMY_POSITION_RANGE 350
#define ENEMY1_RANGE 200
#define ENEMY2_RANGE 450
#define ENEMY3_RANGE 600

#define SLOW_FRAME_CHAR 4
#define SLOW_FRAME_ENEMY 4
#define SLOW_FRAME_ENEMY2 9

#define IS_REPEATITIVE -1
#define NOT_REPEATITIVE 0

#define ENERGY_MAX_HEIGHT 290
#define ENERGY_MIN_HEIGHT 360
#define ENERGY_POSITION_RANGE 250
#define ENERGY_SPEED 7
#define MAX_ENERGY_WIDTH 100

#define SMALL_BUTTON 1
#define PLAY_BUTTON 3
#define COMMON_BUTTON 2
#define BACK_BUTTON 3


const std::string WINDOW_TITLE = "ROAD OF THE DRAGON BOY";

const int SCREEN_WIDTH = 928;
const int SCREEN_HEIGHT = 522;

const int COMMON_BUTTON_WIDTH = 90;
const int COMMON_BUTTON_HEIGHT = 59;
const int SMALL_BUTTON_WIDTH = 22;
const int SMALL_BUTTON_HEIGHT = 34;
const int PLAY_BUTTON_WIDTH = 190;
const int PLAY_BUTTON_HEIGHT = 124;
const int BACK_BUTTON_WIDTH = 100;
const int BACK_BUTTON_HEIGHT = 78;

const int PLAY_BUTON_POSX = 170;
const int PLAY_BUTTON_POSY = 280;
const int HELP_BUTTON_POSX = 170;
const int HELP_BUTTON_POSY = 420;
const int EXIT_BUTTON_POSX = 270;
const int EXIT_BUTTON_POSY = 420;

const int BACK_BUTTON_POSX = 31;
const int BACK_BUTTON_POSY = 29;
const int PAUSE_BUTTON_POSX = 31;
const int PAUSE_BUTTON_POSY = 29;
const int CONTINUE_BUTTON_POSX = 31;
const int CONTINUE_BUTTON_POSY = 29;

const int TEXT_1_POSX = 670;
const int TEXT_1_POSY = 20;
const int TEXT_2_POSX = 670;
const int TEXT_2_POSY = 80;
const int SCORE_POSX = 830;
const int SCORE_POSY = 20;
const int HIGH_SCORE_POSX = 830;
const int HIGH_SCORE_POSY = 80;

const int RUNNING_FRAMES = 8;
const int WEAPON_FRAMES = 7;
const int BLAST_FRAMES = 3;
const int FLYING_FRAMES = 5;
const int BEAR_FRAMES = 9;
static const int BACKGROUND_0 = 10;
static const int BACKGROUND_1 = 5;

static const int PLAYER_WIDTH = 200;
static const int PLAYER_HEIGHT = 260;
static const int player1_X = 180;
static const int player1_Y = 110;
static const int player2_X = 540;
static const int player2_Y = 110;

static const int FRAME_PER_SECOND = 80;

enum ButtonSprite
{
	BUTTON_MOUSE_OUT = 0,
	BUTTON_MOUSE_OVER = 1,
	BUTTON_SPRITES = 2,
	ONE_SPRITES = 3
};

void LogError(std::string msg, int error_code = SDL_ERROR);

#endif // !GAME_LIB_