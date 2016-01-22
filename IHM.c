#include "RTv1.h"

static unsigned int g_current_scene = 0;

static t_scene *(*g_scenes[])(void) =
{
	&init_scene1,
	&init_scene2,
	&init_scene3,
	&init_scene4,
	&init_scene5,
	&init_scene6,
	&init_scene7,
	&init_scene8,
	&init_scene9,
};

int		key_hook(int keycode, void *params)
{
	t_env *env;

	env = (t_env *)params;
	if (keycode == KEY_ESC)
		exit(0);
	if (keycode == KEY_RIGHT)
	{
		g_current_scene = ((g_current_scene == MAX_SCENES - 1) ? g_current_scene : g_current_scene + 1);
		iterate_pixels(*env, g_scenes[g_current_scene]());
	}
	if (keycode == KEY_LEFT)
	{
		g_current_scene = ((g_current_scene == 0) ? 0 : g_current_scene - 1);
		iterate_pixels(*env, g_scenes[g_current_scene]());
	}
	return (0);
}

int		expose_hook(void *params)
{
	t_env *env;

	env = (t_env *)params;
	iterate_pixels(*env, g_scenes[g_current_scene]());
	printf("explose_hook\n");
	return (0);
}

t_env		win_init()
{
	t_env	e;

	e.mlx = mlx_init();
	e.win = mlx_new_window(e.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "RTv1");
	mlx_key_hook(e.win, key_hook, &e);
	mlx_expose_hook(e.win, expose_hook, &e);
	mlx_loop(e.mlx);
	return (e);
}

