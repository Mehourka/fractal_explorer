#include "fractol.h"


t_data *init_data(void)
{
	static t_data *data;


	if (!data)
	{
		data = malloc(sizeof(t_data));
		data->mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
		data->image = mlx_new_image(data->mlx, WIDTH, HEIGHT);
		data->x_range[0] = -2;
		data->x_range[1] = 2;
		data->y_range[0] = -data->x_range[0] * HEIGHT / WIDTH;
		data->y_range[1] = -data->x_range[1] * HEIGHT / WIDTH;
		data->x_pix_range[0] = 0;
		data->x_pix_range[1] = WIDTH;
		data->y_pix_range[0] = 0;
		data->y_pix_range[1] = HEIGHT;
		data->offset[0] = 0;
		data->offset[1] = 0;
		data->pan_start[0] = 0;
		data->pan_start[1] = 0;
		data->color = COLOR;

		data->julia_c[0] = 0.2345;
		data->julia_c[0] = 0.3254;
		data->t			 = 0;

		data->step_i = -1;
		data->max_iter = MAX_ITER;
	}
	return (data);
}