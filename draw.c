#include "RTv1.h"

static t_ray	getRay(t_camera *camera, int x, int y)
{
	t_vector	initDir;
	t_vector	dir;
	double		xamnt;
	double		yamnt;

	xamnt = (x + 0.5) / SCREEN_WIDTH;
	yamnt = ((SCREEN_HEIGHT - y) + 0.5) / SCREEN_HEIGHT;
	initDir = ADD(mult(camera->camright, xamnt - 0.5),
					mult(camera->camdown, yamnt - 0.5));
	dir = normalize(ADD(camera->camdir, initDir));
	return (RAY(camera->campos, dir));
}

void			iterate_pixels(t_env env, t_scene *scene)
{
	t_color		color;
	int			x;
	int			y;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		y = 0;
		while (y < SCREEN_HEIGHT)
		{
			color = rayTrace(scene, getRay(scene->camera, x, y));
			mlx_pixel_put(env.mlx, env.win, x, y,
				((int)(255 * color.r) << 16) | ((int)(255 * color.g) << 8) | ((int)(255 * color.b)));
			y++;
		}
		x++;
	}
}
