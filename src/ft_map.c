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


float ft_map(float val, t_range in_range, t_range out_range)
{
	float scale;

	scale = (float) (val - in_range.min) / (in_range.max - in_range.min);
	return (float) (out_range.min + (out_range.max - out_range.min) * scale);

}
// float ft_map_to_plane(t_vec v, t_data data)
// {

// 	ft_map(val[], );
// }