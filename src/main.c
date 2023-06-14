/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:10:50 by kmehour           #+#    #+#             */
/*   Updated: 2023/06/14 13:11:34 by kmehour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

int32_t	main(int argc, char *argv[])
{
	t_data	*data;

	data = init_data();
	parse_arguments(argc, argv, data);
	mlx_loop_hook(data->mlx, &keyboard_hooks, data);
	mlx_loop_hook(data->mlx, &mouse_hooks, data);
	mlx_loop_hook(data->mlx, data->frac_function, data);
	mlx_loop(data->mlx);
	free_data();
	return (EXIT_SUCCESS);
}
