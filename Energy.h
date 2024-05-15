#pragma once
#include "Game_Base.h"
#include "LTexture.h"
#define ENERGY_MAX_HEIGHT 300
#define ENERGY_MIN_HEIGHT 330
#define ENERGY_POSITION_RANGE 250
#define ENERGY_SPEED 7
#define MAX_ENERGY_WIDTH 100

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

