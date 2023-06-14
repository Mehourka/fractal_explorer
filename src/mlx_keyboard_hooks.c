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

void keyboard_julia_flag(mlx_key_data_t keydata, void *param)
{
	t_data	*data;
	data = (t_data*) param;
	int julia_control_flag;

	julia_control_flag = 0;
	if (keydata.key == MLX_KEY_J && keydata.action == MLX_PRESS)
		julia_control_flag = !julia_control_flag;

	if(julia_control_flag)
		mlx_cursor_hook(data->mlx, &julia_mouse_control, data);

}

void keyboard_hooks(void *param)
{
	t_data	*data = param;

	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	keyboard_zoom((void*) data);
	keyboard_navigation((void*) data);
	keyboard_itterations((void*) data);
	mlx_key_hook(data->mlx, &keyboard_julia_flag, data);
}
