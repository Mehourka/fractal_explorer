#include "fractol.h"

int32_t	main(void)
{
	t_data			*data = init_data();
	mlx_t			*mlx = data->mlx;

	data = init_data();

	if (!mlx)
		exit(EXIT_FAILURE);

	mlx_loop_hook(data->mlx, &keyboard_hooks, data);
	mlx_loop_hook(data->mlx, &mouse_hooks, data);

	/* Fractal */
	mlx_loop_hook(data->mlx, &mandelbrot, data);
	// mlx_loop_hook(data->mlx, &julia_pthread, data);
	// mlx_cursor_hook(data->mlx, &julia_mouse_control, data);


	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return (EXIT_SUCCESS);
}