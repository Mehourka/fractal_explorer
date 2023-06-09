#include "bonus_fractol.h"

void free_data(void)
{
	t_data *data;
	data = init_data();

	mlx_terminate(data->mlx);
	free(data);
}

void ft_error(void)
{
	ft_putstr_fd((char*)mlx_strerror(mlx_errno), STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	free_data();
	exit(EXIT_FAILURE);
}

