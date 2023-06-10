#include "bonus_fractol.h"

static double compute_burnin_ship_iterations(double z0[2], t_data *data)
{
	uint32_t	i;
	double		zn[2];
	double		tmp;
	double		mod;
	double		smooth_iter;

	zn[0] = z0[0];
	zn[1] = z0[1];
	i = 0;
	while(i < data->max_iter && mod2(zn) < 4.0)
	{
		tmp = zn[0];
		zn[0] = zn[0] * zn[0] - zn[1] * zn[1] + z0[0];
		zn[1] = -2.0 * fabs(zn[1] * tmp)  + z0[1];
		i++;
	}
	mod = sqrt(mod2(zn));
	if (i == data->max_iter)
		return (double) i;
	smooth_iter = (double) i + 1 - log(log(mod)) / log(2.0);
	return (smooth_iter);
}

void *burning_ship_routine(void *param)
{
	t_data			*data = param;
	double			pos[2];
	double iterations;
	uint32_t	i;
	uint32_t	j;


	uint32_t thread_num = ++data->step_i;
	uint32_t q = data->image->width / N_THREADS;
	uint32_t r = data->image->width % N_THREADS;
	uint32_t w = q + (thread_num < r);
	uint32_t start = thread_num * q + fmin(thread_num, r);
	uint32_t end = start + w;


	i = start;
	while (i < end)
	{
		j = 0;
		while(j < data->image->height)
		{
			pos[0] = (double) i;
			pos[1] = (double) j;
			map_vector(pos, data);
			sub_vector(pos, data->offset);
			iterations = compute_burnin_ship_iterations(pos,data);
			render_pixel(data->image, i, j, iterations);
			j++;
		}
		i++;
	}
	return (NULL);
}

void burning_ship_pthread(void *param)
{
	pthread_t th[N_THREADS];
	t_data *data = (t_data *) param;

	for (int i = 0; i < N_THREADS; i++)
	{
		pthread_create(&th[i], NULL, &burning_ship_routine, (void *) data);
	}

	for (int i = 0; i < N_THREADS; i++)
	{
		pthread_join(th[i], NULL);
	}
	data->step_i = -1;
}
