#include "fractol.h"

t_data *init_data(void)
{
	static t_data *data;


	if (!data)
	{
		data = malloc(sizeof(t_data));
		data->mlx = mlx_init(WIDTH, HEIGHT, "MLX42", false);
		data->image = mlx_new_image(data->mlx, WIDTH, HEIGHT);
		data->x_range[0] = -2;
		data->x_range[1] = 2;
		data->y_range[0] = 2;
		data->y_range[1] = -2;
		data->x_pix_range[0] = 0;
		data->x_pix_range[1] = WIDTH;
		data->y_pix_range[0] = 0;
		data->y_pix_range[1] = HEIGHT;
		data->offset[0] = 0;
		data->offset[1] = 0;
		data->pan_start[0] = 0;
		data->pan_start[1] = 0;

		data->max_iter = MAX_ITER;
	}
	return (data);
}


static void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

void capt_mouse_start(mouse_key_t button, action_t action, modifier_key_t mods, void* param)
{
	t_data *data = (t_data *) param;
	int32_t x;
	int32_t y;

	if(button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
	{
		mlx_get_mouse_pos(data->mlx, &x, &y);
		data->pan_start[0] = (float) x;
		data->pan_start[1] = (float) y;
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


	/* NAVIGATION */
	mlx_loop_hook(data->mlx, &key_navigation, data);
	mlx_scroll_hook(mlx, &scroll_zoom, data);
	mlx_mouse_hook(data->mlx, &capt_mouse_start, data);
	mlx_loop_hook(data->mlx, &mouse_navigation, data);

	/* Fractal */
	mlx_loop_hook(data->mlx, &iter_hook, data);
	mlx_loop_hook(data->mlx, &mandelbrot, data);

	/* Test Square */
	// mlx_loop_hook(data->mlx, &square_hook, data);

	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return (EXIT_SUCCESS);
}