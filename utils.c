/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosnefr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 19:04:33 by fcosnefr          #+#    #+#             */
/*   Updated: 2016/02/07 19:04:35 by fcosnefr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

double		ttan(double angle)
{
	return (tan(angle * PI / 180));
}

t_vector	mult(t_vector v, double val)
{
	return (VEC((v.x * val), (v.y * val), (v.z * val)));
}

t_vector	normalize(t_vector const v)
{
	const double magnitude = sqrt(SQR(v));

	return (VEC(v.x / magnitude, v.y / magnitude, v.z / magnitude));
}

char		find_roots(double a, double b, double c, double *t)
{
	double denominator;
	double delta;
	double t1;
	double t2;

	delta = ((a == 0) ? ((b * b) - c) : ((b * b) - (4 * a * c)));
	denominator = ((a == 0) ? 1 : (2 * a));
	if (delta < 0.0f)
		return (0);
	if (delta != 0)
	{
		delta = (double)sqrt(delta);
		*t = MIN((-b + delta) / denominator, (-b - delta) / denominator);
	}
	else
	{
		*t = (-b) / (2 * a);
	}
	return (1);
}
