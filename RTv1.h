/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RTv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosnefr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 19:15:58 by fcosnefr          #+#    #+#             */
/*   Updated: 2016/02/07 19:27:12 by fcosnefr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <stdio.h>
# include <math.h>
# include <limits.h>
# include "./mlx/mlx.h"
# include <unistd.h>
# include <stdlib.h>

# define KEY_ESC				53
# define KEY_LEFT				123
# define KEY_RIGHT				124

# define ONE					83
# define NINE					91

# define RED					COLOR(1, 0, 0, 0)
# define GREEN					COLOR(0, 1, 0, 0)
# define BLUE					COLOR(0, 0, 1, 0)
# define YELLOW					COLOR(0.99, 0.76, 0, 0)
# define PURPLE					COLOR(1, 0.3, 1, 0)
# define PINK					COLOR(0.9, 0.23, 0.63, 0)
# define CYAN					COLOR(0.29, 0.59, 0.82, 0)
# define RANDOM					COLOR((double)(rand() % 100) / 100,\
		(double)(rand() % 100) / 100, (double)(rand() % 100) / 100, 0)

# define S_RED					COLOR(1, 0, 0, 1)
# define S_GREEN				COLOR(0, 1, 0, 1)
# define S_BLUE					COLOR(0, 0, 1, 1)
# define S_YELLOW				COLOR(0.99, 0.76, 0, 1)
# define S_PURPLE				COLOR(1, 0.3, 1, 1)
# define S_PINK					COLOR(0.9, 0.23, 0.63, 1)
# define S_CYAN					COLOR(0.29, 0.59, 0.82, 1)
# define S_RANDOM				COLOR((double)(rand() % 100) / 100,\
		(double)(rand() % 100) / 100, (double)(rand() % 100) / 100, 1)

# define MAX_SCENES				9

# define INVSQRTF(x)			(1.0f / sqrtf(x))

# define MIN(x, y)				(x < y ? x : y)
# define MAX(x, y)				(x > y ? x : y)

# define SCREEN_HEIGHT			800
# define SCREEN_WIDTH			800
# define FOV					60

# define PI 					3.14159265

# define X_VEC					((t_vector){1, 0, 0})
# define Y_VEC					((t_vector){0, 1, 0})
# define Z_VEC					((t_vector){0, 0, 1})
# define D_VEC					((t_vector){0, 0 ,0})

# define VEC(x, y, z)			((t_vector){x, y, z})

# define MAG(v)					sqrt(v.x * v.x + v.y * v.y + v.z + v.z)
# define NEG(v)					(VEC(-v.x, -v.y, -v.z))
# define DOT_PROD(v1, v2)		((v1.x * v2.x) +	\
								(v1.y * v2.y) +		\
								(v1.z * v2.z))		\
# define CROSS_PROD(v1, v2)		(VEC(								\
									v1.y * v2.z - v1.z * v2.y,		\
									v1.z * v2.x - v1.x * v2.z,		\
									v1.x * v2.y - v1.y * v2.x)		\
								)
# define ADD(v1, v2)			(VEC(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z))
# define MUL(v, val)			(VEC(v.x * val, v.y * val, v.z * val))
# define SUB(v1, v2)			(VEC(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z))
# define SUBV(v1, val)			(VEC(v1.x - val, v1.y - val, v1.z - val))
# define SQR(v)					v.x * v.x + v.y * v.y + v.z * v.z
# define DIST(p1, p2)			(sqrt(pow(p2.x - p1.x, 2) +			\
									pow(p2.y - p1.y, 2) +			\
									pow(p2.z - p1.z, 2)))			\
# define DEFAULT_RAY			((t_ray){D_VEC, X_VEC})
# define RAY(ori, dir)			((t_ray){ori, dir})

# define CAM(pos, dir, right, down)	((t_camera) {pos, dir, right, down})

# define COLOR(r, g, b, s)		((t_color){r, g, b, s})

# define LIGHT(o, c)			((t_light){o, c})

# define SCENE(c)				((t_scene){c, NULL, NULL, NULL, NULL, NULL})

# define SPHERE(v, r, c)		((t_sphere){v, r, c})

# define PLANE(n, o, c)			((t_plane){normalize(n), o, c})

# define CONE(o, d, h, c)		((t_cone){o, d, ttan(h), c})

# define CYLINDER(o, d, r, c)	((t_cylinder){o, normalize(d), r, c})

# define COLOR_ADD(o, t)	((t_color){o.r + t.r, o.g + t.g, o.b + t.b, o.s})

# define COLOR_ADDV(c, v)	((t_color){c.r + v, c.g + v, c.b + v, c.s + v})

# define COLOR_DIV(c, v)	((t_color){c.r / v, c.g / v, c.b / v, c.s / v})

# define COLOR_MUL(c, v)	((t_color){c.r * v, c.g * v, c.b * v, c.s * v})

# define COLOR_PAD(c)	((t_color){MIN(c.r, 1), MIN(c.g, 1), MIN(c.b, 1), c.s})

# define ADD_PLANE(plane)		(lstadd(&(scene->planes), &plane, sizeof(t_plane)))
# define ADD_SPHERE(sphere)		(lstadd(&(scene->spheres), &sphere, sizeof(t_sphere)))
# define ADD_CYLINDER(cylinder)	(lstadd(&(scene->cylinders), &cylinder, sizeof(t_cylinder)))
# define ADD_CONE(cone)			(lstadd(&(scene->cones), &cone, sizeof(t_cone)))

typedef struct		s_env
{
	void			*mlx;
	void			*win;
}					t_env;

typedef struct		s_vector
{
	double			x;
	double			y;
	double			z;
}					t_vector;

typedef struct		s_ray
{
	t_vector		origin;
	t_vector		direction;
}					t_ray;

typedef struct		s_camera
{
	t_vector		campos;
	t_vector		camdir;
	t_vector		camright;
	t_vector		camdown;
}					t_camera;

typedef struct		s_color
{
	double			r;
	double			g;
	double			b;
	double			s;
}					t_color;

typedef struct		s_light
{
	t_vector		origin;
	double			range;
}					t_light;

typedef struct		s_sphere
{
	t_vector		center;
	double			radius;
	t_color			color;
}					t_sphere;

typedef struct		s_plane
{
	t_vector		normal;
	t_vector		origin;
	t_color			color;
}					t_plane;

typedef struct		s_cylinder
{
	t_vector		origin;
	t_vector		direction;
	double			radius;
	t_color			color;
}					t_cylinder;

typedef struct		s_cone
{
	t_vector		origin;
	t_vector		direction;
	double			half_angle;
	t_color			color;
}					t_cone;

typedef struct		s_list
{
	void			*data;
	unsigned int	size;
	struct s_list	*next;
}					t_list;

typedef struct		s_scene
{
	t_camera		*camera;
	t_list			*lights;
	t_list			*planes;
	t_list			*spheres;
	t_list			*cylinders;
	t_list			*cones;
}					t_scene;

typedef struct		s_intersectInfo
{
	t_vector		point;
	t_vector		normal;
	double			t;
	t_color			color;
	double			brightness;
	char			shadowed;
}					t_intersectInfo;

t_intersectInfo		*cylinder_intersection(t_cylinder *cy, t_ray r);
t_intersectInfo		*cone_intersection(t_cone *co, t_ray r);
t_intersectInfo		*sphere_intersection(t_sphere *s, t_ray r);
t_intersectInfo		*plane_intersection(t_plane *p, t_ray r);
t_scene				*init_scene1(void);
t_scene				*init_scene2(void);
t_scene				*init_scene3(void);
t_scene				*init_scene4(void);
t_scene				*init_scene5(void);
t_scene				*init_scene6(void);
t_scene				*init_scene7(void);
t_scene				*init_scene8(void);
t_scene				*init_scene9(void);
t_camera			*create_camera(t_vector position);
void				add_light(t_scene *scene, t_vector position, int radius);
t_scene				*create_scene(t_camera *camera);
char				shadow_raytrace(t_scene *scene, t_light *light,
	double distance, t_intersectInfo *i);
t_color				raytrace(t_scene *scene, t_ray ray);
t_color				get_pixel_color(t_scene *scene, t_intersectInfo *o,
	t_ray ray);
void				check_planes(t_ray ray, t_list *planes,
	t_intersectInfo **o, double *max);
void				check_spheres(t_ray ray, t_list *spheres,
	t_intersectInfo **o, double *max);
void				check_cylinders(t_ray ray, t_list *cylinders,
	t_intersectInfo **o, double *max);
void				check_cones(t_ray ray, t_list *cones, t_intersectInfo **o,
	double *max);
char				check_sphere_shadows(t_ray light_ray, t_list *spheres,
	double distance);
char				check_cylinder_shadows(t_ray light_ray, t_list *cylinders,
	double distance);
char				check_cone_shadows(t_ray light_ray, t_list *cones,
	double distance);
void				iterate_pixels(t_env env, t_scene *scene);
t_env				init(char *title);
void				cleanup(t_env env);
t_list				*lstnew(const void *data, unsigned int size);
t_list				*lstadd(t_list **lst, const void *data, unsigned int size);
double				ttan(double angle);
t_vector			mult(t_vector v, double val);
t_vector			normalize(t_vector const v);
char				find_roots(double a, double b, double c, double *t);
t_env				win_init();

#endif
