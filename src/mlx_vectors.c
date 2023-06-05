#include "fractol.h"

void map_vector(float v[2], t_data *data)
{
	v[0] = ft_map(v[0], data->x_pix_range, data->x_range);
	v[1] = ft_map(v[1], data->y_pix_range, data->y_range);
}

void add_vector(float v[2], float u[2])
{
	v[0] += u[0];
	v[1] += u[1];
}

void sub_vector(float v[2], float u[2])
{
	v[0] -= u[0];
	v[1] -= u[1];
}

void mult_vector(float v[2], float c)
{
	v[0] *= c;
	v[1] *= c;
}

void cast_vector(float v[2], int u[2])
{
	v[0] = (float) u[0];
	v[1] = (float) u[1];
}