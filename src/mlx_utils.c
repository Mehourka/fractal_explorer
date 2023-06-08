#include "fractol.h"

void ft_error(void)
{
	printf("REPORTING\n");
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

