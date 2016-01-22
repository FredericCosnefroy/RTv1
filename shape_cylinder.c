#include "RTv1.h"

static t_intersectInfo	*endInt(t_cylinder *cylinder, t_ray r, t_intersectInfo *i)
{
	t_vector	X;
	double		m;

	i->color = cylinder->color;
	i->point = (ADD(r.origin, mult(r.direction, i->t)));
	X = SUB(r.origin, cylinder->origin);
	m = DOT_PROD(r.direction, cylinder->direction) *
		i->t + DOT_PROD(X, cylinder->direction);
	i->normal = normalize(SUB(SUB(i->point, cylinder->origin),
		mult(cylinder->direction, m)));
	return (i);
}

t_intersectInfo			*project2DCylinder(t_cylinder *cylinder, t_ray r, t_intersectInfo *i)
{
	double 			A;
	double 			B;
	double 			C;
	
	A = SQR(r.direction);
	B = 2 * (DOT_PROD(r.direction, r.origin) -
			DOT_PROD(r.direction, cylinder->origin));
	C = SQR(r.origin) + SQR(cylinder->origin) - 2 *
		(DOT_PROD(r.origin, cylinder->origin)) -
		(cylinder->radius * cylinder->radius);
	if (!find_roots(A, B, C, &(i->t)))
		return (NULL);
	return (i);
}

t_intersectInfo			*cylinderIntersection(t_cylinder *cylinder, t_ray r)
{
	t_intersectInfo *i;
	t_vector 		nRayOrigin;
	t_vector 		nRayDirection;
	t_cylinder		nCylinder;
	t_ray 			nRay;

	if(!(i = (t_intersectInfo *)malloc(sizeof(t_intersectInfo))))
		return (NULL);
	nRayOrigin = SUB(r.origin,
		mult(cylinder->direction, DOT_PROD(r.origin, cylinder->direction)));
	nRayDirection = SUB(r.direction, mult(cylinder->direction,
		DOT_PROD(r.direction, cylinder->direction)));
	nCylinder = CYLINDER(SUB(cylinder->origin,
		mult(cylinder->direction,
		DOT_PROD(cylinder->origin,cylinder->direction))),
		cylinder->direction, cylinder->radius, cylinder->color);
	nRay = RAY(nRayOrigin, nRayDirection);
	if (!(project2DCylinder(&(nCylinder), nRay, i)))
		return (NULL);
	return (endInt(cylinder, r, i));
}
