/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_mlx_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 12:32:32 by kmehour           #+#    #+#             */
/*   Updated: 2023/06/14 13:48:00 by kmehour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_fractol.h"

void	free_data(void)
{
	t_data	*data;

	data = init_data();
	mlx_terminate(data->mlx);
	free(data);
}

void	ft_error(void)
{
	if (mlx_errno)
	{
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	free_data();
	exit(EXIT_FAILURE);
}

void	set_interval(uint32_t limits[2], t_data *data)
{
	uint32_t	thread_num;
	uint32_t	q;
	uint32_t	r;
	uint32_t	start;
	uint32_t	end;

	thread_num = ++data->step_i;
	q = data->image->width / N_THREADS;
	r = data->image->width % N_THREADS;
	start = thread_num * q + fmin(thread_num, r);
	end = start + q + (thread_num < r);
	limits[0] = start;
	limits[1] = end;
}
