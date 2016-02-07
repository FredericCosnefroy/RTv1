/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosnefr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 18:59:03 by fcosnefr          #+#    #+#             */
/*   Updated: 2016/02/07 18:59:05 by fcosnefr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

char	shadow_raytrace(t_scene *scene, t_light *light, double distance,
	t_intersectInfo *i)
{
	t_list				*tmp;
	t_intersectInfo		*li;
	t_ray				light_ray;

	light_ray = RAY(light->origin, normalize((SUB(i->point, light->origin))));
	if (!(check_sphere_shadows(light_ray, scene->spheres, distance)))
		return (0);
	if (!(check_cylinder_shadows(light_ray, scene->cylinders, distance)))
		return (0);
	if (!(check_cone_shadows(light_ray, scene->cones, distance)))
		return (0);
	return (1);
}

t_color	raytrace(t_scene *scene, t_ray ray)
{
	t_color			pixel_color;
	t_intersectInfo	*o;
	t_list			*tmp;
	double			max;

	o = NULL;
	max = INT_MAX;
	check_planes(ray, scene->planes, &o, &max);
	check_spheres(ray, scene->spheres, &o, &max);
	check_cylinders(ray, scene->cylinders, &o, &max);
	check_cones(ray, scene->cones, &o, &max);
	pixel_color = get_pixel_color(scene, o, ray);
	return (pixel_color);
}
