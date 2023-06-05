#include "fractol.h"

void scroll_zoom(double xdelta, double ydelta, void *param)
{
	t_data			*data = param;
	mlx_t			*mlx = data->mlx;
	float EPS = 0.1;
	float mouse_pos[2];
	int pix_mouse_pos[2];

	mlx_get_mouse_pos(mlx, pix_mouse_pos, pix_mouse_pos + 1);
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

void key_navigation(void *param)
{
	t_data			*data = param;
	mlx_t			*mlx = data->mlx;
	float EPS = 0.02;
	float TRANS_EPS = 0.02;
	float range;

	range = data->x_range[1] - data->x_range[0];

	// Exit
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_P))
		mlx_delete_image(mlx, data->image);

	// Zoom
	if (mlx_is_key_down(mlx, MLX_KEY_PAGE_UP))
	{
		mult_vector(data->x_range, 1 - EPS);
		mult_vector(data->y_range, 1 - EPS);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_PAGE_DOWN))
	{
		mult_vector(data->x_range, 1 + EPS);
		mult_vector(data->y_range, 1 + EPS);
	}

	// Translate
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		data->offset[1] -=  TRANS_EPS * range;

	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		data->offset[1] +=  TRANS_EPS * range;

	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		data->offset[0] -=  TRANS_EPS * range;

	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		data->offset[0] +=  TRANS_EPS * range;
}

void mouse_navigation(void *param)
{
	t_data			*data = param;
	mlx_t			*mlx = data->mlx;

	int mouse_pos[2];
	float delta[2];


	if(mlx_is_mouse_down(mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		mlx_get_mouse_pos(mlx, mouse_pos, mouse_pos + 1);
		delta[0] = mouse_pos[0];
		delta[1] = mouse_pos[1];
		map_vector(delta, data);
		map_vector(data->pan_start, data);
		sub_vector(delta, data->pan_start);
		add_vector(data->offset, delta);

		data->pan_start[0] = mouse_pos[0];
		data->pan_start[1] = mouse_pos[1];
	}
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

void iter_hook(void *param)
{
	t_data *data;

	data = param;
	if(mlx_is_key_down(data->mlx, MLX_KEY_I) && data->max_iter < 500)
		data->max_iter += 1;
	if(mlx_is_key_down(data->mlx, MLX_KEY_O) && data->max_iter > 1)
		data->max_iter -= 1;
	if(mlx_is_key_down(data->mlx, MLX_KEY_C))
		data->color *= 1.3;
}