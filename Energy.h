#pragma once
#include "Game_Base.h"
#include "LTexture.h"


class Energy 
{
private:
    int posX;
    int posY;
    int F_WIDTH;
    int F_HEIGHT;
    bool isEaten;
    SDL_Texture* EnergyTexture;
public:
    Energy();
    ~Energy();

    void Move(const int& acceleration);

    void LoadFromFile(std::string path, SDL_Renderer* gRenderer);
    
    void Render(SDL_Renderer* gRenderer, SDL_Rect* currentClip);
   
    int GetSpeed(const int& acceleration);

    int GetPosX();

    int GetPosY();

    int GetWidth();

    int GetHeight();

    void SetEaten(bool eaten);

    bool IsEaten();
};

