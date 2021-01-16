#include "cub3d.h"

void		v_scale(double a, double v[2], double u[2])
{
	u[1] = a * v[1];
	u[0] = a * v[0];
}
