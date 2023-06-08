#include "fractol.h"

int32_t	main(void)
{
	t_data	*data;
	mlx_t	*mlx;

	data = init_data();
	mlx = data->mlx;

	(void) mlx;

	mlx_loop_hook(data->mlx, &keyboard_hooks, data);
	mlx_loop_hook(data->mlx, &mouse_hooks, data);


	// /* Fractal */
	mlx_loop_hook(data->mlx, &mandelbrot, data);
	// // mlx_loop_hook(data->mlx, &julia_pthread, data);
	// // mlx_cursor_hook(data->mlx, &julia_mouse_control, data);

	mlx_loop(data->mlx);
	free_data();
	return (EXIT_SUCCESS);
}