#ifndef LTEXTURE_H_
#define LTEXTURE_H_

#include "Game_Base.h"

const std::string LAYER_0[BACKGROUND_0] = {
	"imgs/background/m0/10.png",
	"imgs/background/m0/9.png",
	"imgs/background/m0/8.png",
	"imgs/background/m0/7.png",
	"imgs/background/m0/6.png",
	"imgs/background/m0/5.png",
	"imgs/background/m0/4.png",
	"imgs/background/m0/3.png",
	"imgs/background/m0/2.png",
	"imgs/background/m0/1.png"
};

const std::string LAYER_1[BACKGROUND_1] = {
	"imgs/background/m1/1.png",
	"imgs/background/m1/2.png",
	"imgs/background/m1/3.png",
	"imgs/background/m1/4.png",
	"imgs/background/m1/5.png"
};

const std::string LAYER_2[BACKGROUND_1] = {
	"imgs/background/m2/1.png",
	"imgs/background/m2/2.png",
	"imgs/background/m2/3.png",
	"imgs/background/m2/4.png",
	"imgs/background/m2/5.png"
};

const std::string LAYER_3[BACKGROUND_1] = {
	"imgs/background/m3/1.png",
	"imgs/background/m3/2.png",
	"imgs/background/m3/3.png",
	"imgs/background/m3/4.png",
	"imgs/background/m3/5.png"
};

const std::string LAYER_4[BACKGROUND_1] = {
	"imgs/background/m4/1.png",
	"imgs/background/m4/2.png",
	"imgs/background/m4/3.png",
	"imgs/background/m4/4.png",
	"imgs/background/m4/5.png"
};

class LTexture
{
public:
	LTexture();

	~LTexture();

	void Free();

	bool LoadFromRenderedText(std::string textureText, TTF_Font* gFont, SDL_Color textColor, SDL_Renderer* gRenderer);

	bool LoadFromFile(std::string path, SDL_Renderer *gRenderer);

	void Render(int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip = nullptr);

	int GetWidth();

	int GetHeight();

private:
	SDL_Texture* mTexture;

	int mWidth;
	int mHeight;
};

#endif // !LTEXTURE_H_