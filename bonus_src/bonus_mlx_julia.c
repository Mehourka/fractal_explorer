/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_mlx_julia.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:09:57 by kmehour           #+#    #+#             */
/*   Updated: 2023/06/14 13:51:23 by kmehour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_fractol.h"

void	julia_time_shift(t_data *data)
{
	data->t += 0.0005;
	data->julia_c[0] = cos(data->t + M_PI / 4);
	data->julia_c[1] = cos(data->t + M_PI / 2);
}

static double	compute_julia_iterations(double z0[2], double *julia_c,
		t_data *data)
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
		zn[0] = zn[0] * zn[0] - zn[1] * zn[1] + julia_c[0];
		zn[1] = 2.0 * zn[1] * tmp + julia_c[1];
		i++;
	}
	if (i == data->max_iter)
		return ((double)i);
	mod = sqrt(mod2(zn));
	smooth_iter = (double)i + 1 - log(log(mod)) / log(2.0);
	return (smooth_iter);
}

void	*julia_routine(void *param)
{
	t_data		*data;
	double		pos[2];
	double		iterations;
	uint32_t	interval[2];
	uint32_t	pix_xy[2];

	data = param;
	set_interval(interval, data);
	pix_xy[0] = interval[0];
	while (pix_xy[0] < interval[1])
	{
		pix_xy[1] = 0;
		while (pix_xy[1] < data->image->height)
		{
			pos[0] = (double)pix_xy[0];
			pos[1] = (double)pix_xy[1];
			map_vector(pos, data);
			sub_vector(pos, data->offset);
			iterations = compute_julia_iterations(pos, data->julia_c, data);
			render_pixel(data->image, pix_xy[0], pix_xy[1], iterations);
			pix_xy[1]++;
		}
		pix_xy[0]++;
	}
	return (NULL);
}

void	julia_pthread(void *param)
{
	pthread_t	th[N_THREADS];
	t_data		*data;
	int			i;

	data = (t_data *)param;
	i = 0;
	while (i < N_THREADS)
	{
		pthread_create(&th[i], NULL, &julia_routine, (void *)data);
		i++;
	}
	i = 0;
	while (i < N_THREADS)
	{
		pthread_join(th[i], NULL);
		i++;
	}
	data->step_i = -1;
}

void	julia_mouse_control(double xpos, double ypos, void *param)
{
	t_data	*data;
	double	pos2[2];

	pos2[0] = xpos;
	pos2[1] = ypos;
	data = param;
	map_vector(pos2, init_data());
	data->julia_c[0] = pos2[0];
	data->julia_c[1] = pos2[1];
}
