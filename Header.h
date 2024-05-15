#pragma once
#include "LTexture.h"
#include "Enemy.h"
#include "KiBlast.h"
#include "Character.h"
#include "Game_Base.h"
#include "Game_Utils.h"
#include "Timer.h"
#include "Button.h"
#include "Energy.h"
#include "EnemyBullet.h"
#include "Hud.h"

int startTime = SDL_GetTicks();

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;
SDL_Color textColor = { 0, 0, 0 };
TTF_Font* gFont = nullptr;
Mix_Music* gMusic = nullptr;
Mix_Music* gMenuMusic = nullptr;
Mix_Chunk* gClick = nullptr;
Mix_Chunk* gJump = nullptr;
Mix_Chunk* gLose = nullptr;
Mix_Chunk* gAttack = nullptr;
Mix_Chunk* gBlast = nullptr;


SDL_Rect gPlayButton[BUTTON_SPRITES];
SDL_Rect gHelpButton[BUTTON_SPRITES];
SDL_Rect gExitButton[BUTTON_SPRITES];
SDL_Rect gBackButton[BUTTON_SPRITES];
SDL_Rect gPauseButton[BUTTON_SPRITES];
SDL_Rect gContinueButton[BUTTON_SPRITES];
SDL_Rect gPlayAgainButton[BUTTON_SPRITES];
SDL_Rect gCharacterClips[RUNNING_FRAMES];
SDL_Rect gCharacterClips2[WEAPON_FRAMES];
SDL_Rect gCharacterClipsBlast[BLAST_FRAMES];
SDL_Rect gEnemyClips[FLYING_FRAMES];
SDL_Rect gEnemyClipsBear[BEAR_FRAMES];

LTexture gMenuTexture;
LTexture gInstructionTexture;
LTexture gBackgroundTexture[BACKGROUND_0];
LTexture gCharacterTexture;
LTexture gCharacterTexture2;
LTexture gCharacterTextureBlast;
LTexture gGroundTexture;
LTexture gPlayButtonTexture;
LTexture gHelpButtonTexture;
LTexture gExitButtonTexture;
LTexture gBackButtonTexture;
LTexture gPauseButtonTexture;
LTexture gContinueButtonTexture;
LTexture gLoseTexture;
LTexture gText1Texture;
LTexture gScoreTexture;
LTexture gText2Texture;
LTexture gHighScoreTexture;
LTexture Character_Picture;

Bar BATTERY_0;
Bar BATTERY_1; 
Bar BATTERY_2; 
Bar BATTERY_3; 
Bar BATTERY_4;
Bar BATTERY_5;
Bar BATTERY_6;

Button PlayButton(PLAY_BUTON_POSX, PLAY_BUTTON_POSY);
Button HelpButton(HELP_BUTTON_POSX, HELP_BUTTON_POSY);
Button ExitButton(EXIT_BUTTON_POSX, EXIT_BUTTON_POSY);
Button BackButton(BACK_BUTTON_POSX, BACK_BUTTON_POSY);
Button PauseButton(PAUSE_BUTTON_POSX, PAUSE_BUTTON_POSY);
Button ContinueButton(CONTINUE_BUTTON_POSX, CONTINUE_BUTTON_POSY);

int mana = 3;

Character character;
Enemy enemy;
KiBlast kiBlast;
Energy energy;
EnemyBullet bullet;

bool Quit_Menu = false;
bool Play_Again = false;

int num = randomBackground();

