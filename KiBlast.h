#pragma once
#ifndef KIBLAST_H_
#define KIBLAST_H_

#include "Game_Base.h"
#include "Character.h"
#include <vector>
#include <iostream>
#include <SDL.h>

#define KIBLAST_SPEED 20

class KiBlast {
private:
    int posX, posY; 
    int B_SPEED;    
    int B_WIDTH;    
    int B_HEIGHT;   
    bool isMove;    
    bool isHit;     
    int B_NUMBER;   
    Uint32 lastUseTime; 
    Uint32 cooldownTime; 
    SDL_Texture* KiTexture;
    bool isfired;
    Uint32 currentTime;

public:

    KiBlast();


    KiBlast(int x, int y, int speed, int width, int height, SDL_Texture* texture);
    std::vector<KiBlast> blasts;


    void HandleEvent(SDL_Event& e, Character& character, SDL_Renderer* gRenderer, int& mana, Mix_Chunk* gBlast);

    void LoadFromFile(std::string path, SDL_Renderer* gRenderer);

    void Render(SDL_Renderer* gRenderer);

    void IncreaseBlasts();

    void Move();

    void SetBlasts(int number);

    void SetHit(bool hit);

    bool IsHit();

    int GetPosX();

    int GetPosY();

    int GetWidth();

    int GetHeight();

    bool IfFired();

};

#endif // KIBLAST_H_
