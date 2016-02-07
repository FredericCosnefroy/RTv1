/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scenes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosnefr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 19:04:05 by fcosnefr          #+#    #+#             */
/*   Updated: 2016/02/07 19:04:06 by fcosnefr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_scene		*init_scene1(void)
{
	t_scene		*scene;

	scene = createScene(createCamera(VEC(0, 0, -50)));

	ADD_SPHERE(SPHERE(VEC(0, 0, 3), 5, RED));
	ADD_PLANE(PLANE(VEC(0, 1, 0), VEC(0, 5, 0), BLUE));
	return (scene);
}

t_scene		*init_scene2(void)
{
	t_scene		*scene;

	scene = createScene(createCamera(VEC(0, 0, -50)));

	addLight(scene, VEC(10, -5, -50), 1000);
	ADD_SPHERE(SPHERE(VEC(0, 0, 3), 5, RED));
	ADD_PLANE(PLANE(VEC(0, 1, 0), VEC(0, 5, 0), BLUE));
	return (scene);
}

t_scene		*init_scene3(void)
{
	t_scene		*scene;

	scene = createScene(createCamera(VEC(0, 0, -50)));

	addLight(scene, VEC(10, -5, -50), 1000);
	ADD_SPHERE(SPHERE(VEC(0, 0, 3), 5, S_RED));
	ADD_PLANE(PLANE(VEC(0, 1, 0), VEC(0, 5, 0), BLUE));
	return (scene);
}

t_scene		*init_scene4(void)
{
	t_scene		*scene;

	scene = createScene(createCamera(VEC(40, -20, 50)));
	addLight(scene, VEC(-5, -5, -50), 1000);
	ADD_SPHERE(SPHERE(VEC(0, 0, 3), 5, S_RED));
	ADD_PLANE(PLANE(VEC(0, 1, 0), VEC(0, 5, 0), BLUE));
	return (scene);
}


t_scene		*init_scene5(void)
{
	t_scene		*scene;

	scene = createScene(createCamera(VEC(0, 0, -100)));

	addLight(scene, VEC(25, 0, -50), 1000);
	addLight(scene, VEC(-25, 0, -50), 1000);

	ADD_CONE(CONE(VEC(0, 0, 0), VEC(0, 1, 0), 30, S_YELLOW));
	ADD_CYLINDER(CYLINDER(VEC(25, 0, 25), VEC(0, 1, 0), 4, S_PINK));
	ADD_CYLINDER(CYLINDER(VEC(25, 0, -25), VEC(0, 1, 0), 4, S_PINK));
	ADD_CYLINDER(CYLINDER(VEC(-25, 0, 25), VEC(0, 1, 0), 4, S_PINK));
	ADD_CYLINDER(CYLINDER(VEC(-25, 0, -25), VEC(0, 1, 0), 4, S_PINK));
	ADD_PLANE(PLANE(VEC(0, 1, 0), VEC(0, 30, 0), GREEN));
	ADD_PLANE(PLANE(VEC(0, 0, 1), VEC(0, 0, 50), BLUE));
	ADD_PLANE(PLANE(VEC(0, 1, 0), VEC(0, -30, 0), GREEN));
	return (scene);
}

t_scene		*init_scene6(void)
{
	t_scene		*scene;

	scene = createScene(createCamera(VEC(0, 0, -100)));
	addLight(scene, VEC(-7, -20, -30), 1000);

	ADD_SPHERE(SPHERE(VEC(10, -5, 3), 6, S_RED));
	ADD_SPHERE(SPHERE(VEC(5, 12, 17), 4, S_PURPLE));
	ADD_SPHERE(SPHERE(VEC(-7, -20, -10), 3, S_CYAN));
	ADD_SPHERE(SPHERE(VEC(-12, 7, -16), 7, S_GREEN));
	ADD_PLANE(PLANE(VEC(0, 1, 0), VEC(0, -30, 0), CYAN));
	ADD_PLANE(PLANE(VEC(0, 1, 0), VEC(0, 30, 0), GREEN));
	ADD_PLANE(PLANE(VEC(1, 0, 0), VEC(-30, 0, 0), PINK));
	ADD_PLANE(PLANE(VEC(1, 0, 0), VEC(30, 0, 0), YELLOW));
	ADD_PLANE(PLANE(VEC(0, 0, 1), VEC(0, 0, 50), BLUE));
	return (scene);
}

t_scene		*init_scene7(void)
{
	t_scene		*scene;

	scene = createScene(createCamera(VEC(10, 10, -30)));
	ADD_SPHERE(SPHERE(VEC(10, -5, 3), 6, S_RED));
	addLight(scene, VEC(-5, -5, -50), 1000);
	ADD_CYLINDER(CYLINDER(VEC(0, 10, 18), VEC(1, 0, 1), 2, S_PINK));
	ADD_CONE(CONE(VEC(0, 0, 25), VEC(0, 1, 0), 30, S_YELLOW));
	ADD_PLANE(PLANE(VEC(0, 1, 0), VEC(0, 20, 0), GREEN));
	ADD_PLANE(PLANE(VEC(0, 0, 1), VEC(0, 0, 50), BLUE));
	return (scene);
}

t_scene		*init_scene8(void)
{
	t_scene		*scene;

	scene = createScene(createCamera(VEC(0, 0, -100)));
	addLight(scene, VEC(-5, -5, -50), 1000);
	ADD_CYLINDER(CYLINDER(VEC(0, 10, 18), VEC(1, 0, 1), 2, S_PINK));
	ADD_CONE(CONE(VEC(0, 0, 25), VEC(0, 1, 0), 30, S_YELLOW));
	ADD_PLANE(PLANE(VEC(0, 1, 0), VEC(0, 20, 0), GREEN));
	ADD_PLANE(PLANE(VEC(0, 0, 1), VEC(0, 0, 50), BLUE));
	return (scene);
}

t_scene		*init_scene9(void)
{
	t_scene		*scene;
	int 		i;

	scene = createScene(createCamera(VEC(0, 0, -100)));
	addLight(scene, VEC(0, 0, -50), 1000);
	i = 0;
	while (i < 8)
	{
		ADD_SPHERE(SPHERE(VEC(-35 + i * 10, 0, 3), 4, S_RANDOM));
		i++;
	}
	ADD_PLANE(PLANE(VEC(0, 0, 1), VEC(0, 0, 50), BLUE));
	return (scene);
}
