/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_shape_shadows.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosnefr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 18:45:29 by fcosnefr          #+#    #+#             */
/*   Updated: 2016/02/07 18:45:31 by fcosnefr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

char	check_sphere_shadows(t_ray light_ray, t_list *spheres, double distance)
{
	t_list				*tmp;
	t_intersectInfo		*li;
	const double		delta = 0.01f;

	tmp = spheres;
	while (tmp)
	{
		li = sphere_intersection(((t_sphere *)tmp->data), light_ray);
		if (li && li->t > 0 && li->t < distance - delta)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

char	check_cylinder_shadows(t_ray light_ray, t_list *cylinders,
	double distance)
{
	t_list				*tmp;
	t_intersectInfo		*li;
	const double		delta = 0.01f;

	tmp = cylinders;
	while (tmp)
	{
		li = cylinder_intersection(((t_cylinder *)tmp->data), light_ray);
		if (li && li->t > 0 && li->t < distance - delta)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

char	check_cone_shadows(t_ray light_ray, t_list *cones, double distance)
{
	t_list				*tmp;
	t_intersectInfo		*li;
	const double		delta = 0.01f;

	tmp = cones;
	while (tmp)
	{
		li = cone_intersection(((t_cone *)tmp->data), light_ray);
		if (li && li->t > 0 && li->t < distance - delta)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}
