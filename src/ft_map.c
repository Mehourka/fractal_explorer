#include "fractol.h"

double ft_abs(double a)
{
	if (a >= 0)
		return a;
	return (-a);
}

double ft_map(double val, double in_range[2], double out_range[2])
{
	double scale;

	scale = (double) (val - in_range[0]) / (in_range[1] - in_range[0]);
	return (double) (out_range[0] + (out_range[1] - out_range[0]) * scale);

}
