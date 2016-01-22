#include "RTv1.h"

t_intersectInfo 	*sphereIntersection(t_sphere * s, t_ray r)
{
	t_intersectInfo *i;
	double A;
	double B;
	double C;
	t_vector X;

	if (!(i = (t_intersectInfo *)malloc(sizeof(t_intersectInfo))))
		return (NULL);
	X = SUB(r.origin, s->center);
	A = 0;
	B = DOT_PROD(X, r.direction);
	C = SQR(X) - (s->radius * s->radius);
	if (!find_roots(A, B, C, &(i->t)))
		return (NULL);
	i->point = (ADD(r.origin, mult(r.direction, i->t)));
	i->normal = normalize(mult((SUB(i->point, s->center)), (1 / s->radius)));
	i->color = s->color;
	return (i);
}