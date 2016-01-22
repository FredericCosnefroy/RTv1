#include "RTv1.h"

static t_intersectInfo	*endInt(t_cone *cone, t_ray r, t_intersectInfo *i)
{
	t_vector	X;
	double		m;

	i->color = cone->color;
	i->point = (ADD(r.origin, mult(r.direction, i->t)));
	X = SUB(r.origin, cone->origin);
	m = DOT_PROD(r.direction, cone->direction) * i->t + 
				DOT_PROD(X, cone->direction);
	i->normal = normalize(SUB(SUB(i->point, cone->origin),
				mult(cone->direction, (1 + pow(cone->half_angle, 2)) * m)));
	return (i);
}

t_intersectInfo 		*coneIntersection(t_cone *cone, t_ray r)
{
	t_intersectInfo *i;
	t_vector X;
	double A;
	double B;
	double C;
	
	if (!(i = (t_intersectInfo *)malloc(sizeof(t_intersectInfo))))
		return (NULL);
	X = SUB(r.origin, cone->origin);
	A = SQR(r.direction) - (1 + pow(cone->half_angle, 2)) *
			pow(DOT_PROD(r.direction, cone->direction), 2);
	B = 2 * (DOT_PROD(r.direction, X) - (1 + pow(cone->half_angle, 2)) *
			DOT_PROD(r.direction, cone->direction) *
			DOT_PROD(X, cone->direction));
	C = SQR(X) - (1 + pow(cone->half_angle, 2)) *
			pow(DOT_PROD(X, cone->direction), 2);
	if (!find_roots(A, B, C, &(i->t)))
		return (NULL);

	return (endInt(cone, r, i));
}