bool Init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_VIDEO) < 0)
	{
		LogError("Can not initialize SDL.", SDL_ERROR);
		success = false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			std::cout << "Warning: Linear texture filtering not enabled!";
		}

		gWindow = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			LogError("Can not create window", SDL_ERROR);
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				LogError("Can not create renderer", SDL_ERROR);
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					LogError("Can not initialize SDL_image", IMG_ERROR);
					success = false;
				}

				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					success = false;
				}

				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}
			}
		}
	}
	return success;
}
bool LoadMedia()
{
	bool success = true;
	gMusic = Mix_LoadMUS("sound/back_audio.wav");
	if (gMusic == nullptr)
	{
		LogError("Failed to load background music", MIX_ERROR);
		success = false;
	}
	else
	{
		Mix_VolumeMusic(MIX_MAX_VOLUME / 3);
	}
	gMenuMusic = Mix_LoadMUS("sound/menu1.wav");
	if (gMenuMusic == nullptr)
	{
		LogError("Failed to load menu music", MIX_ERROR);
		success = false;
	}

	gClick = Mix_LoadWAV("sound/mouse_click.wav");
	if (gClick == nullptr)
	{
		LogError("Failed to load mouse click sound", MIX_ERROR);
		success = false;
	}
	gAttack = Mix_LoadWAV("sound/attack.ogg");
	if (gAttack == nullptr)
	{
		LogError("Failed to load attack sound", MIX_ERROR);
		success = false;
	}
	else
	{
		Mix_VolumeChunk(gAttack, MIX_MAX_VOLUME);
	}
	gBlast = Mix_LoadWAV("sound/blast.ogg");
	if (gBlast == nullptr)
	{
		LogError("Failed to load blast sound", MIX_ERROR);
		success = false;
	}
	else
	{
		Mix_VolumeChunk(gBlast, MIX_MAX_VOLUME);
	}
	gJump = Mix_LoadWAV("sound/jump.ogg");
	if (gJump == nullptr)
	{
		LogError("Failed to load jumping sound", MIX_ERROR);
		success = false;
	}

	gLose = Mix_LoadWAV("sound/die.ogg");
	if (gLose == nullptr)
	{
		LogError("Failed to load lose sound", MIX_ERROR);
		success = false;
	}
	gFont = TTF_OpenFont("font/NTBrickSans.ttf", 20);
	if (gFont == NULL)
	{
		LogError("Failed to load font", MIX_ERROR);
		success = false;
	}
	if (!gText1Texture.LoadFromRenderedText("Your score: ", gFont, textColor, gRenderer))
	{
		std::cout << "Failed to render text1 texture" << std::endl;
		success = false;
	}

	if (!gText2Texture.LoadFromRenderedText("High score: ", gFont, textColor, gRenderer))
	{
		std::cout << "Failed to render text2 texture" << std::endl;
		success = false;
	}

	if (!gMenuTexture.LoadFromFile("imgs/background/menu1.png", gRenderer))
	{
		std::cout << "Failed to load menu image" << std::endl;
		success = false;
	}

	if (!gInstructionTexture.LoadFromFile("imgs/background/instruction.png", gRenderer))
	{
		std::cout << "Failed to load instruction image" << std::endl;
		success = false;
	}
	BATTERY_0.LoadFromFile("imgs/hud/0.png", gRenderer);
	BATTERY_1.LoadFromFile("imgs/hud/1.png", gRenderer);
	BATTERY_2.LoadFromFile("imgs/hud/2.png", gRenderer);
	BATTERY_3.LoadFromFile("imgs/hud/3.png", gRenderer);
	BATTERY_4.LoadFromFile("imgs/hud/4.png", gRenderer);
	BATTERY_5.LoadFromFile("imgs/hud/5.png", gRenderer);
	BATTERY_6.LoadFromFile("imgs/hud/6.png", gRenderer);

	if (!gPlayButtonTexture.LoadFromFile("imgs/button/big_button/play_button.png", gRenderer))
	{
		std::cout << "Failed to load play_button image" << std::endl;
		success = false;
	}
	else
	{
		for (int i = 0; i < BUTTON_SPRITES; ++i)
		{
			gPlayButton[i].x = 190 * i;
			gPlayButton[i].y = 0;
			gPlayButton[i].w = 190;
			gPlayButton[i].h = 124;
		}
	}

	if (!gHelpButtonTexture.LoadFromFile("imgs/button/big_button/help_button.png", gRenderer))
	{
		std::cout << "Failed to load help_button image" << std::endl;
		success = false;
	}
	else
	{
		for (int i = 0; i < BUTTON_SPRITES; ++i)
		{
			gHelpButton[i].x = 90 * i;
			gHelpButton[i].y = 0;
			gHelpButton[i].w = 90;
			gHelpButton[i].h = 59;
		}
	}

	if (!gBackButtonTexture.LoadFromFile("imgs/button/big_button/back_button.png", gRenderer))
	{
		std::cout << "Failed to load back_button image" << std::endl;
		success = false;
	}
	else
	{
		for (int i = 0; i < BUTTON_SPRITES; ++i)
		{
			gBackButton[i].x = 100 * i;
			gBackButton[i].y = 0;
			gBackButton[i].w = 100;
			gBackButton[i].h = 78;
		}
	}

	if (!gExitButtonTexture.LoadFromFile("imgs/button/big_button/exit_button.png", gRenderer))
	{
		std::cout << "Failed to load exit_button image" << std::endl;
		success = false;
	}
	else
	{
		for (int i = 0; i < BUTTON_SPRITES; ++i)
		{
			gExitButton[i].x = 90 * i;
			gExitButton[i].y = 0;
			gExitButton[i].w = 90;
			gExitButton[i].h = 59;
		}
	}

	if (!gPauseButtonTexture.LoadFromFile("imgs/button/big_button/pause_button.png", gRenderer))
	{
		std::cout << "Failed to load pause_button image " << std::endl;
		success = false;
	}
	else
	{
		for (int i = 0; i < BUTTON_SPRITES; ++i)
		{
			gPauseButton[i].x = 22 * i;
			gPauseButton[i].y = 0;
			gPauseButton[i].w = 22;
			gPauseButton[i].h = 34;
		}
	}

	if (!gContinueButtonTexture.LoadFromFile("imgs/button/big_button/continue_button.png", gRenderer))
	{
		std::cout << "Failed to load continue_button image " << std::endl;
		success = false;
	}
	else
	{
		for (int i = 0; i < BUTTON_SPRITES; ++i)
		{
			gContinueButton[i].x = 22 * i;
			gContinueButton[i].y = 0;
			gContinueButton[i].w = 22;
			gContinueButton[i].h = 34;
		}
	}
	Character_Picture.LoadFromFile("imgs/character/Picture.png", gRenderer);
	if (num == 0)
	{
		for (int i = 0; i < BACKGROUND_0; ++i)
		{
			if (!gBackgroundTexture[i].LoadFromFile(LAYER_0[i].c_str(), gRenderer))
			{
				std::cout << "Failed to load background image" << std::endl;
				success = false;
			}
		}
	}
	else
	{
		switch (num)
		{
		case 1:
			for (int i = 0; i < BACKGROUND_1; ++i)
			{
				if (!gBackgroundTexture[i].LoadFromFile(LAYER_1[i].c_str(), gRenderer))
				{
					std::cout << "Failed to load background image" << std::endl;
					success = false;
				}
			}
			break;
		case 2:
			for (int i = 0; i < BACKGROUND_1; ++i)
			{
				if (!gBackgroundTexture[i].LoadFromFile(LAYER_2[i].c_str(), gRenderer))
				{
					std::cout << "Failed to load background image" << std::endl;
					success = false;
				}
			}
			break;
		case 3:
			for (int i = 0; i < BACKGROUND_1; ++i)
			{
				if (!gBackgroundTexture[i].LoadFromFile(LAYER_3[i].c_str(), gRenderer))
				{
					std::cout << "Failed to load background image" << std::endl;
					success = false;
				}
			}
			break;
		case 4:
			for (int i = 0; i < BACKGROUND_1; ++i)
			{
				if (!gBackgroundTexture[i].LoadFromFile(LAYER_4[i].c_str(), gRenderer))
				{
					std::cout << "Failed to load background image" << std::endl;
					success = false;
				}
			}
			break;
		}
	}

	if (!gGroundTexture.LoadFromFile("imgs/background/ground.png", gRenderer))
	{
		std::cout << "Failed to load ground image" << std::endl;
		success = false;
	}
	if (!gCharacterTextureBlast.LoadFromFile("imgs/character/blast.png", gRenderer))
	{
		std::cout << "Failed to load character_blast image." << std::endl;
		success = false;
	}
	else
	{
		for (int i = 0; i < 3; i++)
		{
			gCharacterClipsBlast[i].x = 46 * i;
			gCharacterClipsBlast[i].y = 0;
			gCharacterClipsBlast[i].w = 46;
			gCharacterClipsBlast[i].h = 53;
		}
	}
	if (!gCharacterTexture2.LoadFromFile("imgs/character/hit.png", gRenderer))
	{
		std::cout << "Failed to load character_run2 image." << std::endl;
		success = false;
	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			gCharacterClips2[i].x = 47 * i;
			gCharacterClips2[i].y = 0;
			gCharacterClips2[i].w = 47;
			gCharacterClips2[i].h = 52;
		}

		gCharacterClips2[4].x = 190;
		gCharacterClips2[4].y = 0;
		gCharacterClips2[4].w = 58;
		gCharacterClips2[4].h = 52;

		gCharacterClips2[5].x = 248;
		gCharacterClips2[5].y = 0;
		gCharacterClips2[5].w = 69;
		gCharacterClips2[5].h = 52;

		gCharacterClips2[6].x = 320;
		gCharacterClips2[6].y = 0;
		gCharacterClips2[6].w = 80;
		gCharacterClips2[6].h = 52;
	}

	if (!gCharacterTexture.LoadFromFile("imgs/character/chaz.png", gRenderer))
	{
		std::cout << "Failed to load character_run image." << std::endl;
		success = false;
	}
	else
	{
		for (int i = 0; i < 8; i++)
		{
			gCharacterClips[i].x = 35 * i;
			gCharacterClips[i].y = 0;
			gCharacterClips[i].w = 35;
			gCharacterClips[i].h = 52;
		}

	}
	if (!gLoseTexture.LoadFromFile("imgs/background/lose.png", gRenderer))
	{
		std::cout << "Failed to load lose image." << std::endl;
		success = false;
	}

	return success;
}

