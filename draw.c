/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosnefr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 18:48:21 by fcosnefr          #+#    #+#             */
/*   Updated: 2016/02/07 18:48:23 by fcosnefr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

static t_ray	get_ray(t_camera *camera, int x, int y)
{
	t_vector	init_dir;
	t_vector	dir;
	double		xamnt;
	double		yamnt;

	xamnt = (x + 0.5) / SCREEN_WIDTH;
	yamnt = ((SCREEN_HEIGHT - y) + 0.5) / SCREEN_HEIGHT;
	init_dir = ADD(mult(camera->camright, xamnt - 0.5),
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
				((int)(255 * color.r) << 16) |
				((int)(255 * color.g) << 8) |
				((int)(255 * color.b)));
			y++;
		}
		x++;
	}
}
