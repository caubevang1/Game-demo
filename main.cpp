#include "Header.h"

int main(int argc, char* argv[])
{
	if (!Init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
			if (!LoadMedia())
			{
				printf("Failed to load media!\n");
			}
			else
			{
				Mix_PlayMusic(gMenuMusic, IS_REPEATITIVE);
				while (!Quit_Menu)
				{
					SDL_Event e_mouse;
					while (SDL_PollEvent(&e_mouse) != 0)
					{
						if (e_mouse.type == SDL_QUIT)
						{
							Quit_Menu = true;
						}

						bool Quit_Game = false;
						HandlePlayButton(&e_mouse, PlayButton, Quit_Menu, Play_Again, gClick);

						HandleHelpButton(&e_mouse, gBackButton,
							HelpButton, BackButton,
							gInstructionTexture, gBackButtonTexture,
							gRenderer, Quit_Game, gClick);

						HandleExitButton(&e_mouse, ExitButton, Quit_Menu, gClick);

						if (Quit_Game == true)
						{
							return 0;
						}
					}

					gMenuTexture.Render(0, 0, gRenderer);

					SDL_Rect* currentClip_Play = &gPlayButton[PlayButton.currentSprite];
					PlayButton.Render(currentClip_Play, gRenderer, gPlayButtonTexture);

					SDL_Rect* currentClip_Help = &gHelpButton[HelpButton.currentSprite];
					HelpButton.Render(currentClip_Help, gRenderer, gHelpButtonTexture);

					SDL_Rect* currentClip_Exit = &gExitButton[ExitButton.currentSprite];
					ExitButton.Render(currentClip_Exit, gRenderer, gExitButtonTexture);

					SDL_RenderPresent(gRenderer);
				}

				while (Play_Again)
				{
					PlayAgain();				
				}
			}
		Close();
		return 0;
	}
}


