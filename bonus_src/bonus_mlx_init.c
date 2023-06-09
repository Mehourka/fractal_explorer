#include "bonus_fractol.h"

void init_mlx_ranges(t_data *data)
{
	data->x_range[0] = -2;
	data->x_range[1] = 2;
	data->y_range[0] = -data->x_range[0] * HEIGHT / WIDTH;
	data->y_range[1] = -data->x_range[1] * HEIGHT / WIDTH;
	data->x_pix_range[0] = 0;
	data->x_pix_range[1] = WIDTH;
	data->y_pix_range[0] = 0;
	data->y_pix_range[1] = HEIGHT;
}

void init_mlx_image(t_data *data)
{
	data->image = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if(!data->image)
		ft_error();
	if (mlx_image_to_window(data->mlx, data->image, 0, 0) == -1)
	{
		mlx_close_window(data->mlx);
		ft_error();
	}
}

t_data *init_data(void)
{
	static t_data *data;

	if (!data)
	{
		data = malloc(sizeof(t_data));
		if (!data)
			exit(EXIT_FAILURE);
		data->mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
		if(!data->mlx)
			ft_error();
		data->offset[0] = 0;
		data->offset[1] = 0;
		data->pan_start[0] = 0;
		data->pan_start[1] = 0;
		data->color = COLOR;
		data->julia_c[0] = 0.2345;
		data->julia_c[0] = 0.3254;
		data->t			 = 0;
		data->step_i	 = -1;
		data->max_iter = MAX_ITER;
		init_mlx_image(data);
		init_mlx_ranges(data);
	}
	return (data);
}
