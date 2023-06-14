#include "fractol.h"

void julia_time_shift(t_data *data)
{
	data->t += 0.0005;

	data->julia_c[0] = cos(data->t + M_PI / 4);
	data->julia_c[1] = cos(data->t + M_PI / 2);
}

static double compute_julia_iterations(double z0[2], double *julia_c, t_data *data)
{
	uint32_t i;
	double zn[2];
	double tmp;
	double mod;
	double smooth_iter;

	zn[0] = z0[0];
	zn[1] = z0[1];
	i = 0;
	while (i < data->max_iter && mod2(zn) < 4.0)
	{
		tmp = zn[0];
		zn[0] = zn[0] * zn[0] - zn[1] * zn[1] + julia_c[0];
		zn[1] = 2.0 * zn[1] * tmp + julia_c[1];
		i++;
	}
	if (i == data->max_iter)
		return (double)i;
	mod = sqrt(mod2(zn));
	smooth_iter = (double)i + 1 - log(log(mod)) / log(2.0);
	return (smooth_iter);
}

void julia(void *param)
{
	t_data *data = param;
	double pos[2];
	double iterations;
	uint32_t i;
	uint32_t j;

	i = 0;
	while (i < data->image->width)
	{
		j = 0;
		while (j < data->image->height)
		{
			pos[0] = (double)i;
			pos[1] = (double)j;
			map_vector(pos, data);
			sub_vector(pos, data->offset);
			iterations = compute_julia_iterations(pos, data->julia_c, data);
			render_pixel(data->image, i, j, iterations);
			j++;
		}
		i++;
	}
}

void julia_mouse_control(double xpos, double ypos, void *param)
{
	t_data *data;
	double pos2[2] = {xpos, ypos};
	// static int flag = 0;

	data = param;

	// if (mlx_is_key_down(data->mlx, MLX_KEY_J))
	// flag = !flag;
	// if (!flag)
	// return;
	// data->julia_c[0] = sin(ft_map(xpos, data->x_pix_range, (double[]){-M_PI / 2, M_PI / 2}));
	// data->julia_c[1] = sin(ft_map(ypos, data->y_pix_range, (double[]){-M_PI / 2, M_PI / 2}));
	map_vector(pos2, init_data());
	data->julia_c[0] = pos2[0];
	data->julia_c[1] = pos2[1];
}
