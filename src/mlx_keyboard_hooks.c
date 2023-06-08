#include "fractol.h"

void keyboard_zoom(void *param)
{
	t_data	*data;
	double	EPS;

	data = (t_data *) param;
	EPS = 0.01;
	if (mlx_is_key_down(data->mlx, MLX_KEY_PAGE_UP))
	{
		mult_vector(data->x_range, 1 - EPS);
		mult_vector(data->y_range, 1 - EPS);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_PAGE_DOWN))
	{
		mult_vector(data->x_range, 1 + EPS);
		mult_vector(data->y_range, 1 + EPS);
	}
}

void keyboard_navigation(void *param)
{
	t_data	*data;
	double	EPS;
	double	range;

	data = (t_data *) param;
	range = data->x_range[1] - data->x_range[0];
	EPS = 0.005;
	if (mlx_is_key_down(data->mlx, MLX_KEY_UP))
		data->offset[1] -=  EPS * range;
	if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
		data->offset[1] +=  EPS * range;
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		data->offset[0] -=  EPS * range;
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		data->offset[0] +=  EPS * range;
}

void keyboard_itterations(void *param)
{
	t_data	*data;

	data = param;
	if(mlx_is_key_down(data->mlx, MLX_KEY_I) && data->max_iter < 500.0)
		data->max_iter += 10;
	if(mlx_is_key_down(data->mlx, MLX_KEY_O) && data->max_iter > 10.0)
		data->max_iter -= 10;
	if(mlx_is_key_down(data->mlx, MLX_KEY_C))
		data->color *= 1.03;
}

void keyboard_exit(void *param)
{
	t_data	*data;
	mlx_t	*mlx;

	data = (t_data*) param;
	mlx = data->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_P))
		mlx_delete_image(mlx, data->image);
}

void keyboard_hooks(void *param)
{
	t_data	*data = param;

	keyboard_exit((void*) data);
	keyboard_zoom((void*) data);
	keyboard_navigation((void*) data);
	keyboard_itterations((void*) data);
}
