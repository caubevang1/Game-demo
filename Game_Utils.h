#ifndef GAME_UTILS_H_
#define GAME_UTILS_H_

#include "Game_Base.h"
#include "Button.h"
#include "Enemy.h"
#include "Character.h"
#include "KiBlast.h"
#include "Energy.h"
#include "EnemyBullet.h"
void Close();

std::string GetHighScoreFromFile(std::string path);

void UpdateHighScore(std::string path,
    const int& score, 
    const std::string& old_high_score);

int UpdateGameTimeAndScore(int& time, int& speed, int& score);

void RenderScrollingBackground(std::vector <double>& offsetSpeed,
    LTexture(&gBackgroundTexture)[BACKGROUND_0], int num,
    SDL_Renderer* gRenderer);

void RenderScrollingGround(int& speed,
    const int acceleration,
    LTexture gGroundTexture,
    SDL_Renderer* gRenderer);

int randomBackground();

void HandlePlayButton(SDL_Event* e,
    Button& PlayButton,
    bool& QuitMenu,
    bool& Play,
    Mix_Chunk* gClick);

void HandleHelpButton(SDL_Event* e,
    SDL_Rect(&gBackButton)[BUTTON_SPRITES],
    Button& HelpButton,
    Button& BackButton,
    LTexture gInstructionTexture,
    LTexture gBackButtonTexture,
    SDL_Renderer* gRenderer,
    bool& Quit_game,
    Mix_Chunk* gClick);

void HandleExitButton(SDL_Event* e,
    Button& ExitButton,
    bool& Quit,
    Mix_Chunk* gClick);

void HandleContinueButton(Button ContinueButton,
    LTexture gContinueButtonTexture,
    SDL_Event* e,
    SDL_Renderer* gRenderer,
    SDL_Rect(&gContinueButton)[BUTTON_SPRITES],
    bool& Game_State, Mix_Chunk* gClick);

void HandlePauseButton(SDL_Event* e,
    SDL_Renderer* gRenderer,
    SDL_Rect(&gContinueButton)[BUTTON_SPRITES],
    Button& PauseButton,
    Button ContinueButton,
    LTexture gContinueButtonTexture,
    bool& game_state,
    Mix_Chunk* gClick);

void GenerateKi(KiBlast& kiBlast, SDL_Renderer* gRenderer);

void GenerateEnergy(Energy& Energy, SDL_Renderer* gRenderer);

void GenerateBullet(EnemyBullet& bullet, SDL_Renderer* gRenderer);

void GenerateEnemy(Enemy& enemy1,
    Enemy& enemy2,
    Enemy& enemy3,
    SDL_Rect(&gEnemyClips)[FLYING_FRAMES], SDL_Rect(&gEnemyClips2)[9],
    SDL_Renderer* gRenderer);

bool CheckColission(Character character,
    Enemy enemy,
    SDL_Rect* char_clip,
    SDL_Rect* enemy_clip = nullptr);
bool CheckBlastColission(KiBlast kiBlast,
    Enemy enemy,
    SDL_Rect* enemy_clip = nullptr);
bool CheckBulletCollission(Character character,
    EnemyBullet bullet,
    SDL_Rect* char_clip);

bool CheckEnemyColission(Character character,
    Enemy enemy1,
    Enemy enemy2,
    Enemy enemy3,
    SDL_Rect* char_clip,
    SDL_Rect* enemy_clip = nullptr);

bool CheckEnergyColission(Character character, Energy energy, SDL_Rect* char_clip);

void ControlCharFrame(int& frame);

void ControlCharFrame2(int& frame);

void ControlCharFrameBlast(int& frame, Character character);

void ControlEnemyFrame(int& frame);

void ControlEnemy2Frame(int& frame);

void DrawPlayerScore(LTexture gTextTexture,
    LTexture gScoreTexture,
    SDL_Color textColor,
    SDL_Renderer* gRenderer,
    TTF_Font* gFont,
    const int& score);

void DrawPlayerHighScore(LTexture gTextTexture,
    LTexture gHighScoreTexture,
    SDL_Color textColor,
    SDL_Renderer* gRenderer,
    TTF_Font* gFont, 
    const std::string& HighScore);

void DrawEndGameSelection(LTexture gLoseTexture,
    SDL_Event* e,
    SDL_Renderer* gRenderer,
    bool& Play_Again);

#endif // !GAME_UTILS_H_