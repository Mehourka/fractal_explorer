#include "fractol.h"

static float float_min(float a, float b)
{
	if (a > b)
		return b;
	else
		return a;
}

static float float_max(float a, float b)
{
	if (a > b)
		return a;
	else
		return b;
}

float ft_abs(float a)
{
	if (a >= 0)
		return a;
	return (-a);
}


float ft_map(float val, float in_range[2], float out_range[2])
{
	float scale;

	scale = (float) (val - in_range[0]) / (in_range[1] - in_range[0]);
	return (float) (out_range[0] + (out_range[1] - out_range[0]) * scale);

}
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

void mul_vector(float v[2], float c)
{
	v[0] *= c;
	v[1] *= c;
}