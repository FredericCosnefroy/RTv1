#include "RTv1.h"

t_intersectInfo 	*planeIntersection(t_plane *p, t_ray r)
{
	t_intersectInfo *i;
	double			t;
	double			dv;

	if (!(i = (t_intersectInfo *)malloc(sizeof(t_intersectInfo))))
		return (NULL);
	dv = DOT_PROD(p->normal, r.direction);
	if (dv == 0)
		return (NULL);
	i->t = (-(DOT_PROD(p->normal, SUB(r.origin, p->origin))) / dv);
	if (i->t < 0)
		return (NULL);
	if (dv < 0)
		i->normal = p->normal;
	else
		i->normal = NEG(p->normal);
	i->point = (ADD(r.origin, mult(r.direction, i->t)));
	i->color = p->color;
	i->brightness = 0;
	return (i);
}