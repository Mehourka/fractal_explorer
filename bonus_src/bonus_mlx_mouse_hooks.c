#include "bonus_fractol.h"

void capt_click_position(mouse_key_t button, action_t action, modifier_key_t mods, void* param)
{
	t_data *data;
	int32_t x;
	int32_t y;

	(void) mods;
	data = (t_data *) param;
	if(button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
	{
		mlx_get_mouse_pos(data->mlx, &x, &y);
		data->pan_start[0] = (double) x;
		data->pan_start[1] = (double) y;
	}
}

void scroll_zoom(double xdelta, double ydelta, void *param)
{
	t_data	*data;
	double	EPS;
	double	mouse_pos[2];
	int		pix_mouse_pos[2];

	data = (t_data*) param;
	EPS = 0.1;
	(void) xdelta;
	mlx_get_mouse_pos(data->mlx, pix_mouse_pos, pix_mouse_pos + 1);
	cast_vector(mouse_pos, pix_mouse_pos);
	map_vector(mouse_pos, data);
	if (ydelta < 0)
	{
		mult_vector(data->x_range, 1 + EPS);
		mult_vector(data->y_range, 1 + EPS);
		mult_vector(mouse_pos, -EPS);
	}
	if (ydelta > 0)
	{
		mult_vector(data->x_range, 1 - EPS);
		mult_vector(data->y_range, 1 - EPS);
		mult_vector(mouse_pos, EPS);
	}
	sub_vector(data->offset, mouse_pos);
}

void resize_window(int32_t width, int32_t height, void *param)
{
	t_data *data;

	data = param;
	mult_vector(data->x_range, width / data->x_pix_range[1]);
	mult_vector(data->y_range, height / data->y_pix_range[1] );
	mlx_resize_image(data->image, width, height);
	data->y_pix_range[1] = height;
	data->x_pix_range[1] = width;
}

void mouse_navigation(void *param)
{
	t_data	*data;
	mlx_t	*mlx;
	int		mouse_pos[2];
	double	delta[2];

	data = (t_data*) param;
	mlx = data->mlx;
	mlx_mouse_hook(data->mlx, &capt_click_position, data);
	if(mlx_is_mouse_down(mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		mlx_get_mouse_pos(mlx, mouse_pos, mouse_pos + 1);
		cast_vector(delta, mouse_pos);
		map_vector(delta, data);
		map_vector(data->pan_start, data);
		sub_vector(delta, data->pan_start);
		add_vector(data->offset, delta);
		cast_vector(data->pan_start, mouse_pos);
	}
}

void mouse_hooks(void *param)
{
	t_data	*data = param;
	
	mouse_navigation((t_data*) data);
	mlx_resize_hook(data->mlx, &resize_window, data);
	mlx_scroll_hook(data->mlx, &scroll_zoom, data);
	mlx_cursor_hook(data->mlx, &julia_mouse_control, data);
}
