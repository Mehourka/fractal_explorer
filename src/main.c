#include "fractol.h"

t_data *init_data(void)
{
	static t_data *data;


	if (!data)
	{
		data = malloc(sizeof(t_data));
		data->mlx = mlx_init(WIDTH, HEIGHT, "MLX42", false);
		data->image = mlx_new_image(data->mlx, WIDTH, HEIGHT);
		data->xy_range.min = -2;
		data->xy_range.max = 2;
		data->xy_offset.x = 0;
		data->xy_offset.x = 0;
		data->max_iter = 50;
	}
	return (data);
}


static void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}


// void	hook(void* param)
// {
// 	mlx_t* mlx;

// 	mlx = param;
// 	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
// 		mlx_close_window(mlx);
// 	if (mlx_is_key_down(mlx, MLX_KEY_P))
// 		mlx_delete_image(mlx, g_img);
// 	for (int x = 0; x < g_img->width; x++)
// 		for(int y= 0; y < g_img->height; y++)
// 			mlx_put_pixel(g_img, x, y, rand() % RAND_MAX);
// }


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

// static t_range		xy_range = {-2, 2};
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


void square_hook(void *param)
{

	t_data			*data = init_data();
	mlx_t			*mlx = data->mlx;
	mlx_image_t		*image = data->image;
	t_range			xy_range = data->xy_range;
	t_vec			off = data->xy_offset;
	float x;
	float y;

	for (int i = 0; i < image->width; i++)
	{
		for(int j= 0; j < image->height; j++)
		{
			x = ft_map(i, (t_range){0, image->width}, xy_range) + off.x;
			y = ft_map(j, (t_range){0, image->height}, xy_range) + off.y;
			if (x >= -1 && x <= 1 && y >= -1 && y <= 1)
				mlx_put_pixel(image, i, j, WHITE);
			else
				mlx_put_pixel(image, i, j, BLACK);
		}
	}
}





int32_t	main(void)
{
	t_data			*data = init_data();
	mlx_t			*mlx = data->mlx;

	data = init_data();

	if (!mlx)
		exit(EXIT_FAILURE);

	mlx_image_to_window(data->mlx, data->image, 0, 0);
	mlx_loop_hook(data->mlx, &square_hook, data->mlx);
	mlx_loop_hook(data->mlx, &key_navigation, data->mlx);
	mlx_scroll_hook(mlx, &scroll_zoom, NULL);

	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return (EXIT_SUCCESS);
}