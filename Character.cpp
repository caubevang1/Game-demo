#include "Character.h"

Character::Character()
{
	posX = SCREEN_WIDTH - 700;
	posY = GROUND;
	status = 0;
	lastUseTime = 0;
	cooldownTime = 2000;
	isFightingPressed = false;
	cnt = 0;
	CurrentTime = 0;
}

bool Character::OnGround()
{
	return posY == GROUND;
}


void Character::HandleEvent(SDL_Event& e, Mix_Chunk *gJump, int& mana, Mix_Chunk* gAttack)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
			case SDLK_UP:
			{
				if (OnGround())
				{
					Mix_PlayChannel(MIX_CHANNEL, gJump, NOT_REPEATITIVE);
					status = JUMP;
				}
				break;
			}
			case SDLK_DOWN:
			{			
				if (!OnGround())
				{
					status = FAST;
				} 
				break;
			}
			case SDLK_BACKSPACE:
			{
				if (OnGround() && mana > 0)
				{
					if ( cnt == 0) 
					{
						Mix_PlayChannel(MIX_CHANNEL, gAttack, NOT_REPEATITIVE);
						CurrentTime = SDL_GetTicks();
						status = FIGHT;						
						cnt = 20;
						mana--;
					}
					
				}
				break;
			}
					
		}
	}
	if (e.type == SDL_KEYUP && status == FIGHT )
	{
		status = 0;
	}
	if (e.type == SDL_KEYUP && status == BLAST)
	{
		if (!OnGround())
		{
			status = FALL;
		}
		else status = 0;
	}
	
}

void Character::SetCoolDown()
{
	if (cnt > 0)
	{
		cnt--;
	}
	
}
bool Character::Fight() 
{
	return status == FIGHT;
}
void Character::Move()
{
	if (status == FIGHT && SDL_GetTicks() - CurrentTime >= 400)
	{
		status = 0;
	}
	if (status == JUMP && posY >= MAX_HEIGHT)
	{
		posY -= JUMP_SPEED;
		if (posY <= MAX_HEIGHT) {  
			status = FALL;
		}
	}
	else if (status == FALL && posY < GROUND)
	{
		posY += FALL_SPEED;
		if (posY >= GROUND) {  
			posY = GROUND;
			status = 0;  
		}
	}
	else if (status == FAST && posY < GROUND)  
	{
		posY += 3 * FALL_SPEED;
		if (posY >= GROUND) {
			posY = GROUND;
			status = 0;
		}
	}
}


void Character::Render(SDL_Rect* currentClip, SDL_Renderer *gRenderer, LTexture gCharacterTexture)
{	
	gCharacterTexture.Render(posX, posY , gRenderer, currentClip);
	
}
int Character::GetPosX()
{
	return posX;
}

int Character::GetPosY()
{
	return posY;
}

 int Character::GetStatus()
{
	return status;
}

 void Character::RenewStatus()
 {
	 posY = GROUND;
	 status = 0;
 }

 void Character::SetStatus(int x)
 {
	 status = x;
 }
