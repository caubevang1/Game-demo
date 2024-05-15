#pragma once
#ifndef SOUND_H
#define SOUND_H

#include "Game_Base.h"

bool LoadSound(Mix_Music** gMusic,
Mix_Music** gMenuMusic,
Mix_Chunk** gClick,
Mix_Chunk** gJump ,
Mix_Chunk** gLose);

#endif // !SOUND_H

