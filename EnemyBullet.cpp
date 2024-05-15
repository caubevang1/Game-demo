#include "EnemyBullet.h"

EnemyBullet::EnemyBullet()
{
    posX = -200;
    posY = -200;
    B_SPEED = 10;
    B_WIDTH = 0;
    B_HEIGHT = 0;
    isMove = true;
    isHit = false;
    B_NUMBER = 20;
    lastUseTime = 0;
    cooldownTime = 2000;
    KiTexture = nullptr;
    isfired = false;
}

EnemyBullet::EnemyBullet(int x, int y, int speed, int width, int height, SDL_Texture* texture)
{
    posX = x;
    posY = y;
    B_SPEED = speed;
    B_WIDTH = width;
    B_HEIGHT = height;
    isMove = true;
    isHit = false;
    B_NUMBER = 2; 
    lastUseTime = 0;
    cooldownTime = 2000;
    KiTexture = texture;
    isfired = false;
}

void EnemyBullet::Fire(int startX, int startY) {
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime > lastUseTime + cooldownTime && B_NUMBER > 0) {
        bullets.push_back(EnemyBullet(startX, startY, B_SPEED, B_WIDTH, B_HEIGHT, KiTexture));
        lastUseTime = currentTime;
    }
}

void EnemyBullet::LoadFromFile(std::string path, SDL_Renderer* gRenderer) {
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

void EnemyBullet::Render(SDL_Renderer* gRenderer) {
    for (auto& bullet : bullets) {
        SDL_Rect renderSpace = { bullet.posX, bullet.posY, bullet.B_WIDTH, bullet.B_HEIGHT };
        SDL_RenderCopy(gRenderer, bullet.KiTexture, NULL, &renderSpace);
    }
}

void EnemyBullet::Increasebullets() {
    B_NUMBER++;
}


void EnemyBullet::Move(const int& acceleration) {
    std::vector<EnemyBullet> activeBullets;
    for (auto& bullet : bullets) {
        bullet.posX -= bullet.B_SPEED + acceleration;
        if (bullet.posX < SCREEN_WIDTH) {  
            activeBullets.push_back(bullet);
        }
    }
    bullets = activeBullets; 
}


void EnemyBullet::Setbullets(int number) {
    B_NUMBER = number;
}

void EnemyBullet::SetHit(bool hit) {
    isHit = hit;
}

bool EnemyBullet::IsHit() {
    return isHit;
}

int EnemyBullet::GetPosX() {
    return posX;
}

int EnemyBullet::GetPosY() {
    return posY;
}

int EnemyBullet::GetWidth() {
    return B_WIDTH;
}

int EnemyBullet::GetHeight() {
    return B_HEIGHT;
}

bool EnemyBullet::IfFired() {
    return isfired;
}
