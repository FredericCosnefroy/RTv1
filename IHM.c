#include "RTv1.h"

t_env init(char *title)
{
	t_env env;

	env.screen = SDL_CreateWindow(title,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
	env.renderer = SDL_CreateRenderer(env.screen, -1, SDL_RENDERER_PRESENTVSYNC);
	if (env.screen == NULL || env.renderer == NULL)
	{
		printf("Impossible d'initialiser le mode écran à %d x %d: %s\n", SCREEN_WIDTH, 
				SCREEN_HEIGHT, SDL_GetError());
		exit(1);
	}
	return (env);
}

void cleanup(t_env env)
{
	SDL_DestroyRenderer(env.renderer);
	env.renderer = NULL;
	SDL_DestroyWindow(env.screen);
	env.screen = NULL;
	SDL_Quit();
}
