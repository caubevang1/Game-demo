#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "LTexture.h"
#include "Game_Base.h"

class Character
{
public:
	static const int JUMP_SPEED = 8;
	static const int FALL_SPEED = 8;
	Character();

	bool OnGround();

	void HandleEvent(SDL_Event& e, Mix_Chunk *gJump, int& mana, Mix_Chunk* gAttack);

	void SetCoolDown();

	bool Fight();

	void Move();

	void Render(SDL_Rect* currentClip, SDL_Renderer *gRenderer, LTexture gCharacterTexture);

	int GetPosX();

	int GetPosY();

	int GetStatus();

	void RenewStatus();

	void SetStatus(int x);

private:
	int posX, posY;
	int status;
	Uint32 lastUseTime; 
	Uint32 cooldownTime;
	bool isFightingPressed;
	int cnt ;
	Uint32 CurrentTime;
};

#endif // !CHARACTER_H_