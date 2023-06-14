/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_mlx_mandelbrot.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 12:58:13 by kmehour           #+#    #+#             */
/*   Updated: 2023/06/14 13:05:00 by kmehour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_fractol.h"

static double	compute_smooth_iterations(double z0[2], t_data *data)
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
		zn[1] = 2.0 * zn[1] * tmp + z0[1];
		i++;
	}
	mod = sqrt(mod2(zn));
	if (i == data->max_iter)
		return ((double)i);
	smooth_iter = (double)i + 1 - log(log(mod)) / log(2.0);
	return (smooth_iter);
}

void	set_interval(uint32_t *limits, t_data *data)
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

void	*mandelbrot_routine(void *param)
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
			iterations = compute_smooth_iterations(pos, data);
			render_pixel(data->image, pix_xy[0], pix_xy[1], iterations);
			pix_xy[0]++;
		}
		pix_xy[1]++;
	}
	return (NULL);
}

void	mandelbrot_pthread(void *param)
{
	pthread_t	th[N_THREADS];
	t_data		*data;
	int			i;

	data = (t_data *)param;
	i = 0;
	while (i < N_THREADS)
	{
		pthread_create(&th[i], NULL, &mandelbrot_routine, (void *)data);
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
