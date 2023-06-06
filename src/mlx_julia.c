#include "fractol.h"

static double mod2(double v[2])
{
	return (v[0] * v[0] + v[1] * v[1]);
}

static double compute_smooth_iterations(double pos[2], t_data *data)
{
	int		i;
	double zn[2];
	double tmp;
	double *julia_c;
	double smooth_iter;

	zn[0] = pos[0];
	zn[1] = pos[1];
	julia_c = data->julia_c;
	i = 0;
	while(i < data->max_iter && mod2(zn) < 4.0)
	{
		tmp = zn[0];
		zn[0] = zn[0] * zn[0] - zn[1] * zn[1] + julia_c[0];
		zn[1] = 2.0 * zn[1] * tmp  + julia_c[1];
		i++;
	}
	smooth_iter = (double) i;
	return (smooth_iter);

}

static int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

static  void render_pixel(mlx_image_t *img, int i, int j, double num_iter)
{
	t_data *data = init_data();
	int max_iter = data->max_iter;
	int32_t		color = data->color;
	int32_t		opacity;

	opacity = (int) ft_map((double) num_iter, (double[]){0, max_iter}, (double[]){0, 255});
	color = color << 8 | opacity;
	if (num_iter == max_iter)
		mlx_put_pixel(img, i, j, BLACK);
	else
		mlx_put_pixel(img, i, j, color);
}

void julia(void *param)
{

	t_data			*data = param;
	mlx_t			*mlx = data->mlx;
	mlx_image_t		*image = data->image;
	double			*off = data->offset;
	double			pos[2];
	double itterations;

	for (int i = 0; i < image->width; i++)
	{
		for(int j= 0; j < image->height; j++)
		{
			pos[0] = (double) i;
			pos[1] = (double) j;
			map_vector(pos, data);
			sub_vector(pos, off);
			itterations = compute_smooth_iterations(pos, data);
			render_pixel(image, i, j, itterations);
		}
	}
}

void julia_mouse_control(double xpos, double ypos, void* param)
{
	t_data *data;

	data = param;
	data->julia_c[0] = sin(ft_map(xpos, data->x_pix_range, (double[]){-M_PI / 2, M_PI / 2}));
	data->julia_c[1] = sin(ft_map(ypos, data->y_pix_range, (double[]){-M_PI / 2, M_PI / 2}));
}
