#pragma once
#include "Game_Base.h"
#include "LTexture.h"

class Bar
{
private:
    int posX;
    int posY;
    int F_WIDTH;
    int F_HEIGHT;
    SDL_Texture* BarTexture;
public:
    Bar();
    ~Bar();

    void LoadFromFile(std::string path, SDL_Renderer* gRenderer);

    void Render(SDL_Renderer* gRenderer, SDL_Rect* currentClip);

    int GetPosX();

    int GetPosY();

    int GetWidth();

    int GetHeight();

};
