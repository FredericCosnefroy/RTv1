/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosnefr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 18:55:31 by fcosnefr          #+#    #+#             */
/*   Updated: 2016/02/07 18:55:32 by fcosnefr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

static double	get_diffuse_coeff(double distance, t_light *light,
	t_intersectInfo *o)
{
	t_vector	light_dir;
	double		angle;

	light_dir = normalize(SUB(o->point, light->origin));
	angle = DOT_PROD(o->normal, NEG(light_dir));
	if (distance == 0 || angle <= 0)
		return (0);
	return (angle);
}

static double	get_max_diffuse_coeff(t_list *lights, t_intersectInfo *o)
{
	double	corr_light_coeff;
	double	max_light_coeff;
	double	distance;

	max_light_coeff = 0;
	while (lights)
	{
		distance = DIST(((t_light *)lights->data)->origin, o->point);
		corr_light_coeff = get_diffuse_coeff(distance, lights->data, o);
		if (corr_light_coeff > max_light_coeff)
			max_light_coeff = corr_light_coeff;
		lights = lights->next;
	}
	return (max_light_coeff);
}

static char		get_shadow_coeff(t_scene *scene, t_intersectInfo *o)
{
	t_list	*lights;
	char	shadows;
	double	distance;

	shadows = 0;
	lights = scene->lights;
	while (lights)
	{
		distance = DIST(((t_light *)lights->data)->origin, o->point);
		if (!shadowRayTrace(scene, lights->data, distance, o))
			shadows++;
		lights = lights->next;
	}
	return (shadows);
}

static double	get_specular_coeff(t_light *light, t_intersectInfo *o,
	t_ray ray, double distance)
{
	t_vector	light_dir;
	t_vector	phongDir;
	double		phongTerm;
	double		lambert;
	double		reflect;

	light_dir = normalize(SUB(o->point, light->origin));
	lambert = (DOT_PROD(NEG(light_dir), o->normal));
	reflect = lambert * 2.0f;
	phongDir = SUB(NEG(light_dir), mult(o->normal, reflect));
	phongTerm = MAX(DOT_PROD(phongDir, ray.direction), 0.0f);
	phongTerm = pow(phongTerm, distance * 1.0f) * 0.75;
	return (phongTerm);
}

t_color			get_pixel_color(t_scene *scene, t_intersectInfo *o, t_ray ray)
{
	t_list	*lights;
	double	distance;
	t_color	output;

	if (!o)
		return (COLOR(0.01, 0.01, 0.01, 0));
	if (!scene->lights)
		return (o->color);
	switch(get_shadow_coeff(scene, o))
	{
		case 0 : output = o->color; break;
		case 1 : output = COLOR_DIV(o->color, 1.5); break;
		case 2 : output = COLOR_DIV(o->color, 3); break;
		default : break;
	}
/*	if (get_shadow_coeff(scene, o))
		output = COLOR_DIV(o->color, 1.5 * get_shadow_coeff(scene, o));
	else
		output = o->color;*/
	output = COLOR_MUL(output, get_max_diffuse_coeff(scene->lights, o));
	lights = scene->lights;
	while (lights)
	{
		distance = DIST(((t_light *)lights->data)->origin, o->point);
		if (o->color.s)
			output = COLOR_ADDV(output, get_specular_coeff(lights->data, o, ray,
				distance));
		lights = lights->next;
	}
	return (COLOR_PAD(output));
}