void PlayAgain()
{
	Timer fps_timer;
	srand(time(NULL));
	int time = 0;
	int score = 0;
	int acceleration = 0;
	int frame_Character = 0;
	int frame_Character2 = 0;
	int frame_Character_Blast = 0;
	int frame_Enemy = 0;
	int frame_Enemy2 = 0;
	mana = 3;
	character.RenewStatus();
	std::string highscore = GetHighScoreFromFile("high_score.txt");

	SDL_Event e;
	Enemy enemy1(BEAR_ENEMY);
	Enemy enemy2(ON_GROUND_ENEMY);
	Enemy enemy3(IN_AIR_ENEMY);

	Mix_PlayMusic(gMusic, IS_REPEATITIVE);
	GenerateKi(kiBlast, gRenderer);
	GenerateEnergy(energy, gRenderer);
	GenerateEnemy(enemy1, enemy2, enemy3, gEnemyClips, gEnemyClipsBear, gRenderer);

	int OffsetSpeed_Ground = BASE_OFFSET_SPEED;
	std::vector <double> OffsetSpeedBackground(BACKGROUND_0, BASE_OFFSET_SPEED);

	bool Quit = false;
	bool Game_State = true;
	while (!Quit)
	{
		fps_timer.start();
		if (Game_State)
		{
			UpdateGameTimeAndScore(time, acceleration, score);

			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT)
				{
					Quit = true;
					Play_Again = false;
				}

				HandlePauseButton(&e, gRenderer, gContinueButton,
					PauseButton, ContinueButton,
					gContinueButtonTexture, Game_State, gClick);
				kiBlast.HandleEvent(e, character, gRenderer, mana, gBlast);
				character.HandleEvent(e, gJump, mana, gAttack);
			}
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(gRenderer);

			RenderScrollingBackground(OffsetSpeedBackground, gBackgroundTexture, num, gRenderer);
			RenderScrollingGround(OffsetSpeed_Ground, acceleration, gGroundTexture, gRenderer);

			Character_Picture.Render(90, 0, gRenderer, nullptr);

			character.Move();
			SDL_Rect* currentClip_Character = nullptr;
			if (character.Fight())
			{
				currentClip_Character = &gCharacterClips2[frame_Character2 / SLOW_FRAME_CHAR];
				character.Render(currentClip_Character, gRenderer, gCharacterTexture2);
			}
			else if (character.GetStatus() == BLAST)
			{
				currentClip_Character = &gCharacterClipsBlast[frame_Character_Blast / SLOW_FRAME_CHAR];
				character.Render(currentClip_Character, gRenderer, gCharacterTextureBlast);
			}

			else if (character.OnGround())
			{
				currentClip_Character = &gCharacterClips[frame_Character / SLOW_FRAME_CHAR];
				character.Render(currentClip_Character, gRenderer, gCharacterTexture);
			}
			else
			{
				currentClip_Character = &gCharacterClips[0];
				character.Render(currentClip_Character, gRenderer, gCharacterTexture);
			}
			switch (mana)
			{
			case 0:
				BATTERY_0.Render(gRenderer, nullptr);
				break;
			case 1:
				BATTERY_1.Render(gRenderer, nullptr);
				break;
			case 2:
				BATTERY_2.Render(gRenderer, nullptr);
				break;
			case 3:
				BATTERY_3.Render(gRenderer, nullptr);
				break;
			case 4:
				BATTERY_4.Render(gRenderer, nullptr);
				break;
			case 5:
				BATTERY_5.Render(gRenderer, nullptr);
				break;
			case 6:
				BATTERY_6.Render(gRenderer, nullptr);
				break;
			}

			SDL_Rect* currentClip_Enemy = nullptr;

			enemy1.Move(acceleration + 3);
			currentClip_Enemy = &gEnemyClipsBear[frame_Enemy2 / SLOW_FRAME_ENEMY2];
			enemy1.Render(gRenderer, currentClip_Enemy);

			enemy2.Move(acceleration);
			enemy2.Render(gRenderer);

			enemy3.Move(acceleration + 1);
			currentClip_Enemy = &gEnemyClips[frame_Enemy / SLOW_FRAME_ENEMY];
			enemy3.Render(gRenderer, currentClip_Enemy);

			GenerateBullet(bullet, gRenderer);
			if (!enemy3.IsDead())
			{
				bullet.Fire(enemy3.GetPosX() - 5, enemy3.GetPosY() + 3);
			}
			
			bullet.Move(acceleration);
			bullet.Render(gRenderer);

			energy.Move(acceleration);
			energy.Render(gRenderer, nullptr);

			kiBlast.SetBlasts(mana / 2);
			kiBlast.Move();
			kiBlast.Render(gRenderer);


			SDL_Rect* currentClip_Pause = &gPauseButton[PauseButton.currentSprite];
			PauseButton.Render(currentClip_Pause, gRenderer, gPauseButtonTexture);


			DrawPlayerScore(gText1Texture, gScoreTexture, textColor, gRenderer, gFont, score);
			DrawPlayerHighScore(gText2Texture, gHighScoreTexture, textColor, gRenderer, gFont, highscore);

			for (auto& blast : kiBlast.blasts) if (CheckBlastColission(blast,
				enemy1,
				currentClip_Enemy) && !blast.IsHit())
			{
				enemy1.SetDead();
				blast.SetHit(true);
			}
			for (auto& blast : kiBlast.blasts) if (CheckBlastColission(blast,
				enemy3,
				currentClip_Enemy) && !blast.IsHit())
			{
				enemy3.SetDead();
				blast.SetHit(true);
			}
			for (auto& blast : kiBlast.blasts) if (CheckBlastColission(blast,
				enemy2,
				currentClip_Enemy) && !blast.IsHit())
			{
				enemy2.SetDead();
				blast.SetHit(true);
			}

			kiBlast.blasts.erase(std::remove_if(kiBlast.blasts.begin(), kiBlast.blasts.end(), [](KiBlast& b) { return b.IsHit(); }), kiBlast.blasts.end());

			if (CheckEnemyColission(character,
				enemy1,
				enemy2,
				enemy3,
				currentClip_Character,
				currentClip_Enemy) && character.GetStatus() != FIGHT)
			{
				Mix_PauseMusic();
				Mix_PlayChannel(MIX_CHANNEL, gLose, NOT_REPEATITIVE);
				UpdateHighScore("high_score.txt", score, highscore);
				Quit = true;
			}
			if (CheckColission(character,
				enemy1,
				currentClip_Character, currentClip_Enemy) && character.GetStatus() == FIGHT)
			{
				enemy1.SetDead();

			}
			if (CheckColission(character,
				enemy2,
				currentClip_Character, currentClip_Enemy) && character.GetStatus() == FIGHT)
			{

				enemy2.SetDead();
			}
			for (auto& bullet : bullet.bullets)if (CheckBulletCollission(character, bullet, currentClip_Character))
			{
				Mix_PauseMusic();
				Mix_PlayChannel(MIX_CHANNEL, gLose, NOT_REPEATITIVE);
				UpdateHighScore("high_score.txt", score, highscore);
				Quit = true;
			}
			if (CheckEnergyColission(character, energy, currentClip_Character))
			{
				energy.SetEaten(true);
				if (mana < 6)
				{
					mana++;
				}

			}

			SDL_RenderPresent(gRenderer);

			ControlCharFrame(frame_Character);
			ControlCharFrame2(frame_Character2);
			ControlCharFrameBlast(frame_Character_Blast, character);
			ControlEnemyFrame(frame_Enemy);
			ControlEnemy2Frame(frame_Enemy2);

		}
		int realTime = fps_timer.get_ticks();
		int TimePerFrame = 1000 / FRAME_PER_SECOND;
		if (realTime < TimePerFrame)
		{
			int delayTime = TimePerFrame - realTime;
			if (delayTime >= 0)
			{
				SDL_Delay(delayTime);
			}
		}
	}

	DrawEndGameSelection(gLoseTexture, &e, gRenderer, Play_Again);
	if (!Play_Again)
	{
		enemy1.~Enemy();
		enemy2.~Enemy();
		enemy3.~Enemy();
	}
	else
	{
		for (int i = 0; i < BACKGROUND_0; ++i)
		{
			gBackgroundTexture[i].Free();
		}
		SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
		SDL_RenderClear(gRenderer);
		if (num == 4)
		{
			num = 0;
		}

		else num++;

		if (LoadMedia())
		{
			if (num == 0)
			{
				for (int i = 0; i < BACKGROUND_0; ++i)
				{
					gBackgroundTexture[i].LoadFromFile(LAYER_0[i].c_str(), gRenderer);
				}
				RenderScrollingBackground(OffsetSpeedBackground, gBackgroundTexture, num, gRenderer);
			}
			else if (num == 1)
			{
				for (int i = 0; i < BACKGROUND_1; ++i)
				{
					gBackgroundTexture[i].LoadFromFile(LAYER_1[i].c_str(), gRenderer);
				}
				RenderScrollingBackground(OffsetSpeedBackground, gBackgroundTexture, num, gRenderer);
			}
			else if (num == 2)
			{
				for (int i = 0; i < BACKGROUND_1; ++i)
				{
					gBackgroundTexture[i].LoadFromFile(LAYER_2[i].c_str(), gRenderer);
				}
				RenderScrollingBackground(OffsetSpeedBackground, gBackgroundTexture, num, gRenderer);
			}
			else if (num == 3)
			{
				for (int i = 0; i < BACKGROUND_1; ++i)
				{
					gBackgroundTexture[i].LoadFromFile(LAYER_3[i].c_str(), gRenderer);
				}
				RenderScrollingBackground(OffsetSpeedBackground, gBackgroundTexture, num, gRenderer);
			}
			else if (num == 4)
			{
				for (int i = 0; i < BACKGROUND_1; ++i)
				{
					gBackgroundTexture[i].LoadFromFile(LAYER_4[i].c_str(), gRenderer);
				}
				RenderScrollingBackground(OffsetSpeedBackground, gBackgroundTexture, num, gRenderer);
			}
		}
	}
}
void Close()
{
	gMenuTexture.Free();
	gInstructionTexture.Free();
	gCharacterTexture.Free();
	gCharacterTexture2.Free();
	gGroundTexture.Free();
	gPlayButtonTexture.Free();
	gHelpButtonTexture.Free();
	gExitButtonTexture.Free();
	gBackButtonTexture.Free();
	gPauseButtonTexture.Free();
	gContinueButtonTexture.Free();
	gLoseTexture.Free();
	gText1Texture.Free();
	gScoreTexture.Free();
	gText2Texture.Free();
	gHighScoreTexture.Free();

	for (int i = 0; i < BACKGROUND_0; ++i)
	{
		gBackgroundTexture[i].Free();
	}

	Mix_FreeMusic(gMusic);
	Mix_FreeMusic(gMenuMusic);
	Mix_FreeChunk(gClick);
	Mix_FreeChunk(gLose);
	Mix_FreeChunk(gJump);
	gMusic = nullptr;
	gMenuMusic = nullptr;
	gClick = nullptr;
	gLose = nullptr;
	gJump = nullptr;

	SDL_DestroyRenderer(gRenderer);
	gRenderer = nullptr;

	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;

	IMG_Quit();
	Mix_Quit();
	SDL_Quit();
}

