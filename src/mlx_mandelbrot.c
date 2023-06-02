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
		if (ft_abs(a + b) > 16)
			break;
		i++;
	}
	return (i);

}

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void render_pixel(mlx_image_t *img, int i, int j, int num_iter)
{
	t_data *data = init_data();
	int max_iter = data->max_iter;
	int32_t		color = 0xFF2288;
	int32_t		opacity;

	opacity = ft_map(num_iter, (t_range){0, max_iter}, (t_range){0, 255});
	// color = get_rgba(255,255, 255, opacity);
	color = color << 8 | opacity;
	if (num_iter == max_iter)
		mlx_put_pixel(img, i, j, BLACK);
	else
		mlx_put_pixel(img, i, j, color);
}

void mandelbrot(void *param)
{

	t_data			*data = init_data();
	mlx_t			*mlx = data->mlx;
	mlx_image_t		*image = data->image;
	t_range			xy_range = data->xy_range;
	t_vec			off = data->xy_offset;

	float x;
	float y;
	int itterations;

	for (int i = 0; i < image->width; i++)
	{
		for(int j= 0; j < image->height; j++)
		{
			x = ft_map(i, (t_range){0, image->width}, xy_range) + off.x;
			y = ft_map(j, (t_range){0, image->height}, xy_range) + off.y;
			itterations = compute_iterations(x, y);
			render_pixel(image, i, j, itterations);
		}
	}
}