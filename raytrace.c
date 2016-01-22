#include "RTv1.h"


char	shadowRayTrace(t_scene *scene, double distance, t_intersectInfo *i)
{
	t_list				*tmp;
	t_intersectInfo		*li;
	t_ray				lightRay;
	
	lightRay = RAY	(
						scene->light->origin,
						normalize(SUB(i->point, scene->light->origin))
					);
	if (!(checkSphereShadows(lightRay, scene->spheres, distance)))
		return (0);
	if (!(checkCylinderShadows(lightRay, scene->cylinders, distance)))
		return (0);
	if (!(checkConeShadows(lightRay, scene->cones, distance)))
		return (0);
	return (1);
}

t_color		rayTrace(t_scene *scene, t_ray ray)
{
	t_color			pixelColor;
	t_intersectInfo	*o;
	t_list			*tmp;
	double			max;

	o = NULL;
	max = INT_MAX;
	checkPlanes(ray, scene->planes, &o, &max);
	checkSpheres(ray, scene->spheres, &o, &max);
	checkCylinders(ray, scene->cylinders, &o, &max);
	checkCones(ray, scene->cones, &o, &max);
	pixelColor = getPixelColor(scene, o, ray);
	return (pixelColor);
}
