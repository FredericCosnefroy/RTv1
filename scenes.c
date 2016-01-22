#include "RTv1.h"

t_scene		*init_scene1(void)
{
	t_scene		*scene;
	const t_color red = COLOR(1, 0, 0, 0);

	scene = createScene(createCamera(VEC(0, 0, -50)), NULL);

	ADD_SPHERE(SPHERE(VEC(0, 0, 3), 5, red));
	return (scene);
}

t_scene		*init_scene2(void)
{
	t_scene		*scene;
	const t_color red = COLOR(1, 0, 0, 0);
	const t_color blue = COLOR(0, 0, 1, 0);

	//scene = createScene(createCamera(VEC(0, 0, -50)), NULL);
	scene = createScene(createCamera(VEC(0, 0, -50)), createLight(VEC(0, 0, -20), 100));

	ADD_SPHERE(SPHERE(VEC(0, 0, 3), 5, red));
	ADD_PLANE(PLANE(VEC(0, 1, 0), VEC(0, 5, 0), blue));
	ADD_PLANE(PLANE(VEC(0, 0, 1), VEC(0, 0, 250), blue));
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
	ADD_CYLINDER(CYLINDER(VEC(0, 10, 18), VEC(1, 0, 1), 2, pink));
	ADD_CONE(CONE(VEC(0, 0, 25), VEC(0, 1, 0), 30, gold));
	ADD_PLANE(PLANE(VEC(0, 1, 0), VEC(0, 20, 0), green));
	ADD_PLANE(PLANE(VEC(0, 0, 1), VEC(0, 0, 50), blue));
	return (scene);
}

t_scene		*init_scene4(void)
{
	t_scene		*scene;
	const t_color red = COLOR(1, 0, 0, 1);
	const t_color violet = COLOR(1, 0.3, 1, 1);
	const t_color green = COLOR(1, 1, 0, 0);
	const t_color blue = COLOR(0.29, 0.59, 0.82, 1);
	const t_color gold = COLOR(0.99, 0.76, 0, 1);
	const t_color pink = COLOR(0.9, 0.23, 0.63, 1);
	int i = 1;
	int j;
	int k;

	scene = createScene(createCamera(VEC(-10, -15, -10)), createLight(VEC(15, -10, -20), 2000));
//	ADD_SPHERE(createSphere(VEC(6, 0, 3), 5, red));
//	ADD_SPHERE(createSphere(VEC(-15, 15, 20), 5, violet));
//	ADD_SPHERE(createSphere(VEC(7, -3, 12), 5, green));
	while (i < 4)
	{
		j = 1;
		while (j < 4)
		{
			ADD_CYLINDER(CYLINDER(VEC(0, i * (-1), j * (1)), VEC(1, 0, 0), 0.025, blue));
			ADD_CYLINDER(CYLINDER(VEC(i * (-1), 0, j * (1)), VEC(0, 1, 0), 0.025, blue));
			ADD_CYLINDER(CYLINDER(VEC(i * (-1), j * (-1), 0), VEC(0, 0, 1), 0.025, blue));
			
			j++;
		}

		i++;
	}


			//	ADD_CYLINDER(CYLINDER(VEC(0, 0, 1), VEC(0, 0, 1), 0.1, pink));
			//	ADD_CYLINDER(CYLINDER(VEC(5, 0, 0), VEC(1, 0, 0), 0.1, pink));
			//	ADD_CYLINDER(CYLINDER(VEC(0, 5, 0), VEC(0, 1, 0), 0.1, pink));
			//	ADD_CYLINDER(CYLINDER(VEC(0, 0, 5), VEC(0, 0, 1), 0.1, pink));
//	ADD_CYLINDER(CYLINDER(VEC(0, 10, 18), VEC(1, 0, 1), 2, pink));
//	ADD_CONE(CONE(VEC(0, 0, 25), VEC(0, 1, 0), 30, gold));
//	ADD_PLANE(PLANE(VEC(0, 1, 0), VEC(0, 20, 0), green));
//	ADD_PLANE(PLANE(VEC(0, 0, 1), VEC(0, 0, 50), blue));
	return (scene);
}