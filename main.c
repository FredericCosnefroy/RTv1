#include <time.h>
#include <limits.h>
#include <stdlib.h>
#include "RTv1.h"

t_list			*lstnew(const void *data, unsigned int size)
{
	t_list			*lst;

	if (!(lst = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	lst->data = (void*)data;
	lst->size = (data == NULL) ? 0 : size;
	lst->next = NULL;
	return (lst);
}

t_list			*lstadd(t_list **lst, const void *data, unsigned int size)
{
	t_list *node;
	t_list *tmp;

	node = lstnew(data, size);
	if (!node || !lst)
		return (NULL);
	if (!*lst)
	{
		*lst = node;
		return (*lst);
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
	return (*lst);
}

t_env init(char *title)
{
	t_env env;

	env.screen = SDL_CreateWindow(title,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
	env.renderer = SDL_CreateRenderer(env.screen, -1, SDL_RENDERER_PRESENTVSYNC);
	if (env.screen == NULL || env.renderer == NULL)
	{
		printf("Impossible d'initialiser le mode écran à %d x %d: %s\n", SCREEN_WIDTH, 
				SCREEN_HEIGHT, SDL_GetError());
		exit(1);
	}
	return (env);
}

void cleanup(t_env env)
{
	SDL_DestroyRenderer(env.renderer);
	env.renderer = NULL;
	SDL_DestroyWindow(env.screen);
	env.screen = NULL;
	SDL_Quit();
}

t_vector mult(t_vector v, double val)
{
	return (VEC((v.x * val), (v.y * val), (v.z * val)));
}

t_vector	normalize(t_vector const v)
{
	const double magnitude = sqrt(SQR(v));

	return (VEC(v.x / magnitude, v.y / magnitude, v.z / magnitude));
}

t_intersectInfo		*cylinderIntersection(t_cylinder *cy, t_ray r)
{
	t_intersectInfo * i = (t_intersectInfo *)malloc(sizeof(t_intersectInfo));
	t_vector newCyOrigin = SUB(cy->origin, mult(cy->direction, DOT_PROD(cy->origin, cy->direction)));
	double delta, t1, t2;
	t_cylinder newCylinder = CYLINDER(newCyOrigin, cy->direction, cy->radius, cy->color);
	t_vector newRayOrigin = SUB(r.origin, mult(cy->direction, DOT_PROD(r.origin, cy->direction)));
	t_vector newRayDirection = SUB(r.direction, mult(cy->direction, DOT_PROD(r.direction, cy->direction)));
	t_ray newRay = RAY(newRayOrigin, newRayDirection);
	double A = SQR(newRay.direction);
	double B = 2 * (DOT_PROD(newRay.direction, newRay.origin) - DOT_PROD(newRay.direction, newCyOrigin));
	double C = SQR(newRayOrigin) + SQR(newCyOrigin) - 2 * (DOT_PROD(newRayOrigin, newCyOrigin)) - cy->radius * cy->radius;

	delta = ((B * B) - (4 * A * C));
	if (delta < 0.0f)
		return (0);
	if (delta != 0)
	{
		delta = (double)sqrt(delta);
		t1 = (-B + delta) / (2 * A);;
		t2 = (-B - delta) / (2 * A);;
		if (t1 < t2)
			i->t = t1;
		else
			i->t = t2;
	}
	else
		i->t = (-B) / (2 * A);
	i->color = cy->color;
	i->point = (ADD(r.origin, mult(r.direction, i->t)));
	t_vector dP = SUB(r.origin, cy->origin);
	double m = DOT_PROD(r.direction, cy->direction) * i->t + DOT_PROD(dP, cy->direction);
	i->normal = normalize(SUB(SUB(i->point, cy->origin), mult(cy->direction, m)));
	return (i);
}

t_intersectInfo * coneIntersection(t_cone * co, t_ray r)
{
	t_intersectInfo * i = (t_intersectInfo *)malloc(sizeof(t_intersectInfo));
	double A, B, C;
	double delta;
	double t1, t2;
	t_vector X = SUB(r.origin, co->origin);

	A = SQR(r.direction) - (1 + pow(co->half_angle, 2)) * pow(DOT_PROD(r.direction, co->direction), 2);
	B = 2 * (DOT_PROD(r.direction, X) - (1 + pow(co->half_angle, 2)) * DOT_PROD(r.direction, co->direction) * DOT_PROD(X, co->direction));
	C = SQR(X) - (1 + pow(co->half_angle, 2)) * pow(DOT_PROD(X, co->direction), 2);
	delta = ((B * B) - (4 * A * C));
	if (delta < 0.0f)
		return (0);
	if (delta != 0)
	{
		delta = (double)sqrt(delta);
		t1 = (-B + delta) / (2 * A);;
		t2 = (-B - delta) / (2 * A);;
		if (t1 < t2)
			i->t = t1;
		else
			i->t = t2;
	}
	else
		i->t = (-B) / (2 * A);
	i->color = co->color;
	i->point = (ADD(r.origin, mult(r.direction, i->t)));
	double m = DOT_PROD(r.direction, co->direction) * i->t + DOT_PROD(X, co->direction);
	i->normal = normalize(SUB(SUB(i->point, co->origin), mult(co->direction, (1 + pow(co->half_angle, 2)) * m)));
	return (i);
}

t_intersectInfo * sphereIntersection(t_sphere * s, t_ray r)
{
	t_intersectInfo * i;
	float b, c;
	float delta;
	float t1, t2;
	float direction;
	t_vector intersect;
	t_vector tmpNormal;

	t_vector rayOrg = SUB(r.origin, s->center);

	i = (t_intersectInfo *)malloc(sizeof(t_intersectInfo));
	b = DOT_PROD(rayOrg, r.direction);
	c = SQR(rayOrg) - (s->radius * s->radius);

	delta = ((b * b) - c);

	if (delta < 0.0f) 
		return (0);
	if (delta != 0)
	{
		delta = (double)sqrt(delta);
		t1 = (-b + delta); if (t1 < 0) return (0);
		t2 = (-b - delta); if (t2 < 0) return (0);

		if (t1 < t2)
			i->t = t1;
		else
			i->t = t2;
	}
	else
		i->t = -b;
	i->point = (ADD(r.origin, mult(r.direction, i->t)));
	i->normal = normalize(mult((SUB(i->point, s->center)), (1 / s->radius)));
	i->color = s->color;
	return (i);
}

t_intersectInfo * planeIntersection(t_plane *p, t_ray r)
{
	t_intersectInfo * i;
	float t;
	float dv;

	i = (t_intersectInfo *)malloc(sizeof(t_intersectInfo));
	dv = DOT_PROD(p->normal, r.direction);

	if (dv == 0)
		return (0);
	i->t = (-(DOT_PROD(p->normal, SUB(r.origin, p->origin))) / dv);
	if (i->t < 0)
		return (0);
	if (dv < 0)
		i->normal = p->normal;
	else
		i->normal = NEG(p->normal);
	i->point = (ADD(r.origin, mult(r.direction, i->t)));
	i->color = p->color;
	i->brightness = 0;
	return (i);
}

t_color		getDiffuseLight(double distance, t_light *light, t_intersectInfo * i)
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

char		traceShadowRay(t_scene *scene, const double distance, t_intersectInfo *i)
{
	t_list				*tmp;
	t_intersectInfo		*li;
	t_ray				lightRay;
	const double delta = 0.01f;

	lightRay = RAY	(
						scene->light->origin,
						normalize(SUB(i->point, scene->light->origin))
					);
	tmp = scene->planes;
	while (tmp)
	{
		li = planeIntersection(((t_plane *)tmp->data), lightRay);
		if (li && li->t > 0 && li->t < distance - delta)
			return (0);
		tmp = tmp->next;
	}
	tmp = scene->spheres;
	while (tmp)
	{
		li = sphereIntersection(((t_sphere *)tmp->data), lightRay);
		if (li && li->t > 0 && li->t < distance - delta)
			return (0);
		tmp = tmp->next;
	}
	tmp = scene->cylinders;
	while (tmp)
	{
		li = cylinderIntersection(((t_cylinder *)tmp->data), lightRay);
		if (li && li->t > 0 && li->t < distance - delta)
			return (0);
		tmp = tmp->next;
	}
	tmp = scene->cones;
	while (tmp)
	{
		li = coneIntersection(((t_cone *)tmp->data), lightRay);
		if (li && li->t > 0 && li->t < distance - delta)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

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

double		getSpecularValue(t_light *light, t_intersectInfo *o, t_ray ray, double distance)
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

t_color		getPixelColor(t_scene *scene, t_intersectInfo *o, t_ray ray)
{
	const double distance = DIST(scene->light->origin, o->point);
	t_color output = COLOR(0, 0, 0, 0);
	char shadowed;

	if (!o)
		return (COLOR(0.01, 0.01, 0.01, 0));
	if (!scene->light)
		return (o->color);
	shadowed = 0;
	if (!traceShadowRay(scene, distance, o))
		shadowed = 1;
	output = COLOR_ADD(output, getDiffuseLight(distance, scene->light, o));
	if (!shadowed && o->color.s)
		output = COLOR_ADDV(output, getSpecularValue(scene->light, o, ray, distance));
	if (shadowed)
		output = COLOR_DIV(output, 2);
	return (COLOR_PAD(output));
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

t_camera	*createCamera(t_vector position)
{
	t_camera	*camera;

	camera = (t_camera *)malloc(sizeof(t_camera));
	camera->campos = position;
	camera->camdir = normalize(NEG(SUB(camera->campos, D_VEC)));
	camera->camright = normalize(CROSS_PROD(Y_VEC, camera->camdir));
	camera->camdown = CROSS_PROD(camera->camright, camera->camdir);
	return (camera);
}

t_light		*createLight(t_vector position, int radius)
{
	t_light		*light;

	light = (t_light *)malloc(sizeof(t_light));
	*light = LIGHT(position, radius);
	return (light);
}

t_scene		*createScene(t_camera *camera, t_light *light)
{
	t_scene		*scene;

	scene = (t_scene *)malloc(sizeof(t_scene));
	*scene = NEW_SCENE(camera, light, NULL, NULL, NULL, NULL);
	return (scene);
}

t_plane * createPlane(t_vector normal, t_vector origin, t_color color)
{
	t_plane		*plane;

	plane = malloc(sizeof(t_plane));
	*plane = PLANE(normal, origin, color);
	return (plane);
}

t_sphere * createSphere(t_vector center, double radius, t_color color)
{
	t_sphere		*sphere;

	sphere = malloc(sizeof(t_sphere));
	*sphere = SPHERE(center, radius, color);
	return (sphere);
}

t_cylinder * createCylinder(t_vector origin, t_vector direction, double radius, t_color color)
{
	t_cylinder		*cylinder;

	cylinder = malloc(sizeof(t_cylinder));
	*cylinder = CYLINDER(origin, direction, radius, color);
	return (cylinder);
}

t_cone * createCone(t_vector origin, t_vector direction, double half_angle, t_color color)
{
	t_cone		*cone;

	cone = malloc(sizeof(t_cone));
	*cone = CONE(origin, direction, half_angle, color);
	return (cone);
}

t_scene		*init_scene1(void)
{
	t_scene		*scene;
	const t_color red = COLOR(1, 0, 0, 0);

	scene = createScene(createCamera(VEC(0, 0, -50)), NULL);

	ADD_SPHERE(createSphere(VEC(0, 0, 3), 5, red));
	return (scene);
}

t_scene		*init_scene2(void)
{
	t_scene		*scene;
	const t_color red = COLOR(1, 0, 0, 0);
	const t_color blue = COLOR(0, 0, 1, 0);

	//scene = createScene(createCamera(VEC(0, 0, -50)), NULL);
	scene = createScene(createCamera(VEC(0, 0, -50)), createLight(VEC(0, 0, -20), 100));

	ADD_SPHERE(createSphere(VEC(0, 0, 3), 5, red));
	ADD_PLANE(createPlane(VEC(0, 1, 0), VEC(0, 5, 0), blue));
	ADD_PLANE(createPlane(VEC(0, 0, 1), VEC(0, 0, 250), blue));
	return (scene);
}

t_scene		*init_scene3(void)
{
	t_scene		*scene;
	const t_color red = COLOR(1, 0, 0, 1);
	const t_color violet = COLOR(1, 0.3, 1, 1);
	const t_color green = COLOR(1, 1, 0, 0);
	const t_color blue = COLOR(0.29, 0.59, 0.82, 0);
	const t_color gold = COLOR(0.99, 0.76, 0, 1);
	const t_color pink = COLOR(0.9, 0.23, 0.63, 1);

	scene = createScene(createCamera(VEC(0, 0, -100)), createLight(VEC(15, -10, -20), 2000));

//	ADD_SPHERE(createSphere(VEC(6, 0, 3), 5, red));
//	ADD_SPHERE(createSphere(VEC(-15, 15, 20), 5, violet));
//	ADD_SPHERE(createSphere(VEC(7, -3, 12), 5, green));
	ADD_CYLINDER(createCylinder(VEC(0, 10, 18), VEC(1, 0, 1), 2, pink));
//	ADD_CONE(createCone(VEC(0, 0, 25), VEC(1, 1, -1), 0.3, gold));
	ADD_PLANE(createPlane(VEC(0, 1, 0), VEC(0, 20, 0), green));
	ADD_PLANE(createPlane(VEC(0, 0, 1), VEC(0, 0, 50), blue));
	return (scene);
}

t_ray	getRay(t_camera *camera, int x, int y)
{
	t_vector	initDir;
	t_vector	dir;
	double		xamnt;
	double		yamnt;

	xamnt = (x + 0.5) / SCREEN_WIDTH;
	yamnt = ((SCREEN_HEIGHT - y) + 0.5) / SCREEN_HEIGHT;
	initDir = ADD(mult(camera->camright, xamnt - 0.5),
					mult(camera->camdown, yamnt - 0.5));
	dir = normalize(ADD(camera->camdir, initDir));
	return (RAY(camera->campos, dir));
}

void	iterate_pixels(t_env env, t_scene *scene)
{
	t_color		color;
	int			x;
	int			y;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		y = 0;
		while (y < SCREEN_HEIGHT)
		{
			color = rayTrace(scene, getRay(scene->camera, x, y));
			SDL_SetRenderDrawColor(env.renderer, 255 * color.r, 255 * color.g, 255 * color.b, 0);
			SDL_RenderDrawPoint(env.renderer, x, y);
			y++;
		}
		x++;
	}
	SDL_RenderPresent(env.renderer);
}

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	SDL_Event e;
	clock_t t = clock();
	t_env env = init("RTv1");

	iterate_pixels(env, init_scene3());
	char continuer = 1;
	while (continuer)
	{
		SDL_WaitEvent(&e);
		if(e.window.event == SDL_WINDOWEVENT_CLOSE)
			continuer = 0;
		if (e.type == SDL_KEYDOWN)
			continuer = 0;
	}
	cleanup(env);
	printf("%lf %d", ((double)(clock() - t)) / CLOCKS_PER_SEC, CLOCKS_PER_SEC);
	return (0);
}
