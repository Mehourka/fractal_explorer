#include "fractol.h"

double mod2(double v[2])
{
	return (v[0] * v[0] + v[1] * v[1]);
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

	opacity = ft_map((double) num_iter, (double[]){0, max_iter}, (double[]){0, 255});
	color = color << 8 | opacity;

	// double hue = ft_map((double) num_iter, (double[]){0, max_iter}, (double[]){-M_PI / 2, M_PI / 2});
	// hue = (cos(hue) / 2 + 0.5) * 255 ;
	// color = get_rgba(hue, hue, hue, 255);
	// color = get_rgba(255 * pow(hue, 0.2), 255 * sqrt(hue), 250 * sqrt(hue), 255);
	// color = get_rgba(200 * sqrt(hue), 200 * pow(hue, 0.2), 200 * pow(hue, 0.2), 255);
	if (num_iter == max_iter)
		mlx_put_pixel(img, i, j, BLACK);
	else
		mlx_put_pixel(img, i, j, color);
}