/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_creation_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosnefr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 19:03:04 by fcosnefr          #+#    #+#             */
/*   Updated: 2016/02/07 19:03:06 by fcosnefr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_camera	*create_camera(t_vector position)
{
	t_camera	*camera;

	camera = (t_camera *)malloc(sizeof(t_camera));
	camera->campos = position;
	camera->camdir = normalize(NEG(SUB(camera->campos, D_VEC)));
	camera->camright = normalize(CROSS_PROD(Y_VEC, camera->camdir));
	camera->camdown = CROSS_PROD(camera->camright, camera->camdir);
	return (camera);
}

void		add_light(t_scene *scene, t_vector position, int radius)
{
	lstadd(&scene->lights, &LIGHT(position, radius), sizeof(t_light));
}

t_scene		*create_scene(t_camera *camera)
{
	t_scene		*scene;

	scene = (t_scene *)malloc(sizeof(t_scene));
	*scene = SCENE(camera);
	return (scene);
}
