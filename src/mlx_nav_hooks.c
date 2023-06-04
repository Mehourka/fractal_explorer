#include "fractol.h"

void scroll_zoom(double xdelta, double ydelta, void *param)
{
	t_data			*data = init_data();
	mlx_t			*mlx = data->mlx;
	float EPS = 0.1;

	int32_t mouseX;
	int32_t mouseY;
	mlx_get_mouse_pos(mlx, &mouseX, &mouseY);
	int dx = ft_map(mouseX, (t_range){0, WIDTH}, data->xy_range);
	int dy = ft_map(mouseY, (t_range){0, HEIGHT}, data->xy_range);

	if (ydelta < 0)
	{
		data->xy_offset.x -= dx * 0.5;
		data->xy_offset.y -= dy * 0.5;
		data->xy_range.min *= 1 + EPS;
		data->xy_range.max *= 1 + EPS;
	}
	if (ydelta > 0)
	{
		data->xy_offset.x += dx * 0.5;
		data->xy_offset.y += dy * 0.5;
		data->xy_range.min *= 1 - EPS;
		data->xy_range.max *= 1 - EPS;
	}
}

void key_navigation(void *param)
{
	t_data			*data = init_data();
	mlx_t			*mlx = data->mlx;
	float EPS = 0.02;
	float TRANS_EPS = 10;
	float range;

	range = data->xy_range.max - data->xy_range.min;

	// Exit
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_P))
		mlx_delete_image(mlx, data->image);

	// Zoom
	if (mlx_is_key_down(mlx, MLX_KEY_PAGE_UP))
	{
		data->xy_range.min *= 1 - EPS;
		data->xy_range.max *= 1 - EPS;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_PAGE_DOWN))
	{
		data->xy_range.min *= 1 + EPS;
		data->xy_range.max *= 1 + EPS;
	}

	// Translate
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		data->xy_offset.y +=  TRANS_EPS * range;

	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		data->xy_offset.y -=  TRANS_EPS * range;

	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		data->xy_offset.x +=  TRANS_EPS * range;

	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		data->xy_offset.x -=  TRANS_EPS * range;
}

void mouse_navigation(void *param)
{
	t_data			*data = param;
	mlx_t			*mlx = data->mlx;
	float EPS = 0.02;
	float TRANS_EPS = 0.2;
	float range;

	int32_t mouseX;
	int32_t mouseY;


	if(mlx_is_mouse_down(mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		mlx_get_mouse_pos(mlx, &mouseX, &mouseY);
		data->xy_offset.x += mouseX - data->pan_start.x;
		data->xy_offset.y += mouseY - data->pan_start.y;
		// printf("(%d, %d)\n", xdelta, ydelta);
		data->pan_start.x = mouseX;
		data->pan_start.y = mouseY;
	}
}

void iter_hook(void *param)
{
	t_data *data;

	data = param;
	if(mlx_is_key_down(data->mlx, MLX_KEY_I) && data->max_iter < 500)
		data->max_iter += 1;
	if(mlx_is_key_down(data->mlx, MLX_KEY_O) && data->max_iter > 1)
		data->max_iter -= 1;
}