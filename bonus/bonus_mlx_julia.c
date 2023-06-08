#include "fractol.h"

static double mod2(double v[2])
{
	return (v[0] * v[0] + v[1] * v[1]);
}

static double compute_smooth_iterations(double pos[2], t_data *data)
{
	int		i;
	double zn[2];
	double tmp;
	double *julia_c;
	double smooth_iter;

	zn[0] = pos[0];
	zn[1] = pos[1];
	julia_c = data->julia_c;
	i = 0;
	while(i < data->max_iter && mod2(zn) < 4.0)
	{
		tmp = zn[0];
		zn[0] = zn[0] * zn[0] - zn[1] * zn[1] + julia_c[0];
		zn[1] = 2.0 * zn[1] * tmp  + julia_c[1];
		i++;
	}
	double mod = sqrt(mod2(zn));
	smooth_iter = (double) i - log(log(mod)) / log(2.0);
	// smooth_iter = (double) i + 1 - log2(fmax(1.0, log2(mod)));
	return (smooth_iter);

}

static int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

static  void render_pixel(mlx_image_t *img, int i, int j, double num_iter)
{
	t_data *data = init_data();
	int max_iter = data->max_iter;
	int32_t		color = data->color;
	int32_t		opacity;

	opacity = (int) ft_map((double) num_iter, (double[]){0, max_iter}, (double[]){0, 255});
	// opacity = sqrt(opacity);
	// opacity = (int) ft_map((double) opacity, (double[]){0, 1}, (double[]){100,150});
	color = color << 8 | opacity;
	// color = get_rgba(opacity, opacity, opacity, 0xFF);
	if (num_iter == max_iter)
		mlx_put_pixel(img, i, j, BLACK);
	else
		mlx_put_pixel(img, i, j, color);
}

void julia_time(t_data *data)
{
	data->t += 0.005;

	data->julia_c[0] = cos(data->t + M_PI / 4);
	data->julia_c[1] = cos(data->t + M_PI / 2);
}


void julia_mouse_control(double xpos, double ypos, void* param)
{
	t_data *data;
	double scale;

	data = param;
	scale = data->x_pix_range[1] - data->x_pix_range[0];

	xpos = ft_map(xpos, data->x_pix_range, data->x_range);
	ypos = ft_map(ypos, data->y_pix_range, data->y_range);

	data->julia_c[0] = ft_map(xpos, data->x_range, (double[]){-M_PI / 2, M_PI / 2});
	data->julia_c[1] = ft_map(ypos, data->y_range, (double[]){-M_PI / 2, M_PI / 2});
}

/* ****************************************************** */
/* 						BONUS							  */
/* ****************************************************** */
# include <pthread.h>
void *julia_routine(void *param)
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

	// julia_time(data);
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

void julia_pthread(void *param)
{
	pthread_t th[N_THREADS];
	t_data *data = (t_data *) param;

	for (int i = 0; i < N_THREADS; i++)
	{
		pthread_create(&th[i], NULL, &julia_routine, (void *) data);
	}

	for (int i = 0; i < N_THREADS; i++)
	{
		pthread_join(th[i], NULL);
	}
	data->step_i = -1;

}