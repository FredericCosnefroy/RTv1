/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosnefr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 19:04:15 by fcosnefr          #+#    #+#             */
/*   Updated: 2016/02/07 19:04:17 by fcosnefr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

static t_intersectInfo	*end_int(t_cylinder *cylinder, t_ray r,
	t_intersectInfo *i)
{
	t_vector	x;
	double		m;

	i->color = cylinder->color;
	i->point = (ADD(r.origin, mult(r.direction, i->t)));
	x = SUB(r.origin, cylinder->origin);
	m = DOT_PROD(r.direction, cylinder->direction) *
		i->t + DOT_PROD(x, cylinder->direction);
	i->normal = normalize(SUB(SUB(i->point, cylinder->origin),
		mult(cylinder->direction, m)));
	return (i);
}

t_intersectInfo			*project_2d_cylinder(t_cylinder *cylinder, t_ray r,
	t_intersectInfo *i)
{
	double		a;
	double		b;
	double		c;

	a = SQR(r.direction);
	b = 2 * (DOT_PROD(r.direction, r.origin) -
			DOT_PROD(r.direction, cylinder->origin));
	c = SQR(r.origin) + SQR(cylinder->origin) - 2 *
		(DOT_PROD(r.origin, cylinder->origin)) -
		(cylinder->radius * cylinder->radius);
	if (!find_roots(a, b, c, &(i->t)))
		return (NULL);
	return (i);
}

t_intersectInfo			*cylinder_intersection(t_cylinder *cylinder, t_ray r)
{
	t_intersectInfo *i;
	t_vector		nray_origin;
	t_vector		nray_direction;
	t_cylinder		ncylinder;
	t_ray			nray;

	if (!(i = (t_intersectInfo *)malloc(sizeof(t_intersectInfo))))
		return (NULL);
	nray_origin = SUB(r.origin,
		mult(cylinder->direction, DOT_PROD(r.origin, cylinder->direction)));
	nray_direction = SUB(r.direction, mult(cylinder->direction,
		DOT_PROD(r.direction, cylinder->direction)));
	ncylinder = CYLINDER(SUB(cylinder->origin,
		mult(cylinder->direction,
		DOT_PROD(cylinder->origin, cylinder->direction))),
		cylinder->direction, cylinder->radius, cylinder->color);
	nray = RAY(nray_origin, nray_direction);
	if (!(project_2d_cylinder(&(ncylinder), nray, i)))
		return (NULL);
	return (end_int(cylinder, r, i));
}
