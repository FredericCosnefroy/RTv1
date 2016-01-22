#include "RTv1.h"

static t_color		getDiffuseLight(double distance, t_light *light, t_intersectInfo * i)
{
	t_vector lightDir;
	double angle;
	double lightCoef;
	t_color c;

	lightDir = normalize(SUB(i->point, light->origin));
	angle = DOT_PROD(i->normal, NEG(lightDir));

	if (distance == 0 || angle <= 0.0)
		c = COLOR(0, 0, 0, 0);
	else
	{
		lightCoef = MIN(pow(light->range / distance, 2), 1);
		c = COLOR(	i->color.r * angle * lightCoef,
					i->color.g * angle * lightCoef,
					i->color.b * angle * lightCoef,
					i->color.s);
	}
	return (c);
}

static double		getSpecularValue(t_light *light, t_intersectInfo *o, t_ray ray, double distance)
{
	t_vector	lightDir;
	t_vector	phongDir;
	double		phongTerm;
	double		lambert;
	double		reflect;

	lightDir = normalize(SUB(o->point, light->origin));
	lambert = (DOT_PROD(NEG(lightDir), o->normal));
	reflect = lambert * 2.0f;
	phongDir = SUB(NEG(lightDir), mult(o->normal, reflect));
	phongTerm = MAX(DOT_PROD(phongDir, ray.direction), 0.0f);
	phongTerm = pow(phongTerm, distance * 1.0f) * 0.75;
	return (phongTerm * 1);
}


t_color				getPixelColor(t_scene *scene, t_intersectInfo *o, t_ray ray)
{
	double distance;
	t_color output = COLOR(0, 0, 0, 0);
	char shadowed;

	if (!o)
		return (COLOR(0.01, 0.01, 0.01, 0));
	if (!scene->light)
		return (o->color);
	distance = DIST(scene->light->origin, o->point);
	shadowed = 0;
	if (!shadowRayTrace(scene, distance, o))
		shadowed = 1;
	output = COLOR_ADD(output, getDiffuseLight(distance, scene->light, o));
	if (!shadowed && o->color.s)
		output = COLOR_ADDV(output, getSpecularValue(scene->light, o, ray, distance));
	if (shadowed)
		output = COLOR_DIV(output, 2);
	return (COLOR_PAD(output));
}