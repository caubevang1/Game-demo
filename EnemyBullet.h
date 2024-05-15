#pragma once
#include "Game_Base.h"
#include "Enemy.h"

#define EnemyBullet_SPEED 20

class EnemyBullet {
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

    EnemyBullet();

    EnemyBullet(int x, int y, int speed, int width, int height, SDL_Texture* texture);

    std::vector<EnemyBullet> bullets;

    void Fire(int startX, int startY);

    void LoadFromFile(std::string path, SDL_Renderer* gRenderer);

    void Render(SDL_Renderer* gRenderer);

    void Increasebullets();

    void Move(const int& acceleration);

    void Setbullets(int number);

    void SetHit(bool hit);

    bool IsHit();

    int GetPosX();

    int GetPosY();

    int GetWidth();

    int GetHeight();

    bool IfFired();

};