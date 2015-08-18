#ifndef RTV1_H
# define RTV1_H

#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>


#define INVSQRTF(x)					(1.0f / sqrtf(x))

#define MIN(x, y)					(x < y ? x : y)
#define MAX(x, y)					(x > y ? x : y)

#define SCREEN_HEIGHT				800
#define SCREEN_WIDTH				1000
#define FOV							60

#define X_VEC						((t_vector){1, 0, 0})
#define Y_VEC						((t_vector){0, 1, 0})
#define Z_VEC						((t_vector){0, 0, 1})
#define D_VEC						((t_vector){0, 0 ,0})

#define VEC(x, y, z)				((t_vector){x, y, z})

#define MAG(v)						sqrt(v.x * v.x + v.y * v.y + v.z + v.z)
#define NEG(v)						(VEC(-v.x, -v.y, -v.z))
#define DOT_PROD(v1, v2)			((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z))
#define CROSS_PROD(v1, v2)			(VEC(										\
										v1.y * v2.z - v1.z * v2.y,				\
										v1.z * v2.x - v1.x * v2.z,				\
										v1.x * v2.y - v1.y * v2.x)				\
									)
#define ADD(v1, v2)					(VEC(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z))
#define MUL(v, val)					(VEC(v.x * val, v.y * val, v.z * val))
#define SUB(v1, v2)					(VEC(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z))
#define SUBV(v1, val)					(VEC(v1.x - val, v1.y - val, v1.z - val))
#define SQR(v)						v.x * v.x + v.y * v.y + v.z * v.z
#define DEFAULT_RAY					((t_ray){D_VEC, X_VEC})
#define RAY(ori, dir)				((t_ray){ori, dir})

#define CAM(pos, dir, right, down)	((t_camera) {pos, dir, right, down})

#define DEFAULT_COLOR				((t_color){0.5, 0.5, 0.5, 0.1})
#define COLOR(r, g, b, s)			((t_color){r, g, b, s})

#define DEFAULT_LIGHT				((t_light){D_VEC, COLOR(1, 1, 1, 0)})
#define LIGHT(o, c)					((t_light){o, c})

#define DEFAULT_SPHERE				((t_sphere){D_VEC, 1.0, DEFAULT_COLOR, b})
#define SPHERE(v, r, c, b)				((t_sphere){v, r, c, b})

#define DEFAULT_PLANE				((t_plane){X_VEC, 0, DEFAULT_COLOR})
#define PLANE(n, o, c)				((t_plane){normalize(n), o, c})

#define CYLINDER(o, d, r, c)		((t_cylinder){o, normalize(d), r, c})
typedef struct s_env
{
	SDL_Window		*screen;
	SDL_Renderer	*renderer;
} t_env;

typedef struct s_vector
{
	double x;
	double y;
	double z;
} t_vector;


typedef struct s_ray
{
	t_vector origin;
	t_vector direction;

} t_ray;


typedef struct s_camera
{
	t_vector campos;
	t_vector camdir;
	t_vector camright;
	t_vector camdown;
} t_camera;

typedef struct s_color
{
	double r;
	double g;
	double b;
	double s;
} t_color;

typedef struct s_light
{
	t_vector	origin;
	t_color		color;
} t_light;

typedef struct s_sphere
{
	t_vector	center;
	double		radius;
	t_color		color;
	double		brightness;
} t_sphere;

typedef struct s_plane
{
	t_vector	normal;
	t_vector	origin;
	t_color		color;
} t_plane;

typedef struct s_cylinder
{
	t_vector	origin;
	t_vector	direction;
	double		radius;
	t_color		color;
} t_cylinder;

typedef struct s_list
{
	void			*data;
	unsigned int	size;
	struct s_list	*next;
} t_list;

typedef struct s_intersectInfo
{
	t_vector		point;
	t_vector		normal;
	double			t;
	t_color			color;
	double			brightness;
	char			shadowed;
} t_intersectInfo;

#endif
