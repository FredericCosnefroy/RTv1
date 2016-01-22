#include "RTv1.h"

static const t_color 	g_colors[] =
{
	COLOR(1, 0, 0, 0),
	COLOR(0, 1, 0, 0),
	COLOR(0, 0, 1, 0),
	COLOR(0.99, 0.76, 0, 0),
	COLOR(1, 0.3, 1, 0),
	COLOR(0.9, 0.23, 0.63, 0),
	COLOR(0.29, 0.59, 0.82, 0),
	COLOR(1, 0, 0, 1),
	COLOR(0, 1, 0, 1),
	COLOR(0, 0, 1, 1),
	COLOR(0.99, 0.76, 0, 1),
	COLOR(1, 0.3, 1, 1),
	COLOR(0.9, 0.23, 0.63, 1),
	COLOR(0.29, 0.59, 0.82, 1)
};

t_scene		*init_scene1(void)
{
	t_scene		*scene;

	scene = createScene(createCamera(VEC(0, 0, -50)), NULL);

	ADD_SPHERE(SPHERE(VEC(0, 0, 3), 5, RED));
	ADD_PLANE(PLANE(VEC(0, 1, 0), VEC(0, 5, 0), BLUE));
	return (scene);
}

t_scene		*init_scene2(void)
{
	t_scene		*scene;

	scene = createScene(createCamera(VEC(0, 0, -50)), createLight(VEC(5, -10, -20), 100));

	ADD_SPHERE(SPHERE(VEC(0, 0, 3), 5, RED));
	ADD_PLANE(PLANE(VEC(0, 1, 0), VEC(0, 5, 0), BLUE));
	return (scene);
}

t_scene		*init_scene3(void)
{
	t_scene		*scene;

	scene = createScene(createCamera(VEC(0, 0, -50)), createLight(VEC(5, -10, -20), 100));

	ADD_SPHERE(SPHERE(VEC(0, 0, 3), 5, S_RED));
	ADD_PLANE(PLANE(VEC(0, 1, 0), VEC(0, 5, 0), BLUE));
	return (scene);
}

t_scene		*init_scene4(void)
{
	t_scene		*scene;

	scene = createScene(createCamera(VEC(40, -20, 50)), createLight(VEC(5, -10, -20), 100));

	ADD_SPHERE(SPHERE(VEC(0, 0, 3), 5, S_RED));
	ADD_PLANE(PLANE(VEC(0, 1, 0), VEC(0, 5, 0), BLUE));
	return (scene);
}


t_scene		*init_scene5(void)
{
	t_scene		*scene;

	scene = createScene(createCamera(VEC(0, 0, -100)), createLight(VEC(15, 0, -10), 2000));

	ADD_SPHERE(SPHERE(VEC(10, -5, 3), 6, S_RED));
	ADD_CYLINDER(CYLINDER(VEC(0, 10, 18), VEC(1, 0, 1), 2, S_PINK));
	ADD_CONE(CONE(VEC(0, 0, 25), VEC(0, 1, 0), 30, S_YELLOW));
	ADD_PLANE(PLANE(VEC(0, 1, 0), VEC(0, 20, 0), GREEN));
	ADD_PLANE(PLANE(VEC(0, 0, 1), VEC(0, 0, 50), BLUE));
	return (scene);
}

t_scene		*init_scene6(void)
{
	t_scene		*scene;

	scene = createScene(createCamera(VEC(-30, -20, -40)), createLight(VEC(15, 0, -10), 2000));
	ADD_SPHERE(SPHERE(VEC(10, -5, 3), 6, S_RED));
	ADD_CYLINDER(CYLINDER(VEC(0, 10, 18), VEC(1, 0, 1), 2, S_PINK));
	ADD_CONE(CONE(VEC(0, 0, 25), VEC(0, 1, 0), 30, S_YELLOW));
	ADD_PLANE(PLANE(VEC(0, 1, 0), VEC(0, 20, 0), GREEN));
	ADD_PLANE(PLANE(VEC(0, 0, 1), VEC(0, 0, 50), BLUE));
	return (scene);
}

t_scene		*init_scene7(void)
{
	t_scene		*scene;

	scene = createScene(createCamera(VEC(40, -15, -70)), createLight(VEC(15, 0, -10), 2000));
	ADD_SPHERE(SPHERE(VEC(10, -5, 3), 6, S_RED));
	ADD_CYLINDER(CYLINDER(VEC(0, 10, 18), VEC(1, 0, 1), 2, S_PINK));
	ADD_CONE(CONE(VEC(0, 0, 25), VEC(0, 1, 0), 30, S_YELLOW));
	ADD_PLANE(PLANE(VEC(0, 1, 0), VEC(0, 20, 0), GREEN));
	ADD_PLANE(PLANE(VEC(0, 0, 1), VEC(0, 0, 50), BLUE));
	return (scene);
}

t_scene		*init_scene8(void)
{
	t_scene		*scene;

	scene = createScene(createCamera(VEC(10, 10, -30)), createLight(VEC(15, 0, -10), 2000));
	ADD_SPHERE(SPHERE(VEC(10, -5, 3), 6, S_RED));
	ADD_CYLINDER(CYLINDER(VEC(0, 10, 18), VEC(1, 0, 1), 2, S_PINK));
	ADD_CONE(CONE(VEC(0, 0, 25), VEC(0, 1, 0), 30, S_YELLOW));
	ADD_PLANE(PLANE(VEC(0, 1, 0), VEC(0, 20, 0), GREEN));
	ADD_PLANE(PLANE(VEC(0, 0, 1), VEC(0, 0, 50), BLUE));
	return (scene);
}

t_scene		*init_scene9(void)
{
	t_scene		*scene;

	scene = createScene(createCamera(VEC(0, 0, -100)), createLight(VEC(15, -10, -20), 35));

	ADD_CYLINDER(CYLINDER(VEC(0, 10, 18), VEC(1, 0, 1), 2, S_PINK));
	ADD_CONE(CONE(VEC(0, 0, 25), VEC(0, 1, 0), 30, S_YELLOW));
	ADD_PLANE(PLANE(VEC(0, 1, 0), VEC(0, 20, 0), GREEN));
	ADD_PLANE(PLANE(VEC(0, 0, 1), VEC(0, 0, 50), BLUE));
	return (scene);
}