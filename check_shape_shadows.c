#include "RTv1.h"

char	checkSphereShadows(t_ray lightRay, t_list *spheres, double distance)
{
	t_list				*tmp;
	t_intersectInfo		*li;
	const double delta = 0.01f;

	tmp = spheres;
	while (tmp)
	{
		li = sphereIntersection(((t_sphere *)tmp->data), lightRay);
		if (li && li->t > 0 && li->t < distance - delta)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

char	checkCylinderShadows(t_ray lightRay, t_list *cylinders, double distance)
{
	t_list				*tmp;
	t_intersectInfo		*li;
	const double delta = 0.01f;

	tmp = cylinders;
	while (tmp)
	{
		li = cylinderIntersection(((t_cylinder *)tmp->data), lightRay);
		if (li && li->t > 0 && li->t < distance - delta)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

char	checkConeShadows(t_ray lightRay, t_list *cones, double distance)
{
	t_list				*tmp;
	t_intersectInfo		*li;
	const double delta = 0.01f;

	tmp = cones;
	while (tmp)
	{
		li = coneIntersection(((t_cone *)tmp->data), lightRay);
		if (li && li->t > 0 && li->t < distance - delta)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}
