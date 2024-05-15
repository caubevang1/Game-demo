#include "Energy.h"

Energy::Energy() 
{
    srand(time(NULL));
    posX = 0;
    posY = 0;
    F_WIDTH = 0;
    F_HEIGHT = 0;
    posX = rand() % (SCREEN_WIDTH + ENERGY_POSITION_RANGE) + SCREEN_WIDTH;
    posY = rand() % (ENERGY_MAX_HEIGHT - ENERGY_MIN_HEIGHT) + ENERGY_MIN_HEIGHT;
    isEaten = false;
    EnergyTexture = nullptr;
}
Energy::~Energy()
{
    srand(time(NULL));
    posX = 0;
    posY = 0;
    F_WIDTH = 0;
    F_HEIGHT = 0;
    posX = 0;
    posY = 0;
    isEaten = false;
    EnergyTexture = nullptr;
}
void Energy::Move(const int& acceleration) {
    srand(time(NULL));
    posX += -(ENERGY_SPEED + acceleration);
    if (posX + MAX_ENERGY_WIDTH < 0) {
        isEaten = false;
        posX = rand() % (SCREEN_WIDTH + ENERGY_POSITION_RANGE) + SCREEN_WIDTH;
        posY = rand() % (290 - 360 ) + ENERGY_MIN_HEIGHT;
    }
}
void Energy::LoadFromFile(std::string path, SDL_Renderer* gRenderer)
{
    SDL_Texture* tmpTexture = nullptr;

    SDL_Surface* tmpSurface = IMG_Load(path.c_str());
    if (tmpSurface == nullptr)
    {
        LogError("Can not load image.", IMG_ERROR);
    }
    else
    {
        SDL_SetColorKey(tmpSurface, SDL_TRUE, SDL_MapRGB(tmpSurface->format, 0, 255, 255));

        tmpTexture = SDL_CreateTextureFromSurface(gRenderer, tmpSurface);
        if (tmpTexture == nullptr)
        {
            LogError("Can not create texture from surface.", SDL_ERROR);
        }
        else
        {
            F_WIDTH = tmpSurface->w;
            F_HEIGHT = tmpSurface->h;
        }

        SDL_FreeSurface(tmpSurface);
    }

    EnergyTexture = tmpTexture;
}
void Energy::Render(SDL_Renderer* gRenderer, SDL_Rect* currentClip)
{
    if (isEaten)
    {
        return;
    }
    SDL_Rect renderSpace = { posX, posY, F_WIDTH, F_HEIGHT };

    if (currentClip != nullptr)
    {
        renderSpace.w = currentClip->w;
        renderSpace.h = currentClip->h;
    }
    SDL_RenderCopy(gRenderer, EnergyTexture, currentClip, &renderSpace);
}
int Energy::GetSpeed(const int& acceleration) {
    return ENERGY_SPEED + acceleration;
}

int Energy::GetPosX() {
    return posX;
}

int Energy::GetPosY() {
    return posY;
}

int Energy::GetWidth() {
    return F_WIDTH;
}

int Energy::GetHeight() {
    return F_HEIGHT;
}
void Energy::SetEaten(bool eaten) {
    isEaten = eaten;
}
bool Energy::IsEaten() {
    return isEaten;
}