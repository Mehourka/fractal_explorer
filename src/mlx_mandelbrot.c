#include "fractol.h"


int compute_iterations(float re, float im)
{
	t_data	*data = init_data();
	int		max_iter = data->max_iter;
	int		i;
	float a;
	float b;
	float new_a;
	float new_b;

	a = 0;
	b = 0;
	i = 0;
	while(i < max_iter)
	{
		new_a = a * a - b * b ;
		new_b = 2 * a * b ;

		a = new_a + re;
		b = new_b + im;
		if (a * a + b * b > 4)
			break;
		i++;
	}
	return (i);

}

float mod2(float v[2])
{
	return (v[0] * v[0] + v[1] * v[1]);
}

float compute_smooth_iterations(float z0[2], t_data *data)
{
	int		i;
	float zn[2];
	float tmp[2];
	float mod;
	float smooth_iter;

	zn[0] = z0[0];
	zn[1] = z0[1];
	i = 0;
	while(i < data->max_iter && mod2(zn) < 4)
	{
		tmp[0] = zn[0] * zn[0] - zn[1] * zn[1] ;
		tmp[1] = 2 * zn[0] * zn[1];
		zn[0] = tmp[0] + z0[0];
		zn[1] = tmp[1] + z0[1];
		i++;
	}
	mod = sqrt(mod2(zn));
	smooth_iter = (float) i - log2(fmax(1.0, log2(mod)));
	return (smooth_iter);

}

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void render_pixel(mlx_image_t *img, int i, int j, double num_iter)
{
	t_data *data = init_data();
	int max_iter = data->max_iter;
	int32_t		color = data->color;
	int32_t		opacity;

	opacity = (int) ft_map((float) num_iter, (float[]){0, max_iter}, (float[]){0, 255});
	color = color << 8 | opacity;
	if (num_iter == max_iter)
		mlx_put_pixel(img, i, j, BLACK);
	else
		mlx_put_pixel(img, i, j, color);
}

void mandelbrot(void *param)
{

	t_data			*data = param;
	mlx_t			*mlx = data->mlx;
	mlx_image_t		*image = data->image;
	float			*off = data->offset;
	float			pos[2];
	float itterations;

	for (int i = 0; i < image->width; i++)
	{
		for(int j= 0; j < image->height; j++)
		{
			pos[0] = (float) i;
			pos[1] = (float) j;
			map_vector(pos, data);
			sub_vector(pos, off);
			itterations = compute_smooth_iterations(pos, data);
			render_pixel(image, i, j, itterations);
		}
	}
}