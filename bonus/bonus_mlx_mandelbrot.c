#include "fractol.h"

double mod2(double v[2])
{
	return (v[0] * v[0] + v[1] * v[1]);
}

static double compute_smooth_iterations(double z0[2], t_data *data)
{
	int		i;
	double zn[2];
	double tmp;
	double mod;
	double smooth_iter;

	zn[0] = z0[0];
	zn[1] = z0[1];
	i = 0;
	while(i < data->max_iter && mod2(zn) < 4.0)
	{
		tmp = zn[0];
		zn[0] = zn[0] * zn[0] - zn[1] * zn[1] + z0[0];
		zn[1] = 2.0 * zn[1] * tmp  + z0[1];
		i++;
	}
	// mod = sqrt(mod2(zn));
	// smooth_iter = (double) i - log2(fmax(1.0, log2(mod)));
	// if (smooth_iter < 0)
	// {
	// 	printf("%d, %f, %f, %f\n", i, mod, log(fmax(1.0f, log(mod))), smooth_iter);
	// }
	smooth_iter = (double) i;
	return (smooth_iter);

}

static int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

static void render_pixel(mlx_image_t *img, int i, int j, double num_iter)
{
	t_data *data = init_data();
	int max_iter = data->max_iter;
	int32_t		color = data->color;
	int32_t		opacity;

	opacity = (int) ft_map((double) num_iter, (double[]){0, max_iter}, (double[]){0, 255});
	color = color << 8 | opacity;
	if (num_iter == max_iter)
		mlx_put_pixel(img, i, j, BLACK);
	else
		mlx_put_pixel(img, i, j, color);
}

void *mandelbrot_routine(void *param)
{
	t_data			*data = param;
	mlx_t			*mlx = data->mlx;
	mlx_image_t		*image = data->image;
	double			*off = data->offset;
	double			pos[2];
	double itterations;

	int thread_num = ++data->step_i;
	int q = data->image->width / N_THREADS;
	int r = data->image->width % N_THREADS;
	int w = q + (thread_num < r);
	int start = thread_num * q + min(thread_num, r);
	int end = start + w;


	for (int i = start; i < end; i++)
	{
		for(int j= 0; j < image->height; j++)
		{
			pos[0] = (double) i;
			pos[1] = (double) j;
			map_vector(pos, data);
			sub_vector(pos, off);
			itterations = compute_smooth_iterations(pos, data);
			render_pixel(image, i, j, itterations);
		}
	}
}

void mandelbrot_pthread(void *param)
{
	pthread_t th[N_THREADS];
	t_data *data = (t_data *) param;

	for (int i = 0; i < N_THREADS; i++)
	{
		pthread_create(&th[i], NULL, &mandelbrot_routine, (void *) data);
	}

	for (int i = 0; i < N_THREADS; i++)
	{
		pthread_join(th[i], NULL);
	}
	data->step_i = -1;
}