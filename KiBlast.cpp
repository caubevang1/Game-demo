#include "KiBlast.h"

KiBlast::KiBlast()
{
    posX = -200; 
    posY = -200; 
    B_SPEED = 10;
    B_WIDTH = 0; 
    B_HEIGHT = 0;
    isMove = true;
    isHit = false;
    B_NUMBER = 0;
    lastUseTime = 0;
    cooldownTime = 2000;
    KiTexture = nullptr;
    isfired = false;
}

KiBlast::KiBlast(int x, int y, int speed, int width, int height, SDL_Texture* texture)
{
    posX = x;
    posY = y;
    B_SPEED = 10;
    B_WIDTH = width;
    B_HEIGHT = height;
    isMove = true;
    isHit = false;
    B_NUMBER = 0;
    lastUseTime = 0;
    cooldownTime = 2000;
    KiTexture = texture;
    isfired = false;
}

void KiBlast::HandleEvent(SDL_Event& e, Character& character, SDL_Renderer* gRenderer, int& mana, Mix_Chunk* gBlast) {
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
        case SDLK_SPACE:
            Uint32 currentTime = SDL_GetTicks();
            if (B_NUMBER > 0 && (currentTime - lastUseTime >= cooldownTime) && mana >= 2) {
                Mix_PlayChannel(MIX_CHANNEL, gBlast, NOT_REPEATITIVE);
                lastUseTime = currentTime;
                B_NUMBER--; 
                character.SetStatus(BLAST);
                mana -= 2;
                isfired = true;
                SDL_Texture* newTexture = KiTexture;
                blasts.push_back(KiBlast(character.GetPosX() + 20, character.GetPosY() + 5, B_SPEED, B_WIDTH, B_HEIGHT, newTexture));
            }
            break;
        }
    }
}

void KiBlast::LoadFromFile(std::string path, SDL_Renderer* gRenderer) {
    SDL_Surface* tmpSurface = IMG_Load(path.c_str());
    if (tmpSurface == nullptr) {
        std::cout << "Can not load image: " << IMG_GetError() << std::endl;
    }
    else {
        SDL_SetColorKey(tmpSurface, SDL_TRUE, SDL_MapRGB(tmpSurface->format, 0, 255, 255));
        KiTexture = SDL_CreateTextureFromSurface(gRenderer, tmpSurface);
        if (KiTexture == nullptr) {
            std::cout << "Can not create texture from surface: " << SDL_GetError() << std::endl;
        }
        else {
            B_WIDTH = tmpSurface->w;
            B_HEIGHT = tmpSurface->h;
        }
        SDL_FreeSurface(tmpSurface);
    }
}

void KiBlast::Render(SDL_Renderer* gRenderer) {
    for (auto& blast : blasts) {
        SDL_Rect renderSpace = { blast.posX, blast.posY, blast.B_WIDTH, blast.B_HEIGHT };
        SDL_RenderCopy(gRenderer, blast.KiTexture, NULL, &renderSpace);
    }
}


void KiBlast::IncreaseBlasts() {
    B_NUMBER++;
}

void KiBlast::Move() {
    std::vector<KiBlast> activeBlasts;
    if (isfired)
    {
        for (auto& blast : blasts) {
            if (blast.posX < SCREEN_WIDTH) 
            {
                blast.posX += blast.B_SPEED;
                activeBlasts.push_back(blast);
             
            }
            else
            {
                blast.posX = 0;
                isfired = false;
            }
        }
        blasts = activeBlasts; 
    }
}

void KiBlast::SetBlasts(int number) {
    B_NUMBER = number;
}
void KiBlast::SetHit(bool hit) {
    isHit = hit;
}

bool KiBlast::IsHit() {
    return isHit;
}

int KiBlast::GetPosX() {
    return posX;
}

int KiBlast::GetPosY() {
    return posY;
}

int KiBlast::GetWidth() {
    return B_WIDTH;
}

int KiBlast::GetHeight() {
    return B_HEIGHT;
}

bool KiBlast::IfFired() {
    return isfired;
}
