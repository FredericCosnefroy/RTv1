#include <time.h>
#include <stdlib.h>
#include "RTv1.h"

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	SDL_Event e;
	clock_t t = clock();
	t_env env = init("RTv1");

	iterate_pixels(env, init_scene4());
	char continuer = 1;
	while (continuer)
	{
		SDL_WaitEvent(&e);
		if(e.window.event == SDL_WINDOWEVENT_CLOSE)
			continuer = 0;
		if (e.type == SDL_KEYDOWN)
			continuer = 0;
	}
	cleanup(env);
	return (0);
}
