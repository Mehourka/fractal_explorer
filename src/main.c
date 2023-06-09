#include "fractol.h"
#include <stdio.h>


void identity(void *param)
{

	t_data			*data = param;
	mlx_image_t		*image = data->image;
	double			*off = data->offset;
	double			pos[2];


	for (uint32_t i = 0; i < image->width; i++)
	{
		for(uint32_t j= 0; j < image->height; j++)
		{
			pos[0] = (double) i;
			pos[1] = (double) j;
			map_vector(pos, data);
			sub_vector(pos, off);
			if (pos[0] == 0 || pos[1] == 0)
				mlx_put_pixel(image, i, j, WHITE);
		}
	}
}

int32_t	main(int argc, char *argv[])
{
	t_data	*data;
	// mlx_t	*mlx;

	data = init_data();
	// mlx = data->mlx;

	(void) argc;
	(void) argv;

	parse_arguments(argc, argv, data);
	printf("atod result : %f\n", ft_atod("0.0"));
	printf("atod result : %f\n", ft_atod("-1.6"));
	printf("atod result : %f\n", ft_atod("2.6"));
	printf("atod result : %f\n", ft_atod("-125798"));
	printf("atod result : %f\n", ft_atod("3324"));



	// mlx_loop_hook(data->mlx, &keyboard_hooks, data);
	// mlx_loop_hook(data->mlx, &mouse_hooks, data);


	// mlx_loop_hook(data->mlx, data->frac_function, data);
	// mlx_cursor_hook(data->mlx, &julia_mouse_control, data);
	mlx_loop_hook(data->mlx, &identity, data);

	mlx_loop(data->mlx);
	free_data();

	return (EXIT_SUCCESS);
}