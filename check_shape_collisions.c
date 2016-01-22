#include "RTv1.h"

void checkPlanes(t_ray ray, t_list *planes, t_intersectInfo **o, double *max)
{
	t_intersectInfo *i;

	while (planes)
	{
		i = planeIntersection(((t_plane *)planes->data), ray);
		if (i && i->t > 0 && i->t < *max)
		{
			*max = i->t;
			free(*o);
			*o = i;
		}
		else
			free(i);
		planes = planes->next;
	}
}

void checkSpheres(t_ray ray, t_list *spheres, t_intersectInfo **o, double *max)
{
	t_intersectInfo *i;

	while (spheres)
	{
		i = sphereIntersection(((t_sphere *)spheres->data), ray);
		if (i && i->t > 0 && i->t < *max)
		{
			*max = i->t;
			free(*o);
			*o = i;
		}
		else
			free(i);
		spheres = spheres->next;
	}
}
void checkCylinders(t_ray ray, t_list *cylinders, t_intersectInfo **o, double *max)
{
	t_intersectInfo *i;

	while (cylinders)
	{
		i = cylinderIntersection(((t_cylinder *)cylinders->data), ray);
		if (i && i->t > 0 && i->t < *max)
		{
			*max = i->t;
			free(*o);
			*o = i;
		}
		else
			free(i);
		cylinders = cylinders->next;
	}
}
void checkCones(t_ray ray, t_list *cones, t_intersectInfo **o, double *max)
{
	t_intersectInfo *i;

	while (cones)
	{
		i = coneIntersection(((t_cone *)cones->data), ray);
		if (i && i->t > 0 && i->t < *max)
		{
			*max = i->t;
			free(*o);
			*o = i;
		}
		else
			free(i);
		cones = cones->next;
	}
}