/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_burning_ship.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:10:41 by kmehour           #+#    #+#             */
/*   Updated: 2023/06/14 13:10:44 by kmehour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static double	compute_burnin_ship_iterations(double z0[2], t_data *data)
{
	uint32_t	i;
	double		zn[2];
	double		tmp;
	double		mod;
	double		smooth_iter;

	zn[0] = z0[0];
	zn[1] = z0[1];
	i = 0;
	while (i < data->max_iter && mod2(zn) < 4.0)
	{
		tmp = zn[0];
		zn[0] = zn[0] * zn[0] - zn[1] * zn[1] + z0[0];
		zn[1] = -2.0 * fabs(zn[1] * tmp) + z0[1];
		i++;
	}
	mod = sqrt(mod2(zn));
	if (i == data->max_iter)
		return ((double)i);
	smooth_iter = (double)i + 1 - log(log(mod)) / log(2.0);
	return (smooth_iter);
}

void	burning_ship(void *param)
{
	t_data		*data;
	double		pos[2];
	double		iterations;
	uint32_t	i;
	uint32_t	j;

	data = param;
	i = 0;
	while (i < data->image->width)
	{
		j = 0;
		while (j < data->image->height)
		{
			pos[0] = (double)i;
			pos[1] = (double)j;
			map_vector(pos, data);
			sub_vector(pos, data->offset);
			iterations = compute_burnin_ship_iterations(pos, data);
			render_pixel(data->image, i, j, iterations);
			j++;
		}
		i++;
	}
}
