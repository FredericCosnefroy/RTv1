/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosnefr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 19:04:25 by fcosnefr          #+#    #+#             */
/*   Updated: 2016/02/07 19:04:26 by fcosnefr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_intersectInfo		*sphere_intersection(t_sphere *s, t_ray r)
{
	t_intersectInfo *i;
	double			a;
	double			b;
	double			c;
	t_vector		x;

	if (!(i = (t_intersectInfo *)malloc(sizeof(t_intersectInfo))))
		return (NULL);
	x = SUB(r.origin, s->center);
	a = 0;
	b = DOT_PROD(x, r.direction);
	c = SQR(x) - (s->radius * s->radius);
	if (!find_roots(a, b, c, &(i->t)))
		return (NULL);
	i->point = (ADD(r.origin, mult(r.direction, i->t)));
	i->normal = normalize(mult((SUB(i->point, s->center)), (1 / s->radius)));
	i->color = s->color;
	return (i);
}
