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
		data->max_iter = MAX_ITER;
	}
	return (data);
}


static void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}



int32_t	main(void)
{
	t_data			*data = init_data();
	mlx_t			*mlx = data->mlx;

	data = init_data();

	if (!mlx)
		exit(EXIT_FAILURE);

	mlx_image_to_window(data->mlx, data->image, 0, 0);
	// mlx_loop_hook(data->mlx, &square_hook, data->mlx);
	mlx_loop_hook(data->mlx, &mandelbrot, data->mlx);

	/* NAVIGATION */
	mlx_loop_hook(data->mlx, &key_navigation, data->mlx);
	mlx_scroll_hook(mlx, &scroll_zoom, NULL);

	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return (EXIT_SUCCESS);
}