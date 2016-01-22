#include "RTv1.h"

double		ttan(double angle)
{
	return (tan(angle * PI/180));
}

t_vector 	mult(t_vector v, double val)
{
	return (VEC((v.x * val), (v.y * val), (v.z * val)));
}

t_vector	normalize(t_vector const v)
{
	const double magnitude = sqrt(SQR(v));

	return (VEC(v.x / magnitude, v.y / magnitude, v.z / magnitude));
}

char 		find_roots(double A, double B, double C, double *t)
{
	double denominator;
	double delta;
	double t1;
	double t2;

	delta = ((A == 0) ? ((B * B) - C) : ((B * B) - (4 * A * C)));
	denominator = ((A == 0) ? 1 : (2 * A));
	if (delta < 0.0f)
		return (0);
	if (delta != 0)
	{
		delta = (double)sqrt(delta);
		*t = MIN((-B + delta) / denominator, (-B - delta) / denominator);
	}
	else
	{
		*t = (-B) / (2 * A);
	}
	return (1);
}
