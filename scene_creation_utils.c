#include "RTv1.h"

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
	*scene = SCENE(camera, light);
	return (scene);
}