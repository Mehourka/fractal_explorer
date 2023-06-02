#include "fractol.h"

void scroll_zoom(double xdelta, double ydelta, void *param)
{
	t_data			*data = init_data();
	mlx_t			*mlx = data->mlx;
	float EPS = 0.1;

	if (ydelta > 0)
	{
		data->xy_range.min *= 1 + EPS;
		data->xy_range.max *= 1 + EPS;
	}
	if (ydelta < 0)
	{
		data->xy_range.min *= 1 - EPS;
		data->xy_range.max *= 1 - EPS;
	}

}

void key_navigation(void *param)
{
	t_data			*data = init_data();
	mlx_t			*mlx = data->mlx;
	float EPS = 0.02;
	float TRANS_EPS = 0.2;
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
		data->xy_range.min *= 1 + EPS;
		data->xy_range.max *= 1 + EPS;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_PAGE_DOWN))
	{
		data->xy_range.min *= 1 - EPS;
		data->xy_range.max *= 1 - EPS;
	}

	// Translate
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		data->xy_offset.y -=  EPS * range;

	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		data->xy_offset.y +=  EPS * range;

	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		data->xy_offset.x -=  EPS * range;

	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		data->xy_offset.x +=  EPS * range;
}