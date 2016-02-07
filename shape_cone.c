/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosnefr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 19:03:54 by fcosnefr          #+#    #+#             */
/*   Updated: 2016/02/07 19:03:56 by fcosnefr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

static t_intersectInfo	*end_int(t_cone *cone, t_ray r, t_intersectInfo *i)
{
	t_vector	x;
	double		m;

	i->color = cone->color;
	i->point = (ADD(r.origin, mult(r.direction, i->t)));
	x = SUB(r.origin, cone->origin);
	m = DOT_PROD(r.direction, cone->direction) * i->t +
				DOT_PROD(x, cone->direction);
	i->normal = normalize(SUB(SUB(i->point, cone->origin),
				mult(cone->direction, (1 + pow(cone->half_angle, 2)) * m)));
	return (i);
}

t_intersectInfo			*cone_intersection(t_cone *cone, t_ray r)
{
	t_intersectInfo	*i;
	t_vector		x;
	double			a;
	double			b;
	double			c;

	if (!(i = (t_intersectInfo *)malloc(sizeof(t_intersectInfo))))
		return (NULL);
	x = SUB(r.origin, cone->origin);
	a = SQR(r.direction) - (1 + pow(cone->half_angle, 2)) *
			pow(DOT_PROD(r.direction, cone->direction), 2);
	b = 2 * (DOT_PROD(r.direction, x) - (1 + pow(cone->half_angle, 2)) *
			DOT_PROD(r.direction, cone->direction) *
			DOT_PROD(x, cone->direction));
	c = SQR(x) - (1 + pow(cone->half_angle, 2)) *
			pow(DOT_PROD(x, cone->direction), 2);
	if (!find_roots(a, b, c, &(i->t)))
		return (NULL);
	return (end_int(cone, r, i));
}
