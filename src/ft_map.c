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
